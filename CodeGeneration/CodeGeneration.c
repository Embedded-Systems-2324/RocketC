#include "../Util/Logger.h"
#include "CodeGeneration.h"
#include "CodeGenerationTypes.h"
#include "../Util/Util.h"

#define MAX_32BIT_RANGE  0xFFFFFFFF
#define MAX_IMMED_ALU   ((1 << 16) - 1)
#define MAX_IMMED_LD    ((1 << 22) - 1)
#define MAX_IMMED_LDI   ((1 << 22) - 1)
#define MAX_IMMED_LDX   ((1 << 17) - 1)
#define MAX_IMMED_ST    ((1 << 22) - 1)
#define MAX_IMMED_STX   ((1 << 17) - 1)


#define INSTRUCTION(x) (instructionLut[(x)])
#define REGISTER(x) (regNameLut[(x)])
#define L_CHILD_TYPE(p) ((p)->pChilds[0].nodeType)
#define R_CHILD_TYPE(p) ((p)->pChilds[1].nodeType)
#define NODE_TYPE(p) ((p)->nodeType)

#define L_CHILD_DVAL(p) ((p)->pChilds[0].nodeData.dVal)
#define R_CHILD_DVAL(p) ((p)->pChilds[1].nodeData.dVal)
#define NODE_DVAL(p) ((p)->nodeData.dVal)

#define L_CHILD_MEM_LOC(p) ((p)->pChilds[0].pSymbol->symbolContent_u.memoryLocation)
#define R_CHILD_MEM_LOC(p) ((p)->pChilds[1].pSymbol->symbolContent_u.memoryLocation)
#define NODE_MEM_LOC(p) ((p)->pSymbol->symbolContent_u.memoryLocation)

#define L_CHILD_OP_TYPE(p) ((OperatorType_et)((p)->pChilds[0].nodeData.dVal))
#define R_CHILD_OP_TYPE(p) ((OperatorType_et)((p)->pChilds[1].nodeData.dVal))

#define L_CHILD(p) ((p)->pChilds[0])
#define R_CHILD(p) ((p)->pChilds[1])
#define VALID_ALU_IMMED(x) ((x) <= MAX_IMMED_ALU)
#define VALID_LDI_IMMED(x) ((x) <= MAX_IMMED_LDI)
#define VALID_LD_IMMED(x) ((x) <= MAX_IMMED_LD)
#define VALID_ST_IMMED(x) ((x) <= MAX_IMMED_ST)
#define IS_IN_32BIT_RANGE(x) ((x) <= MAX_32BIT_RANGE)

#define IS_TERMINAL_NODE(x) (((x) == NODE_IDENTIFIER) || ((x) == NODE_INTEGER) || ((x) == NODE_CHAR) || ((x) == NODE_FLOAT))
#define IS_ALU_OPERATION(x) (((x) == OP_PLUS) || ((x) == OP_MINUS) || ((x) == OP_RIGHT_SHIFT) || ((x) == OP_LEFT_SHIFT) || ((x) == OP_MULTIPLY) || ((x) == OP_DIVIDE) || ((x) == OP_REMAIN))


#define TRACE_CODE


typedef struct
{
    reg_et regName;
    bool isFree;
} reg_state_st;

typedef struct
{
    OperatorType_et operatorType;
    OperatorType_et assignOpType;
    asm_instr_et asmInstruction;
} operator_pair_st;

static FILE *pAsmFile;
static reg_et ctxReg;
static reg_et dRegSave;
static reg_et lRegSave;
static reg_et rRegSave;

void emitComment(char *c)
{
#ifdef TRACE_CODE
    fprintf(pAsmFile, "; %s\n", c);
#endif
}

static int releaseReg(reg_et reg);

static reg_et getNextAvailableReg();

static int parseNode(TreeNode_st *pTreeNode);

static int parseNode2(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited);

static int generateCode(TreeNode_st *pTreeNode);

static reg_state_st regStateList[] =
        {
                {.regName = REG_R12, .isFree = true},
                {.regName = REG_R13, .isFree = true},
                {.regName = REG_R14, .isFree = true},
                {.regName = REG_R15, .isFree = true},
                {.regName = REG_R24, .isFree = true},
                {.regName = REG_R25, .isFree = true},
                {.regName = REG_R26, .isFree = true},
                {.regName = REG_R27, .isFree = true},
                {.regName = REG_R28, .isFree = true},
                {.regName = REG_R29, .isFree = true},
                {.regName = REG_R30, .isFree = true},
                {.regName = REG_R31, .isFree = true}
        };

static operator_pair_st operatorLut[] =
        {
                {.operatorType = OP_PLUS, .assignOpType = OP_PLUS_ASSIGN, .asmInstruction = INST_ADD},
                {.operatorType = OP_MINUS, .assignOpType = OP_MINUS_ASSIGN, .asmInstruction = INST_SUB},
                {.operatorType = OP_RIGHT_SHIFT, .assignOpType = OP_RIGHT_SHIFT_ASSIGN, .asmInstruction = INST_RR},
                {.operatorType = OP_LEFT_SHIFT, .assignOpType = OP_LEFT_SHIFT_ASSIGN, .asmInstruction = INST_RL},
                {.operatorType = OP_BITWISE_AND, .assignOpType = OP_BITWISE_AND_ASSIGN, .asmInstruction = INST_AND},
                {.operatorType = OP_BITWISE_NOT, .assignOpType = -1, .asmInstruction = INST_NOT},
                {.operatorType = OP_BITWISE_OR, .assignOpType = OP_BITWISE_OR_ASSIGN, .asmInstruction = INST_OR},
                {.operatorType = OP_BITWISE_XOR, .assignOpType = OP_BITWISE_XOR_ASSIGN, .asmInstruction = INST_XOR},

        };


#define OPERATOR_LUT_SIZE (sizeof(operatorLut) / sizeof(operator_pair_st))
#define NOF_SCRATCH_REGISTER (sizeof(regStateList) / sizeof(reg_state_st))


static asm_instr_et mapInstructionFromOperator(OperatorType_et opType)
{
    size_t i;

    for (i = 0; i < OPERATOR_LUT_SIZE; ++i)
    {
        if (operatorLut[i].operatorType == opType)
            return operatorLut[i].asmInstruction;
    }

    return INST_NOP;
}

static asm_instr_et mapInstructionFromAssignOp(OperatorType_et opType)
{
    size_t i;

    for (i = 0; i < OPERATOR_LUT_SIZE; ++i)
    {
        if (operatorLut[i].assignOpType == opType)
            return operatorLut[i].asmInstruction;
    }

    return INST_NOP;
}

int executeCodeGeneration(TreeNode_st *pTreeRoot, const char *pDestFile)
{
    if (!pTreeRoot || !pDestFile)
        return -EINVAL;

    pAsmFile = fopen(pDestFile, "w");
    if (!pAsmFile)
        return -EIO;

    return 0;
}

static int generateCode(TreeNode_st *pTreeNode)
{
    TreeNode_st *pSib;
    int ret = parseNode2(pTreeNode, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
    if (ret < 0)
        return ret;

    pSib = pTreeNode->pSibling;
    while (pSib)
    {
        parseNode2(pSib, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
        pSib = pSib->pSibling;
    }

    return 0;
}

/// \brief This function allows to generate code for ALU instructions
/// \param instructionType Enum representing the ALU instruction to emit
/// \param isImed Boolean value that defines if the right hand operand should be an immediate or from memory
/// \param imedValue If isImed is set to true, this value is used as the right hand operand
/// \param resultReg Register to put the operation result into
/// \param leftOperand Left side operand
/// \param rightOperand Right side operand, only used if isImed is equal to false
/// \return -EINVAL if invalid arguments are passed, -EPERM if the combination of arguments is invalid, 0 on success
static int emitAluInstruction(asm_instr_et instructionType,
                              uint8_t isImed,
                              uint32_t imedValue,
                              reg_et resultReg,
                              reg_et leftOperand,
                              reg_et rightOperand)
{

    //NOT instruction can't use immediate as a parameter
    if ((instructionType == INST_NOT) && (isImed))
        return -EPERM;

    if ((isImed) && (rightOperand != REG_NONE))
        return -EPERM;

    if (isImed)
    {
        if (instructionType == INST_CMP)
        {
            fprintf(pAsmFile, "%s %s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(leftOperand),
                    imedValue);
        }
        else
        {
            fprintf(pAsmFile, "%s %s,%s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(resultReg),
                    REGISTER(leftOperand),
                    imedValue);
        }
    }
    else
    {
        if (instructionType == INST_CMP)
        {
            fprintf(pAsmFile, "%s %s,%s\n",
                    INSTRUCTION(instructionType),
                    REGISTER(leftOperand),
                    REGISTER(rightOperand));
        }
        else
        {
            if (rightOperand == REG_NONE)
            {
                fprintf(pAsmFile, "%s %s,%s\n",
                        INSTRUCTION(instructionType),
                        REGISTER(resultReg),
                        REGISTER(leftOperand));
            }
            else
            {
                fprintf(pAsmFile, "%s %s,%s,%s\n",
                        INSTRUCTION(instructionType),
                        REGISTER(resultReg),
                        REGISTER(leftOperand),
                        REGISTER(rightOperand));
            }
        }
    }

    return 0;
}

/// \brief This function emits to the destination assembly file a memory type instruction (LD, LDI, LDX, ST, STX)
/// \param instructionType Enum representing the instruction to generate assembly for
/// \param reg Register used for the memory operation
/// \param idx Index register used for LDX and STX operations
/// \param dVal Immediate value used for the memory operation
/// \return -EINVAL if invalid arguments are passed, -EPERM if the passed instruction is not a valid memory instruction
/// returns 0 on success.
static int emitMemoryInstruction(asm_instr_et instructionType, reg_et reg, reg_et idx, uint32_t dVal)
{
    if (reg >= REG_NONE)
        return -EINVAL;

    switch (instructionType)
    {
        case INST_LD:

            if (VALID_LD_IMMED(dVal))
            {
                fprintf(pAsmFile, "%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_LD);
            }
            else
            {
                //Emit LDI of dVal to a Register X
                //Emit LDX reg, register X, 0
                reg_et auxReg = getNextAvailableReg();
                emitMemoryInstruction(INST_LDI, auxReg, REG_NONE, dVal);
                emitMemoryInstruction(INST_LDX, reg, auxReg, 0);
                releaseReg(auxReg);
            }
            break;

        case INST_LDI:

            if (VALID_LDI_IMMED(dVal))
            {
                fprintf(pAsmFile, "%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_LD);
            }
            else
                loadImm32(dVal, reg);
            break;

        case INST_ST:

            if (VALID_ST_IMMED(dVal))
            {
                fprintf(pAsmFile, "%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_ST);
            }
            else
            {
                //Emit LDI of dVal to a Register X
                //Emit LDX reg, register X, 0
                reg_et auxReg = getNextAvailableReg();
                emitMemoryInstruction(INST_LDI, auxReg, REG_NONE, dVal);
                emitMemoryInstruction(INST_STX, reg, auxReg, 0);
                releaseReg(auxReg);
            }
            break;

        case INST_LDX:
        case INST_STX:

            if (idx >= REG_NONE)
                return -EINVAL;

            fprintf(pAsmFile, "%s %s,%s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(reg),
                    REGISTER(idx),
                    dVal & MAX_IMMED_LDX);
            break;

        default:
            return -EPERM;
    }


    // if ((instructionType == INST_LD) || (instructionType == INST_LDI) || (instructionType == INST_ST))
    // {
    //     fprintf(pAsmFile, "%s %s,#%d\n",
    //             INSTRUCTION(instructionType),
    //             REGISTER(reg),
    //             dVal & MAX_IMMED_LDI);
    // }

    return 0;
}

/// \brief Considering the LDI instruction only allows to load values up to 2^22 - 1, some arithmetic must be used in
/// order to use immediate values larger than this. This function generates boilerplate code to perform this operation
/// \param dVal Value of the immediate to load
/// \param destReg Register that the immediate should be loaded to
/// \return -ENOMEM if unable to acquire a register to perform arithmetic operations on, other negative errors if unable
/// to emit operations or release the working register, returns 0 on success
static int loadImm32(uint32_t dVal, reg_et destReg)
{
    int ret;
    reg_et workingReg;
    uint16_t lw16 = dVal & 0xFFFF;
    uint16_t hp16 = (dVal >> 16) & 0xFFFF;

    workingReg = getNextAvailableReg();
    if (workingReg == REG_NONE)
        return -ENOMEM;

    ret = emitMemoryInstruction(INST_LDI, workingReg, REG_NONE, hp16);
    ret |= emitAluInstruction(INST_RL, true, 16, workingReg, workingReg, REG_NONE);
    ret |= emitAluInstruction(INST_OR, true, lw16, destReg, workingReg, REG_NONE);
    ret |= releaseReg(workingReg);

    return ret;
}

static int generateChildNodes(TreeNode_st* pTreeNode)
{
    if (!pTreeNode)
        return -EINVAL;

    for (size_t i = 0; i < pTreeNode->childNumber; ++i)
    {
        generateCode(&pTreeNode->pChilds[i]);
    }

    return 0;
}

static int generateAluOperation(TreeNode_st *pTreeNode, reg_et destReg)
{
    uint32_t memAddr;
    uint32_t leftAddr;
    uint32_t rightAddr;
    reg_et lReg = getNextAvailableReg();
    reg_et rReg = getNextAvailableReg();
    OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;
    asm_instr_et asmInstruction = mapInstructionFromOperator(opType);

    if ((L_CHILD_TYPE(pTreeNode) == NODE_INTEGER) && (R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER))
    {
        memAddr = R_CHILD_MEM_LOC(pTreeNode);

        emitMemoryInstruction(INST_LD, rReg, REG_NONE, memAddr);

        //Since ALU always performs Immed - RLeft, for performing subtractions with immediate, instead of a SUB
        //an ADD with the immediate negated is performed
        if (opType == OP_MINUS)
        {
            if (VALID_ALU_IMMED(L_CHILD_DVAL(pTreeNode)))
            {
                emitAluInstruction(INST_ADD, true, -L_CHILD_DVAL(pTreeNode), destReg, rReg, REG_NONE);
            }
            else
            {
                emitMemoryInstruction(INST_LDI, lReg, REG_NONE, -L_CHILD_DVAL(pTreeNode));
                emitAluInstruction(INST_ADD, false, 0, destReg, lReg, rReg);
            }
        }
        else
        {
            if (VALID_ALU_IMMED(L_CHILD_DVAL(pTreeNode)))
            {
                emitAluInstruction(asmInstruction, true, L_CHILD_DVAL(pTreeNode), destReg, rReg, REG_NONE);
            }
            else
            {
                emitMemoryInstruction(INST_LDI, lReg, REG_NONE, L_CHILD_DVAL(pTreeNode));
                emitAluInstruction(asmInstruction, false, 0, destReg, lReg, rReg);
            }
        }
    }
    else if ((L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER) && (R_CHILD_TYPE(pTreeNode) == NODE_INTEGER))
    {
        memAddr = L_CHILD_MEM_LOC(pTreeNode);
        emitMemoryInstruction(INST_LD, lReg, REG_NONE, memAddr);

        if (VALID_ALU_IMMED(R_CHILD_DVAL(pTreeNode)))
        {
            emitAluInstruction(asmInstruction, true, R_CHILD_DVAL(pTreeNode), destReg, lReg, REG_NONE);
        }
        else
        {
            emitMemoryInstruction(INST_LDI, lReg, REG_NONE, R_CHILD_DVAL(pTreeNode));
            emitAluInstruction(asmInstruction, false, 0, destReg, lReg, rReg);
        }
    }
    else if (L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER && R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
    {
        leftAddr = L_CHILD_MEM_LOC(pTreeNode);
        rightAddr = R_CHILD_MEM_LOC(pTreeNode);

        emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
        emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
        emitAluInstruction(asmInstruction, false, 0, destReg, lReg, rReg);
    }
    else
    {
        LOG_ERROR("Un-Implemented condition!\n");
    }

    releaseReg(lReg);
    releaseReg(rReg);

    return 0;
}


static int generateAssignOperation(OperatorType_et operatorType, TreeNode_st *pTreeNode, reg_et destReg)
{
    uint32_t memAddr;

    switch (operatorType)
    {
        case OP_ASSIGN:
        {
            if (R_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
            {
                emitMemoryInstruction(INST_LDI, destReg, REG_NONE, R_CHILD_DVAL(pTreeNode));
                emitMemoryInstruction(INST_ST, destReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
            }
            else if (R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
            {
                emitMemoryInstruction(INST_LD, destReg, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
                emitMemoryInstruction(INST_ST, destReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
            }
            break;
        }
        case OP_PLUS_ASSIGN:
        case OP_MINUS_ASSIGN:
        case OP_LEFT_SHIFT_ASSIGN:
        case OP_RIGHT_SHIFT_ASSIGN:
        case OP_BITWISE_AND_ASSIGN:
        case OP_BITWISE_OR_ASSIGN:
        case OP_BITWISE_XOR_ASSIGN:
            //case OP_MULTIPLY_ASSIGN:    Not Yet Handled!
            //case OP_DIVIDE_ASSIGN:      Not Yet Handled!
            //case OP_MODULUS_ASSIGN:     Not Yet Handled!

            if (R_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
            {
                emitMemoryInstruction(INST_LD, destReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
                emitAluInstruction(mapInstructionFromAssignOp(operatorType), true, R_CHILD_DVAL(pTreeNode), destReg,
                                   destReg, REG_NONE);
            }
            else if (R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
            {
                uint32_t tempReg1 = getNextAvailableReg();
                emitMemoryInstruction(INST_LD, tempReg1, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
                emitMemoryInstruction(INST_LD, destReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
                emitAluInstruction(mapInstructionFromAssignOp(operatorType), false, 0, destReg, destReg, tempReg1);
                releaseReg(tempReg1);
            }

            emitMemoryInstruction(INST_ST, destReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
            break;
        default:
            LOG_ERROR("Un-Implemented assignment operation!\n");
    }

    return 0;
}

static int parseOperatorNode(TreeNode_st *pTreeNode, reg_et dReg)
{
    OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;

    switch (opType)
    {
        case OP_PLUS:
        case OP_MINUS:
        case OP_RIGHT_SHIFT:
        case OP_LEFT_SHIFT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_REMAIN:
            generateAluOperation(pTreeNode, dReg);
            break;
        case OP_GREATER_THAN:
            break;
        case OP_LESS_THAN_OR_EQUAL:
            break;
        case OP_GREATER_THAN_OR_EQUAL:
            break;
        case OP_LESS_THAN:
            break;
        case OP_EQUAL:
            break;
        case OP_NOT_EQUAL:
            break;
        case OP_LOGICAL_AND:
            break;
        case OP_LOGICAL_OR:
            break;
        case OP_LOGICAL_NOT:
            break;
        case OP_BITWISE_AND:
            break;
        case OP_BITWISE_NOT:
            break;
        case OP_BITWISE_OR:
            break;
        case OP_BITWISE_XOR:
            break;
        case OP_ASSIGN:
            break;
        case OP_PLUS_ASSIGN:
            break;
        case OP_MINUS_ASSIGN:
            break;
        case OP_MODULUS_ASSIGN:
            break;
        case OP_LEFT_SHIFT_ASSIGN:
            break;
        case OP_RIGHT_SHIFT_ASSIGN:
            break;
        case OP_BITWISE_AND_ASSIGN:
            break;
        case OP_BITWISE_OR_ASSIGN:
            break;
        case OP_BITWISE_XOR_ASSIGN:
            break;
        case OP_MULTIPLY_ASSIGN:
            break;
        case OP_DIVIDE_ASSIGN:
            break;
        case OP_SIZEOF:
            break;
        case OP_NEGATIVE:
            break;
    }

    return 0;
}


// static int parseNode(TreeNode_st *pTreeNode)
// {
//     reg_et lReg = REG_NONE;
//     reg_et rReg = REG_NONE;
//     reg_et dReg = getNextAvailableReg();
//     OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;

//     if (!pTreeNode)
//         return -EINVAL;

//     switch (pTreeNode->nodeType)
//     {
//         case NODE_SIGN:
//             break;
//         case NODE_MISC:
//             break;
//         case NODE_VISIBILITY:
//             break;
//         case NODE_MODIFIER:
//             break;
//         case NODE_TYPE:
//             break;
//         case NODE_OPERATOR:                

//                 //Gen Code for Left Child If its not a terminal node
//                 if (!IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode)))
//                 {
//                     generateCode(&pTreeNode->pChilds[0]);
//                     lReg = ctxReg;
//                 }

                
//                 //Gen Code for Right Child If its not terminal node
//                 if (!IS_TERMINAL_NODE(R_CHILD_TYPE(pTreeNode)))
//                 {
//                     generateCode(&pTreeNode->pChilds[1]);
//                     rReg = ctxReg;
//                 }
                

//                 //If One Is a terminal node and the other Is Not 
//                 if (((IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode))) &&  (!IS_TERMINAL_NODE(R_CHILD_TYPE(pTreeNode)))) || 
//                 ((IS_TERMINAL_NODE(R_CHILD_TYPE(pTreeNode))) &&  (!IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode)))))
//                 {
//                     //Falta o caso em que é outro tipo de não terminais (NODE_POINTER;... )
//                     //IDEIA: Talvez chamar aqui o parseNode e colocar estes emits nos templates dos INTEGER, IDENTIFIER, etc 
//                     if (L_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
//                     {
//                         lReg = ctxReg;
//                         //Foi necessário colocar aqui a mesma verificação que está na func generateALUOperation 
//                         if(opType == OP_MINUS)
//                         {
//                             emitAluInstruction(INST_ADD, true, -L_CHILD_DVAL(pTreeNode), dReg, lReg, REG_NONE);
//                         }
//                         else
//                             emitAluInstruction(mapInstructionFromOperator(opType), true, L_CHILD_DVAL(pTreeNode), dReg, lReg, REG_NONE);
//                         ctxReg = dReg;
//                     }
//                     else if (R_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
//                     {   
//                         lReg = ctxReg;
//                         emitAluInstruction(mapInstructionFromOperator(opType), true, R_CHILD_DVAL(pTreeNode), dReg, lReg, REG_NONE);
//                         ctxReg = dReg;  
//                     }
//                     else if (R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
//                     {
//                         uint32_t memAddr = R_CHILD_MEM_LOC(pTreeNode);
//                         emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
//                         ctxReg = dReg;
//                         rReg = dReg;
//                         emitAluInstruction(mapInstructionFromOperator(opType), false, 0, dReg, lReg, rReg);
//                     }
//                     else if(L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
//                     {
//                         uint32_t memAddr = L_CHILD_MEM_LOC(pTreeNode);
//                         emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
//                         ctxReg = dReg;
//                         lReg = dReg;
//                         emitAluInstruction(mapInstructionFromOperator(opType), false, 0, dReg, lReg, rReg);
//                     }
                    
//                 }
//                 //If both childs are terminals, parse the node to generate the ALU operation
//                 else if (IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode)) && IS_TERMINAL_NODE(R_CHILD_TYPE(pTreeNode)))
//                 {
//                     parseOperatorNode(pTreeNode, dReg);
//                     ctxReg = dReg;
//                 }
//                 //If both childs are Non-Terminals
//                 else
//                 {
//                     rReg = ctxReg;
//                     emitAluInstruction(mapInstructionFromOperator(opType), false, 0, dReg, lReg, rReg);
//                     ctxReg = dReg;
//                 }

//             break;
//         case NODE_TERNARY:
//             break;
//         case NODE_IDENTIFIER:
//             break;
//         case NODE_STRING:
//             break;
//         case NODE_INTEGER:
//             break;
//         case NODE_FLOAT:
//             break;
//         case NODE_CHAR:
//             break;
//         case NODE_STRUCT:
//             break;
//         case NODE_IF:
//             break;
//         case NODE_WHILE:
//             break;
//         case NODE_DO_WHILE:
//             break;
//         case NODE_RETURN:
//             break;
//         case NODE_CONTINUE:
//             break;
//         case NODE_BREAK:
//             break;
//         case NODE_GOTO:
//             break;
//         case NODE_LABEL:
//             break;
//         case NODE_SWITCH:
//             break;
//         case NODE_CASE:
//             break;
//         case NODE_DEFAULT:
//             break;
//         case NODE_REFERENCE:
//             break;
//         case NODE_POINTER:
//             break;
//         case NODE_POINTER_CONTENT:
//             break;
//         case NODE_TYPE_CAST:
//             break;
//         case NODE_POST_DEC:
//             break;
//         case NODE_PRE_DEC:
//             break;
//         case NODE_POST_INC:
//             break;
//         case NODE_PRE_INC:
//             break;
//         case NODE_VAR_DECLARATION:
//             break;
//         case NODE_ARRAY_DECLARATION:
//             break;
//         case NODE_ARRAY_INDEX:
//             break;
//         case NODE_FUNCTION:
//             break;
//         case NODE_FUNCTION_CALL:
//             break;
//         case NODE_PARAMETER:
//             break;
//         case NODE_NULL:
//             break;
//         case NODE_END_SCOPE:
//             break;
//         case NODE_START_SCOPE:
//             break;
//     }

//     return 0;
// }




//IDEIA: O Parsenode2 recebe também o nó do pai e uma variavel que diz se o nó atual está à esquerda ou direita do pai....
//Assim criavam-se templates dos INTEGER,IDs, etc no "Case integer"/"Case ID", etc


/// \brief Different ParsesNode because it allows to parse the terminal nodes (INTEGER, IDENTIFIER, POINTER_CONTENT,..) in their own "case" of the big switch
/// Although, it has to receive additional params  
/// \param pCurrentNode Pointer to the current Node to be parsed
/// \param parentNodeType The type of the parent of the currentNode
/// \param isLeftInherited 1 if the currentNode is at the left of its parent, 0 if its at the right of the parent
/// \return 0 if success; -EINVAL in pCurrentNode is NULL
static int parseNode2(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited)
{
    reg_et lReg;
    reg_et rReg; 
    reg_et dReg;
    
    OperatorType_et CurrentNodeOpType = (OperatorType_et) pCurrentNode->nodeData.dVal;

    if(!IS_TERMINAL_NODE(NODE_TYPE(pCurrentNode)))
        dReg = getNextAvailableReg();
    else
    {
        dReg = dRegSave;
        lReg = lRegSave;
        rReg = rRegSave;
    }
    

    if (!pCurrentNode)
        return -EINVAL;

    switch (pCurrentNode->nodeType)
    {
        case NODE_SIGN:
            break;
        case NODE_MISC:
            break;
        case NODE_VISIBILITY:
            break;
        case NODE_MODIFIER:
            break;
        case NODE_TYPE:
            break;
        case NODE_OPERATOR:                

            
            if (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Left Child If its not a terminal node
                generateCode(&pCurrentNode->pChilds[0]);
                lReg = ctxReg;
            }
            
            
            if (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Right Child If its not terminal node
                generateCode(&pCurrentNode->pChilds[1]);
                rReg = ctxReg;
            }               

            

            if ((IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))) && (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))))
            {
                //If Right child is a terminal node and Left child is not
                dRegSave = dReg;
                lRegSave = lReg;
                rRegSave = rReg;
                parseNode2(&pCurrentNode->pChilds[1], NODE_OPERATOR, CurrentNodeOpType, false); 
            }     
            else if ((IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))) &&  (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))))               
            {
                //If Left child is a terminal node and Right child is not
                dRegSave = dReg;
                lRegSave = lReg;
                rRegSave = rReg;
                parseNode2(&pCurrentNode->pChilds[0], NODE_OPERATOR, CurrentNodeOpType, true);                   
            }                 
            else if (IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)) && IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //If both childs are terminals, parse the node to generate the ALU operation
                parseOperatorNode(pCurrentNode, dReg);
                ctxReg = dReg;
            }           
            else
            {
                //If both childs are Non-Terminals
                rReg = ctxReg;
                emitAluInstruction(mapInstructionFromOperator(CurrentNodeOpType), false, 0, dReg, lReg, rReg);
                ctxReg = dReg;
            }

            break;
        case NODE_TERNARY:
            break;
        case NODE_IDENTIFIER:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if(parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                if(isLeftInherited)
                {
                    uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                    emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                    ctxReg = dReg;
                    lReg = dReg;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, rReg);
                }
                else
                {
                    uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                    emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                    ctxReg = dReg;
                    rReg = dReg;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, rReg);
                }
            }
            //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            // else if(parentNodeType == NODE_OPERATOR && IS_ASSING_OPERATION(parentOperatorType))
            // {

            // }

            break;
        case NODE_STRING:
            break;
        case NODE_INTEGER:

            //If the integer is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if(parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                
                lReg = ctxReg;
                //Foi necessário colocar aqui a mesma verificação que está na func generateALUOperation (se for operaçao menos trocar para ADD e negar o imediato)
                if(parentOperatorType == OP_MINUS)
                {
                    long int immVal = pCurrentNode->nodeData.dVal;
                    //immVal -= immVal;
                    emitAluInstruction(INST_ADD, true, -immVal, dReg, lReg, REG_NONE);
                }
                else
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), true, pCurrentNode->nodeData.dVal, dReg, lReg, REG_NONE);

                ctxReg = dReg;
                
                
            }
            //If the integer is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            // else if (parentNodeType == NODE_OPERATOR && IS_ASSING_OPERATION(parentOperatorType))
            // {

            // }

            break;
        case NODE_FLOAT:
            break;
        case NODE_CHAR:
            break;
        case NODE_STRUCT:
            break;
        case NODE_IF:
            break;
        case NODE_WHILE:
            break;
        case NODE_DO_WHILE:
            break;
        case NODE_RETURN:
            break;
        case NODE_CONTINUE:
            break;
        case NODE_BREAK:
            break;
        case NODE_GOTO:
            break;
        case NODE_LABEL:
            break;
        case NODE_SWITCH:
            break;
        case NODE_CASE:
            break;
        case NODE_DEFAULT:
            break;
        case NODE_REFERENCE:
            break;
        case NODE_POINTER:
            break;
        case NODE_POINTER_CONTENT:
            break;
        case NODE_TYPE_CAST:
            break;
        case NODE_POST_DEC:
            break;
        case NODE_PRE_DEC:
            break;
        case NODE_POST_INC:
            break;
        case NODE_PRE_INC:
            break;
        case NODE_VAR_DECLARATION:
            break;
        case NODE_ARRAY_DECLARATION:
            break;
        case NODE_ARRAY_INDEX:
            break;
        case NODE_FUNCTION:
            break;
        case NODE_FUNCTION_CALL:
            break;
        case NODE_PARAMETER:
            break;
        case NODE_NULL:
            break;
        case NODE_END_SCOPE:
            break;
        case NODE_START_SCOPE:
            break;
    }

    return 0;
}












/// \brief This function gets the first available register of the working register list
/// \return Register number or REG_NONE if no register is available
static reg_et getNextAvailableReg()
{
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {
        if (regStateList[i].isFree)
        {
            regStateList[i].isFree = false;
            return regStateList[i].regName;
        }
    }

    LOG_ERROR("No register available!\n");
    return REG_NONE;
}

/// \brief This function tries to release a previously allocated register
/// \param reg Enum representing the register that should be released
/// \return -EPERM if the passed register is already free, -ENODATA if the passed register was not found on the register
/// list, returns 0 on success
static int releaseReg(reg_et reg)
{
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {
        if (regStateList[i].regName == reg)
        {
            if (regStateList[i].isFree)
            {
                LOG_ERROR("Trying to release already freed register!\n");
                return -EPERM;
            }

            regStateList[i].isFree = true;
            return 0;
        }
    }

    return -ENODATA;
}





















void codeGenerationTestUnit()
{
    reg_et reg;
    TreeNode_st treeRoot = {0};
    TreeNode_st* pLeftChild;
    TreeNode_st* pRightChild;
    TreeNode_st* pLeftGrandChild;
    TreeNode_st* pRightGrandChild;
    TreeNode_st* _pLeftGrandChild;
    TreeNode_st* _pRightGrandChild;
    TreeNode_st* pLeftGrandChild_;
    TreeNode_st* pRightGrandChild_;
    SymbolEntry_st symbolEntry = {.symbolContent_u.memoryLocation = 0x20};
    SymbolEntry_st symbolEntry2 = {.symbolContent_u.memoryLocation = 0xF};
    SymbolEntry_st symbolEntry3 = {.symbolContent_u.memoryLocation = 0xAB};
    SymbolEntry_st symbolEntry4 = {.symbolContent_u.memoryLocation = 0xCD};

    //reg = getNextAvailableReg();
    pAsmFile = stdout;

    emitComment("--> Asm File");

//    Un-Comment for testing ALU operations of type L:Immediate R:Variable
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_BITWISE_XOR;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_INTEGER);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

//    pLeftChild->nodeData.dVal = 0xFAFEDEAD;
//    pRightChild->pSymbol = &symbolEntry;

    //generateAluOperation(OP_PLUS, &treeRoot, reg);
    //  generateAluOperation(OP_MINUS, &treeRoot, reg);

//    Un-Comment for testing ALU operations of type  L:Variable R:Immediate
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_PLUS;
//
//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);
//
//    pLeftChild->pSymbol = &symbolEntry;
//    pRightChild->nodeData.dVal = 0xFAFEDEAD;
//
//    generateAluOperation(OP_PLUS, &treeRoot, reg);
//    generateAluOperation(OP_MINUS, &treeRoot, reg);
// generateAluOperation(treeRoot.nodeData.dVal, &treeRoot, reg);

    //ASSIGN TESTS
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_MINUS_ASSIGN;
//
//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);
//
//    pRightChild->nodeData.dVal = 0x1;
//    //pRightChild->pSymbol = &symbolEntry2; //0xF
//    pLeftChild->pSymbol = &symbolEntry;   //0x20
//
//
//    generateAssignOperation(treeRoot.nodeData.dVal, &treeRoot, reg);








/* TEST 0 
 * M (Mem)-> Means it is an identifier 
 *
 *              +
 *             / \
 *            +   1
 *           / \
 *       M:32   #2
 */

//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_PLUS;

//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

//    pLeftChild->nodeData.dVal = OP_PLUS;
//    pRightChild->nodeData.dVal = 1;

//    NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
//    NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

//    pLeftGrandChild->pSymbol = &symbolEntry;
//    pRightGrandChild->nodeData.dVal = 2;

/*  TEST 1
 *                 +
 *              /     \
 *             /       \
 *            /         \
 *           +           -    
 *          / \        /   \
 *   Mem:0x20 #2  Mem:0xF  #10
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;


/* TEST 2
 *                  +
 *                /   \ 
 *               /     \ 
 *              /       \
 *             /         \    
 *            +           -
 *           / \        /   \ 
 *          /   #2    M:0xF  #10      
 *         +                
 *       /   \              
 *   M:0xAB M:0xCD    
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;

    // NodeAddNewChild(pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 3
 *                  +
 *                /   \ 
 *               /     \ 
 *              /       \
 *             /         \    
 *            +           -
 *           / \        /   \ 
 *          / M:0x20  #10  M:0xF
 *         +                
 *       /   \              
 *   M:0xAB M:0xCD    
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_IDENTIFIER);

    // pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // pRightGrandChild->pSymbol = &symbolEntry;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_IDENTIFIER);

    // _pLeftGrandChild->nodeData.dVal = 10;
    // _pRightGrandChild->pSymbol = &symbolEntry2;
    

    // NodeAddNewChild(pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 4
 *                  -
 *                /   \  
 *               /     \ 
 *              /       \
 *             /         \
 *            -           -
 *           / \         / \  
 *     M:0x20   \   Mem:0xF #10 
 *               -         
 *              / \          
 *         M:0xAB M:0xCD      
 *                 
 */


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_MINUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;

    // NodeAddNewChild(pRightGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 5
 *              +
 *             / \
 *            +   \
 *           / \   \
 *   Mem:0x20  #2   \
 *                   -
 *                  / \
 *                 +   Mem:0xF
 *                / \
 *         Mem:0XAB Mem:0xCD        
 */                     


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_IDENTIFIER);

    // _pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // _pRightGrandChild->pSymbol = &symbolEntry2;

    // NodeAddNewChild(_pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(_pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;




/* TEST 6
 *              +
 *             / \
 *            +   \
 *           / \   \
 *      M:0x20 #2   \
 *                   -
 *                  / \
 *               #20   \ 
 *                      +
 *                    /   \
 *                  0XAB  0xCD        
 */                     


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

    // _pLeftGrandChild->nodeData.dVal = 20;
    // _pRightGrandChild->nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(_pRightGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(_pRightGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;



/* TEST 7
                     -
                    / \
                  /     \
                /         \
              /             \
            +                 -
          /  \               /  \
        /      \            /    \
      -         +         #255     -
     / \       / \                / \
    /   \     /   \              /   \
 M:0xF #32  M:0xAB M:0xCD      #42  M:0x20         
      
 */


// TreeNode_st* pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;    

//     treeRoot.nodeType = NODE_OPERATOR;
//     treeRoot.nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

//     pLeftChild->nodeData.dVal = OP_PLUS;
//     pRightChild->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
//     NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

//     pLeftGrandChild->nodeData.dVal = OP_MINUS;   //1º OP da ultima linha
//     pRightGrandChild->nodeData.dVal = OP_PLUS;   //2º OP da ultima linha

//     NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
//     NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

//     _pLeftGrandChild->nodeData.dVal = 255;
//     _pRightGrandChild->nodeData.dVal = OP_MINUS;   //3º OP da ultima linha

//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

//     pThirdLevelChild_1->pSymbol = &symbolEntry2;
//     pThirdLevelChild_2->nodeData.dVal = 32;

//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_IDENTIFIER);

//     pThirdLevelChild_3->pSymbol = &symbolEntry3;
//     pThirdLevelChild_4->pSymbol = &symbolEntry4;

//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_INTEGER);
//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_IDENTIFIER);

//     pThirdLevelChild_5->nodeData.dVal = 42;
//     pThirdLevelChild_6->pSymbol = &symbolEntry;



/* TEST 8
                                -
                               / \
                             /     \
                           /         \
                         /             \
                        +                 -
                      /  \               /  \
                    /      \            /    \
                  -         +         #255     -
                 / \       / \                / \
                /   \     /   \              /   \
            M:0xF #32  M:0xAB  -          M:0x20  + 
                              / \                / \
                            /     \             /   \        
                          #20      +           -     M:0xAB
                                  / \         / \  
                                 /   \       /   \
                               0xAB  0xCD   #1  M:0xF      
*/
TreeNode_st *pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;
TreeNode_st *pFourthLevelChild_1, *pFourthLevelChild_2, *pFourthLevelChild_3, *pFourthLevelChild_4;
TreeNode_st *pFifthLevelChild_1, *pFifthLevelChild_2, *pFifthLevelChild_3, *pFifthLevelChild_4;     

    treeRoot.nodeType = NODE_OPERATOR;
    treeRoot.nodeData.dVal = OP_MINUS;

    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    pLeftChild->nodeData.dVal = OP_PLUS;
    pRightChild->nodeData.dVal = OP_MINUS;

    NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

    pLeftGrandChild->nodeData.dVal = OP_MINUS;  
    pRightGrandChild->nodeData.dVal = OP_PLUS;   

    NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

    _pLeftGrandChild->nodeData.dVal = 255;
    _pRightGrandChild->nodeData.dVal = OP_MINUS;  

    NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
    NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

    pThirdLevelChild_1->pSymbol = &symbolEntry2;
    pThirdLevelChild_2->nodeData.dVal = 32;

    NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
    NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_OPERATOR);

    pThirdLevelChild_3->pSymbol = &symbolEntry3;
    pThirdLevelChild_4->nodeData.dVal = OP_MINUS;

    NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_IDENTIFIER);
    NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_OPERATOR);

    pThirdLevelChild_5->pSymbol = &symbolEntry;
    pThirdLevelChild_6->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_3, NODE_OPERATOR);
    NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_4, NODE_IDENTIFIER);
    
    pFourthLevelChild_3->nodeData.dVal = OP_MINUS;
    pFourthLevelChild_4->pSymbol = &symbolEntry3;
    
    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_3, NODE_INTEGER);
    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_4, NODE_IDENTIFIER);
    
    pFifthLevelChild_3->nodeData.dVal = 1;
    pFifthLevelChild_4->pSymbol = &symbolEntry2;
    
    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_1, NODE_INTEGER);
    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_2, NODE_OPERATOR);

    pFourthLevelChild_1->nodeData.dVal = 20;
    pFourthLevelChild_2->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_1, NODE_IDENTIFIER);
    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_2, NODE_IDENTIFIER);

    pFifthLevelChild_1->pSymbol = &symbolEntry3;
    pFifthLevelChild_2->pSymbol = &symbolEntry4;
    
    
    
    
    generateCode(&treeRoot);

    //releaseReg(reg);

}

static int generateMultiplication()
{
    int ret = 0;

    // Init Regs to contain result and condition
    reg_et regResult, regCondition;
    ret = emitMemoryInstruction(INST_LDI, regResult, REG_NONE, 0);

    // Emit all 32 iterations
    for (size_t i = 0; i < 32; i++)
    {
        //Label = SKIP_MUL_ADD_BITi

        ret |= emitAluInstruction(INST_ADD, 1, 1, regCondition, REG_R5, REG_NONE);
        ret |= emitAluInstruction(INST_CMP, 1, 0, REG_NONE, regCondition, REG_NONE);
        // Emit BNE to label bellow
        ret |= emitAluInstruction(INST_ADD, 0, 0, regResult, regResult, REG_R4);
        // Emit Label
        ret |= emitAluInstruction(INST_RL, 1, 1, REG_R4, REG_R4, REG_NONE);
        ret |= emitAluInstruction(INST_RR, 1, 1, REG_R5, REG_R5, REG_NONE);
    }

    // Move result to return register
    ret |= emitMemoryInstruction(INST_LD, REG_R4, regResult, 0);
    return 0;
}

static int generateDivision()
{
    int ret = 0;

    reg_et regQuocient, regRemainder, regCondition, regTemp1, regTemp2;
    ret = emitMemoryInstruction(INST_LDI, regQuocient, REG_NONE, 0);
    ret |= emitMemoryInstruction(INST_LDI, regRemainder, REG_NONE, 0);

    for (size_t i = 0; i < 32; i++)
    {
        ret |= emitAluInstruction(INST_RR, 1, (31 - i), regTemp1, REG_R4, REG_NONE);
        ret |= emitAluInstruction(INST_AND, 1, 1, regTemp1, regTemp1, REG_NONE);
        ret |= emitAluInstruction(INST_RL, 1, 1, regTemp2, regRemainder, REG_NONE);
        ret |= emitAluInstruction(INST_OR, 0, 0, regRemainder, regTemp1, regTemp2);

        ret |= emitAluInstruction(INST_SUB, 0, 0, regCondition, regRemainder, REG_R5);
        // Emit BGE to label bellow
        ret |= emitAluInstruction(INST_SUB, 0, 0, regRemainder, regRemainder, REG_R5);
        ret |= emitMemoryInstruction(INST_LDI, regTemp1, 0, 1);
        ret |= emitAluInstruction(INST_RL, 1, (31 - i), regTemp1, regTemp1, REG_NONE);
        ret |= emitAluInstruction(INST_OR, 0, 0, regQuocient, regQuocient, regTemp1);

        // Emit label SKIP_DIV_BITi
    }

    // Load Quocient and Remainder to return registers
    ret |= emitMemoryInstruction(INST_LD, REG_R4, regQuocient, 0);
    ret |= emitMemoryInstruction(INST_LD, REG_R5, regRemainder, 0);

    return ret;
}