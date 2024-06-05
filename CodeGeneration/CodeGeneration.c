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

#define STACK_START_ADDR 0x1000 // Change this after

#define INSTRUCTION(x) (instructionLut[(x)])
#define REGISTER(x) (regNameLut[(x)])
#define L_CHILD_TYPE(p) ((p)->pChilds[0].nodeType)
#define R_CHILD_TYPE(p) ((p)->pChilds[1].nodeType)
#define NODE_TYPE(p) ((p)->nodeType)
#define NODE_CHILD_NUM(p) ((p)->childNumber)

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

#define IS_TERMINAL_NODE(x) (((x) == NODE_IDENTIFIER) || ((x) == NODE_INTEGER) || ((x) == NODE_CHAR) || ((x) == NODE_FLOAT) || ((x) == NODE_POINTER_CONTENT) || ((x) == NODE_REFERENCE) || ((x) == NODE_POST_INC) || ((x) == NODE_POST_DEC) || ((x) == NODE_PRE_INC) || ((x) == NODE_PRE_DEC) || ((x) == NODE_ARRAY_INDEX))
#define IS_ALU_OPERATION(x) (((x) == OP_PLUS) || ((x) == OP_MINUS) || ((x) == OP_RIGHT_SHIFT) || ((x) == OP_LEFT_SHIFT) || ((x) == OP_MULTIPLY) || ((x) == OP_DIVIDE) || ((x) == OP_REMAIN) || ((x) == OP_BITWISE_AND) || ((x) == OP_BITWISE_NOT) || ((x) == OP_BITWISE_OR) || ((x) == OP_BITWISE_XOR))
#define IS_ASSIGN_OPERATION(x) (((x) == OP_ASSIGN) || ((x) == OP_PLUS_ASSIGN) || ((x) == OP_MINUS_ASSIGN) || ((x) == OP_LEFT_SHIFT_ASSIGN) || ((x) == OP_RIGHT_SHIFT_ASSIGN) || ((x) == OP_BITWISE_AND_ASSIGN) || ((x) == OP_BITWISE_OR_ASSIGN) || ((x) == OP_BITWISE_XOR_ASSIGN) || ((x) == OP_MULTIPLY_ASSIGN) || ((x) == OP_DIVIDE_ASSIGN) || ((x) == OP_MODULUS_ASSIGN))
#define IS_BOOLEAN_OPERATION(x) (((x) == OP_GREATER_THAN) || ((x) == OP_LESS_THAN_OR_EQUAL) || ((x) == OP_GREATER_THAN_OR_EQUAL) || ((x) == OP_LESS_THAN) || ((x) == OP_EQUAL) || ((x) == OP_NOT_EQUAL) || ((x) == OP_LOGICAL_AND) || ((x) == OP_LOGICAL_OR) || ((x) == OP_LOGICAL_NOT))

#define IS_CONDITIONAL_NODE(x) (((x) == NODE_WHILE) || ((x) == NODE_SWITCH) || ((x) == NODE_CASE) || ((x) == NODE_DO_WHILE) || ((x) == NODE_IF))


#define LABEL(x) (labelLut[x])

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

static reg_et arrayIndexRegSave;
static reg_et dRegSave;
static reg_et lRegSave;
static reg_et rRegSave;


postinc_list_st* postIncList;
static bool delayPostIncDec = 0;

void emitComment(char *c)
{
#ifdef TRACE_CODE
    fprintf(pAsmFile, "; %s\n", c);
#endif
}

static int releaseReg(reg_et reg);

static reg_et getNextAvailableReg();

static void push(reg_et reg);

static void pop(reg_et reg);

static int parseNode(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited);

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

    {.operatorType = (OperatorType_et) OP_GREATER_THAN, .assignOpType = -1, .asmInstruction = INST_BGT},
    {.operatorType = (OperatorType_et) OP_LESS_THAN_OR_EQUAL, .assignOpType = -1, .asmInstruction = INST_BLE},
    {.operatorType = (OperatorType_et) OP_GREATER_THAN_OR_EQUAL, .assignOpType = -1, .asmInstruction = INST_BGE},
    {.operatorType = (OperatorType_et) OP_LESS_THAN, .assignOpType = -1, .asmInstruction = INST_BLT},
    {.operatorType = (OperatorType_et) OP_EQUAL, .assignOpType = -1, .asmInstruction = INST_BEQ},
    {.operatorType = (OperatorType_et) OP_NOT_EQUAL, .assignOpType = -1, .asmInstruction = INST_BNE},
    {.operatorType = (OperatorType_et) OP_LOGICAL_AND, .assignOpType = -1, .asmInstruction = INST_BEQ},
    {.operatorType = (OperatorType_et) OP_LOGICAL_OR, .assignOpType = -1, .asmInstruction = INST_BNE},
    {.operatorType = (OperatorType_et) OP_LOGICAL_NOT, .assignOpType = -1, .asmInstruction = INST_BEQ},
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

int executeCodeGeneration(TreeNode_st *pTreeRoot, FILE* pDestStream)
{
    if (!pTreeRoot || !pDestStream)
        return -EINVAL;

    pAsmFile = pDestStream;

    PostIncListInit();
    
    generateCode(pTreeRoot);


    return 0;
}

static int generateCode(TreeNode_st *pTreeNode)
{
    TreeNode_st *pSib;
    int ret = parseNode(pTreeNode, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
    if (ret < 0)
        return ret;

    pSib = pTreeNode->pSibling;
    while (pSib)
    {
        parseNode(pSib, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
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

    return 0;
}

static uint32_t labelCounters[LABEL_MAX] = {0};

static int emitLabelInstruction(label_et labelType, uint32_t count, char* nameLabel)
{
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;

    if(labelType != FUNCTION_NAME)
        fprintf(pAsmFile, "%s%u:\n",
                LABEL(labelType),
                count);
    else
        fprintf(pAsmFile, "%s:\n",
            nameLabel);
    
    return 0;
}

static uint32_t getPostIncLabelCounter(label_et labeltype)
{
    if (labeltype < WHILE_START || labeltype >= LABEL_MAX)
        return -EINVAL;

    return labelCounters[labeltype]++;
}

static uint32_t getLabelCounter(label_et labelType)
{
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;

    return labelCounters[labelType];
}

/// \brief this function emit the branch labels
static int emitBranchInstruction(asm_instr_et instructionType, label_et labelType, uint32_t counter)
{
   //CheckLabel type
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;

    if (instructionType < INST_BGT || instructionType > INST_BMI)
        return -EINVAL;

    if(counter < 0)
        return -EINVAL;

    fprintf(pAsmFile, "%s %s%u\n",
            INSTRUCTION(instructionType),
            LABEL(labelType),
            counter);

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


/// \brief Goes through the postIncList and emits all the increments of the addresses that were added to it
/// \param reg_et auxReg to perform operations
/// \return -ENODATA if list is empty
static int handlePostIncDecOperations(reg_et auxReg)
{

    delayPostIncDec = 0;

    if(postIncList->size <= 0)
        return -ENODATA;
    
    while (postIncList->size > 0) 
    {        
        list_item_st* current_item = &postIncList->savedAddr[postIncList->size - 1];
        emitMemoryInstruction(INST_LD, auxReg, REG_NONE, current_item->Addr);

        if(current_item->is_increment)
            emitAluInstruction(INST_ADD, true, 1, auxReg, auxReg, REG_NONE);
        else
            emitAluInstruction(INST_SUB, true, 1, auxReg, auxReg, REG_NONE);

        emitMemoryInstruction(INST_ST, auxReg, REG_NONE, current_item->Addr);

        PostIncListDelete(postIncList);
    }

    return 0;
}

/// \brief Places the memory location of the array[exp] in the register passed in the parameters
/// \param reg_et ArrayLocationReg to place the memory location of the array[exp] 
/// \param TreeNode_st pointer to the Array Node
/// \return -EINVAL if any argument is invalid
static int handleArrayIndexedExpressions(TreeNode_st *pTreeNode, reg_et ArrayLocationReg)
{
    reg_et IndexValReg;

    if (ArrayLocationReg >= REG_NONE)
        return -EINVAL;
    
    if(pTreeNode == NULL || (NODE_TYPE(pTreeNode) != NODE_ARRAY_INDEX))
        return -EINVAL;
    
    //If the node is not a terminal node, parse the left child node
    if(!IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode)))
    {
        parseNode(&L_CHILD(pTreeNode), NODE_ARRAY_INDEX, OP_NOT_DEFINED, true);
        //Get the reg alocated as dreg in the parseNode func
        IndexValReg = arrayIndexRegSave;
        emitMemoryInstruction(INST_LD, ArrayLocationReg, REG_NONE, NODE_MEM_LOC(pTreeNode));
        emitAluInstruction(INST_ADD, false, 0, ArrayLocationReg, IndexValReg, ArrayLocationReg);
        return 0;
    }
    else
    {
        if(L_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
        {
            emitMemoryInstruction(INST_LD, ArrayLocationReg, REG_NONE, NODE_MEM_LOC(pTreeNode));
            emitAluInstruction(INST_ADD, true, L_CHILD_DVAL(pTreeNode), ArrayLocationReg, ArrayLocationReg, REG_NONE);
        }
        else
        if(L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
        {
            reg_et tempReg = getNextAvailableReg();
            emitMemoryInstruction(INST_LD, ArrayLocationReg, REG_NONE, NODE_MEM_LOC(pTreeNode));
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
            releaseReg(tempReg);
        }
    }


    return 0;
}

static int generateImmediateAluOperation(TreeNode_st *pTreeNode, asm_instr_et asmInstruction,
                                         reg_et destReg, reg_et tempReg)
{
    // i = 1 if the integer is the left child
    uint8_t i = ((L_CHILD_TYPE(pTreeNode)) == NODE_INTEGER) ? 1 : 0;

    uint32_t addr = pTreeNode->pChilds[i].pSymbol->symbolContent_u.memoryLocation;

    //Gen Code for the Terminal Node that is not an INTEGER
    //Nodes with 2 constants will never exist 
    switch (pTreeNode->pChilds[i].nodeType)
    {
        case NODE_IDENTIFIER:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            break;
        case NODE_POINTER_CONTENT:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0);
            break;
        case NODE_REFERENCE:
            emitMemoryInstruction(INST_LDI, tempReg, REG_NONE, addr);
            break;
        case NODE_POST_INC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            //If an assign was detected earlier, add this addr to the list so that it can be incremented later on
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, addr); 
            break;
        case NODE_PRE_INC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
            emitMemoryInstruction(INST_ST, tempReg, 0, addr);
            break;
        case NODE_POST_DEC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            //If an assign was detected earlier, add this addr to the list so that it can be decremented later on
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, addr);           
            break;
        case NODE_PRE_DEC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, addr);
            emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
            emitMemoryInstruction(INST_ST, tempReg, 0, addr);         
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&pTreeNode->pChilds[i], tempReg);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }

    //now switch the i var to the INTEGER POSITION
    i = !i;

    //Since ALU always performs Immed - RLeft, for performing subtractions with immediate, instead of a SUB
    //an ADD with the immediate negated is performed and then we negate the result using R0_REG
    //Enters this if when the operation is a SUB and the integer is at the left
    if ((asmInstruction == INST_SUB) && (!i))
    {
        if (VALID_ALU_IMMED(L_CHILD_DVAL(pTreeNode)))
        {
            emitAluInstruction(INST_ADD, true, -L_CHILD_DVAL(pTreeNode), destReg, tempReg, REG_NONE);
            emitAluInstruction(INST_SUB, false, 0, destReg, REG_R0, destReg);

        }
        else //In case Immediate value is bigger then 16 bits
        {
            emitMemoryInstruction(INST_LDI, destReg, REG_NONE, -L_CHILD_DVAL(pTreeNode));
            emitAluInstruction(INST_ADD, false, 0, destReg, destReg, tempReg);
        }
    }
    else
    {
        if (pTreeNode->pChilds[i].nodeData.dVal <= MAX_IMMED_ALU)
        {
            emitAluInstruction(asmInstruction, true, pTreeNode->pChilds[i].nodeData.dVal, destReg, tempReg, REG_NONE);
        }
        else //In case Immediate value is bigger then 16 bits
        {
            emitMemoryInstruction(INST_LDI, destReg, REG_NONE, pTreeNode->pChilds[i].nodeData.dVal);
            emitAluInstruction(asmInstruction, false, 0, destReg, destReg, tempReg);
        }
    }


    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && (pTreeNode->pChilds[!i].nodeData.dVal == NODE_POST_INC))
    {
        emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
        emitMemoryInstruction(INST_ST, tempReg, 0, addr);
    }

    if(!delayPostIncDec && (pTreeNode->pChilds[!i].nodeData.dVal == NODE_POST_DEC))
    {
        emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
        emitMemoryInstruction(INST_ST, tempReg, 0, addr);
        delayPostIncDec = 0;
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
    bool post_inc_left = 0;
    bool post_inc_right = 0;

    int childPos = 0;
    bool is_postdec= 0;
    bool is_postinc= 0;

    if ((L_CHILD_TYPE(pTreeNode) == NODE_INTEGER) || (R_CHILD_TYPE(pTreeNode)) == NODE_INTEGER)
    {
        generateImmediateAluOperation(pTreeNode, asmInstruction, destReg, lReg);
        releaseReg(lReg);
        releaseReg(rReg);
        return 0;
    }

    leftAddr = L_CHILD_MEM_LOC(pTreeNode);
    rightAddr = R_CHILD_MEM_LOC(pTreeNode);

    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            break;
        case NODE_POINTER_CONTENT:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            emitMemoryInstruction(INST_LDX, lReg, lReg, 0);
            break;
        case NODE_REFERENCE:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LDI, lReg, REG_NONE, leftAddr);
            break;
        case NODE_POST_INC:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, leftAddr);
            childPos = 0;
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            emitAluInstruction(INST_ADD, true, 1, lReg, lReg, REG_NONE);
            emitMemoryInstruction(INST_ST, lReg, REG_NONE, leftAddr);
            break;
        case NODE_POST_DEC:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, leftAddr);
            childPos = 0;
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            leftAddr = L_CHILD_MEM_LOC(pTreeNode);
            emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            emitAluInstruction(INST_SUB, true, 1, lReg, lReg, REG_NONE);
            emitMemoryInstruction(INST_ST, lReg, REG_NONE, leftAddr);
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&L_CHILD(pTreeNode), lReg);
            emitMemoryInstruction(INST_LDX, lReg, lReg, 0);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    switch (R_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            break;
        case NODE_POINTER_CONTENT:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            emitMemoryInstruction(INST_LDX, rReg, rReg, 0);
            break;
        case NODE_REFERENCE:
            emitMemoryInstruction(INST_LDI, rReg, REG_NONE, rightAddr);
            break;
        case NODE_POST_INC:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, rightAddr);
            childPos = 1;
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            emitAluInstruction(INST_ADD, true, 1, rReg, rReg, REG_NONE);
            emitMemoryInstruction(INST_ST, rReg, REG_NONE, rightAddr);
            break;
        case NODE_POST_DEC:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, rightAddr);
            childPos = 1;
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            emitMemoryInstruction(INST_LD, rReg, REG_NONE, rightAddr);
            emitAluInstruction(INST_SUB, true, 1, rReg, rReg, REG_NONE);
            emitMemoryInstruction(INST_ST, rReg, REG_NONE, rightAddr);
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&R_CHILD(pTreeNode), rReg);
            emitMemoryInstruction(INST_LDX, rReg, rReg, 0);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    emitAluInstruction(asmInstruction, false, 0, destReg, lReg, rReg);

    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && is_postinc)
    {
        //rReg already has the value contained in the address of the right child
        //lreg already has the value contained in the address of the left child
        if(childPos == 1)
        {
            emitAluInstruction(INST_ADD, true, 1, rReg, rReg, REG_NONE);
            emitMemoryInstruction(INST_ST, rReg, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
        }
        else
        {
            emitAluInstruction(INST_ADD, true, 1, lReg, lReg, REG_NONE);
            emitMemoryInstruction(INST_ST, lReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
        }
        
    }

    if(!delayPostIncDec && is_postdec)
    {
        //rReg already has the value contained in the address of the right child
        //lreg already has the value contained in the address of the left child
        if(childPos == 1)
        {
            emitAluInstruction(INST_SUB, true, 1, rReg, rReg, REG_NONE);
            emitMemoryInstruction(INST_ST, rReg, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
        }
        else
        {
            emitAluInstruction(INST_SUB, true, 1, lReg, lReg, REG_NONE);
            emitMemoryInstruction(INST_ST, lReg, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
        }
        
    }

    releaseReg(lReg);
    releaseReg(rReg);

    return 0;
}



static int generateBooleanOperation(OperatorType_et operatorType, TreeNode_st *pTreeNode, reg_et destReg, reg_et lReg, reg_et rReg, bool is_root)
{
    bool allocTemp1 = (lReg == REG_NONE) ? 1 : 0;
    bool allocTemp2 = (rReg == REG_NONE) ? 1 : 0;

    reg_et tempReg1 = allocTemp1 ? getNextAvailableReg() : lReg;
    reg_et tempReg2 = allocTemp2 ? getNextAvailableReg() : rReg;

    if(!is_root)
    {
        switch (L_CHILD_TYPE(pTreeNode))
        {
            case NODE_INTEGER:
                emitMemoryInstruction(INST_LDI, tempReg1, REG_NONE, L_CHILD_DVAL(pTreeNode));
                break;
            case NODE_IDENTIFIER:
                emitMemoryInstruction(INST_LD, tempReg1, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
                break;
            case NODE_POINTER:
                emitMemoryInstruction(INST_LD, tempReg1, REG_NONE, L_CHILD_MEM_LOC(pTreeNode));
                emitMemoryInstruction(INST_LDX, tempReg1, tempReg1, 0);
                break;
            case NODE_ARRAY_INDEX:
                handleArrayIndexedExpressions(&L_CHILD(pTreeNode), tempReg1);
                emitMemoryInstruction(INST_LDX, tempReg1, tempReg1, 0);
                break;
            
            default:
                LOG_ERROR("Un-Implemented condition!\n");
                break;
        }


        switch (R_CHILD_TYPE(pTreeNode))
        {
            case NODE_INTEGER:
                emitMemoryInstruction(INST_LDI, tempReg2, REG_NONE, R_CHILD_DVAL(pTreeNode));
                break;
            case NODE_IDENTIFIER:
                emitMemoryInstruction(INST_LD, tempReg2, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
                break;
            case NODE_POINTER:
                emitMemoryInstruction(INST_LD, tempReg2, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));
                emitMemoryInstruction(INST_LDX, tempReg2, tempReg2, 0);
                break;
            case NODE_ARRAY_INDEX:
                handleArrayIndexedExpressions(&R_CHILD(pTreeNode), tempReg2);
                emitMemoryInstruction(INST_LDX, tempReg2, tempReg2, 0);
                break;
            
            default:
                LOG_ERROR("Un-Implemented condition!\n");
                break;
        }
    }
    

    //Pre-load the value 1 to indicate that the condition is true if it doesnt change
    emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 1);

    
    if(operatorType == OP_LOGICAL_AND)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BEQ, FALSE, getLabelCounter(FALSE));
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg2, REG_NONE);
        emitBranchInstruction(INST_BEQ, FALSE, getLabelCounter(FALSE));
        emitBranchInstruction(INST_BRA, TRUE, getLabelCounter(TRUE));
        emitLabelInstruction(FALSE, getPostIncLabelCounter(FALSE), NULL);
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);


    }
    else if(operatorType == OP_LOGICAL_OR)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg2, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);

    }
    else if (operatorType == OP_LOGICAL_NOT)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);
    }
    else
    { //Cases: !=, ==, >=, <=, etc
        emitAluInstruction(INST_CMP, false, 0, REG_NONE, tempReg1, tempReg2);
        emitBranchInstruction(mapInstructionFromOperator(operatorType), SKIP, getLabelCounter(SKIP));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0);
        emitLabelInstruction(SKIP, getLabelCounter(SKIP), NULL);      
    }
    
    if(allocTemp1) 
        releaseReg(tempReg1);
    if(allocTemp2) 
        releaseReg(tempReg2);

    return 0;
}


 static int handleRootBooleanNode(OperatorType_et rootNodeOpType, reg_et dreg, reg_et lReg, reg_et rReg)
 {
    generateBooleanOperation(rootNodeOpType, NULL, dreg, lReg, rReg, true);
 }


/// @brief function for emiting assign operations 
/// @param operatorType -> Type of assign(=, +=, <<=, &=,*x = &y, etc.)
/// @param pTreeNode -> current node being processed
/// @param destReg -> destiny register used for code emition
/// @return 
static int generateAssignOperation(OperatorType_et operatorType, TreeNode_st *pTreeNode, reg_et destReg)
{
    uint32_t leftAddr;
    uint32_t rightAddr;

    reg_et tempReg = getNextAvailableReg();
    reg_et lReg = getNextAvailableReg();

    bool is_postdec= 0;
    bool is_postinc= 0;

    //Address where we will store the value of the assign
    leftAddr = L_CHILD_MEM_LOC(pTreeNode);


    if (R_CHILD_TYPE(pTreeNode) != NODE_INTEGER)
        rightAddr = R_CHILD_MEM_LOC(pTreeNode);

        

    //Templates for the Right childs of an assignement
    switch (R_CHILD_TYPE(pTreeNode))
    {
        case NODE_INTEGER:
            emitMemoryInstruction(INST_LDI, tempReg, REG_NONE, R_CHILD_DVAL(pTreeNode));
            break;
        case NODE_IDENTIFIER:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            break;
        case NODE_POINTER_CONTENT:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0);
            break;
        case NODE_REFERENCE:
            emitMemoryInstruction(INST_LDI, tempReg, REG_NONE, rightAddr);
            break;
        case NODE_POST_INC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
            emitMemoryInstruction(INST_ST, tempReg, REG_NONE, rightAddr);
            break;
        case NODE_POST_DEC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            emitMemoryInstruction(INST_LD, tempReg, REG_NONE, rightAddr);
            emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
            emitMemoryInstruction(INST_ST, tempReg, REG_NONE, rightAddr);
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&R_CHILD(pTreeNode), tempReg);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    //Templates for the left child of an assignement
    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            if (operatorType != OP_ASSIGN)
            {
                emitMemoryInstruction(INST_LD, lReg, REG_NONE, leftAddr);
            }
            break;
        case NODE_POINTER_CONTENT:
            emitMemoryInstruction(INST_LD, destReg, REG_NONE, leftAddr);
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&L_CHILD(pTreeNode), destReg);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    //If its an assign with an Alu operation (+=, -=,..), generate the operation before the Store
    //Will need to halndle here the multiply, div and remaind diferently
    if (operatorType != OP_ASSIGN)
    {
        if (operatorType == OP_MULTIPLY_ASSIGN || operatorType == OP_DIVIDE_ASSIGN || operatorType == OP_MODULUS_ASSIGN)
            LOG_ERROR("multiplies, divides and modulus assigns are not being handled right now!\n");

        emitAluInstruction(mapInstructionFromAssignOp(operatorType), false, 0, lReg, lReg, tempReg);
    }

    //Templates for the left child of an assignement
    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            if(operatorType != OP_ASSIGN)
                emitMemoryInstruction(INST_ST, lReg, REG_NONE, leftAddr);
            else
                emitMemoryInstruction(INST_ST, tempReg, REG_NONE, leftAddr);
            break;
        case NODE_POINTER_CONTENT:
            if(operatorType != OP_ASSIGN)
                emitMemoryInstruction(INST_STX, lReg, destReg, 0);
            else
                emitMemoryInstruction(INST_STX, tempReg, destReg, 0);
            break;
        case NODE_ARRAY_INDEX:
            if(operatorType != OP_ASSIGN)
                emitMemoryInstruction(INST_STX, lReg, destReg, 0);
            else
                emitMemoryInstruction(INST_STX, tempReg, destReg, 0);
            break;
        default:
            LOG_ERROR("Un-Implemented condition!\n");
            break;
    }

    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && is_postinc)
    {       
        emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
        emitMemoryInstruction(INST_ST, tempReg, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));       
    }
    if(!delayPostIncDec && is_postdec)
    {     
        emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
        emitMemoryInstruction(INST_ST, tempReg, REG_NONE, R_CHILD_MEM_LOC(pTreeNode));  
    }

    releaseReg(tempReg);
    releaseReg(lReg);

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
        case OP_BITWISE_AND:
        case OP_BITWISE_NOT:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
            generateAluOperation(pTreeNode, dReg);
            break;
        case OP_GREATER_THAN:
        case OP_LESS_THAN_OR_EQUAL:
        case OP_GREATER_THAN_OR_EQUAL:
        case OP_LESS_THAN:
        case OP_EQUAL:
        case OP_NOT_EQUAL:
        case OP_LOGICAL_AND:
        case OP_LOGICAL_OR:
        case OP_LOGICAL_NOT:
            generateBooleanOperation(opType, pTreeNode, dReg, REG_NONE, REG_NONE, false);
            break;
        case OP_ASSIGN:
        case OP_PLUS_ASSIGN:
        case OP_MINUS_ASSIGN:
        case OP_MODULUS_ASSIGN:
        case OP_LEFT_SHIFT_ASSIGN:
        case OP_RIGHT_SHIFT_ASSIGN:
        case OP_BITWISE_AND_ASSIGN:
        case OP_BITWISE_OR_ASSIGN:
        case OP_BITWISE_XOR_ASSIGN:
        case OP_MULTIPLY_ASSIGN:
        case OP_DIVIDE_ASSIGN:
            generateAssignOperation(opType, pTreeNode, dReg);
            break;
        case OP_SIZEOF:
            break;
        case OP_NEGATIVE:
            break;
    }

    return 0;
}


//Nova versao: O Parsenode agora recebe também o nó do pai e uma variavel que diz se o nó atual está à esquerda ou direita do pai....
//Assim criavam-se templates dos INTEGER,IDs, etc no "Case integer"/"Case ID", etc

/// \brief Different ParsesNode because it allows to parse the terminal nodes (INTEGER, IDENTIFIER, POINTER_CONTENT,..) in their own "case" of the big switch
/// Although, it has to receive additional params  
/// \param pCurrentNode Pointer to the current Node to be parsed
/// \param parentNodeType The type of the parent of the currentNode
/// \param isLeftInherited 1 if the currentNode is at the left of its parent, 0 if its at the right of the parent
/// \return 0 if success; -EINVAL in pCurrentNode is NULL
static int parseNode(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited)
{
    reg_et lReg;
    reg_et rReg;
    reg_et dReg;

    OperatorType_et CurrentNodeOpType = (OperatorType_et) pCurrentNode->nodeData.dVal;

    if (!IS_TERMINAL_NODE(pCurrentNode->nodeType) && NODE_TYPE(pCurrentNode) == NODE_OPERATOR)
    {
        //If we enter a non terminal node we allocate a new dReg for that operation
        dReg = getNextAvailableReg();
        lReg = REG_NONE;
        rReg = REG_NONE;
    }
    
    if(IS_TERMINAL_NODE(pCurrentNode->nodeType) && IS_CONDITIONAL_NODE(parentNodeType))
        dReg = getNextAvailableReg();

    if(parentNodeType == NODE_ARRAY_INDEX)
        arrayIndexRegSave = dReg;

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
        case NODE_OPERATOR:

            if(IS_ASSIGN_OPERATION(CurrentNodeOpType))
                delayPostIncDec = 1;

            if (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Left Child If its not a terminal node
                generateCode(&pCurrentNode->pChilds[0]);
                lReg = dRegSave;

            }
            //There are nodes with only 1 left child so before we genCode for the right one we need to verify if it exists in order to not get SegFault Error
            if (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Right Child If its not terminal node
                generateCode(&pCurrentNode->pChilds[1]);
                rReg = dRegSave;
            }

            //TERMINAL NODE CASES
            //Should only enter these cases when we find Terminal nodes and when we start going upwards in the AST
            if (IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)) && IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //If both childs are terminals, parse the node to generate the ALU operation
                parseOperatorNode(pCurrentNode, dReg);
                dRegSave = dReg;
            }
            else if ((IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))) && (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))))
            {
                //If Left child is a terminal node and Right child is not
                rRegSave = rReg;  //Save lReg and dReg because we will enter a new calling stack
                dRegSave = dReg;
                parseNode(&pCurrentNode->pChilds[0], NODE_OPERATOR, CurrentNodeOpType, true);
                releaseReg(rReg); //Release the right reg when going up in the tree. But it will be used to generate an instruction for this node
            }
            else if ((IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))) && (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))))
            {
                //If Right child is a terminal node and Left child is not
                lRegSave = lReg; //Save lReg and dReg because we will enter a new calling stack
                dRegSave = dReg;
                parseNode(&pCurrentNode->pChilds[1], NODE_OPERATOR, CurrentNodeOpType, false);
                releaseReg(lReg); //Release the right reg when going up in the tree. But it will be used to generate an instruction for this node
            }
            else
            {
                //If both childs are Non-Terminals
                if(IS_ALU_OPERATION(CurrentNodeOpType))
                    emitAluInstruction(mapInstructionFromOperator(CurrentNodeOpType), false, 0, dReg, lReg, rReg);

                else if(IS_BOOLEAN_OPERATION(CurrentNodeOpType))
                    handleRootBooleanNode(CurrentNodeOpType, dReg, lReg, rReg);

                dRegSave = dReg;
                releaseReg(lReg);
                releaseReg(rReg);
            }

            //If there are Post Increments or Decrements to emit, handle it here
            if(IS_ASSIGN_OPERATION(CurrentNodeOpType))
                handlePostIncDecOperations(dReg);

            break;
        case NODE_TERNARY:
            break;
        case NODE_IDENTIFIER:
            

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Will always be left inherited so the value to assign is always at rReg
                rReg = rRegSave;

                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);

                //If its an assign with an operation (+=, -=), GenCode for the operation
                if (parentOperatorType != OP_ASSIGN)
                {
                    reg_et auxReg = getNextAvailableReg();
                    emitMemoryInstruction(INST_LD, auxReg, REG_NONE, memAddr);
                    emitAluInstruction(mapInstructionFromAssignOp(parentOperatorType), false, 0, rReg, auxReg, rReg);
                    releaseReg(auxReg);
                }

                emitMemoryInstruction(INST_ST, rReg, REG_NONE, memAddr);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(x), while(x)...
            {
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                dRegSave = dReg;
            }

            break;
        case NODE_STRING:
            break;
        case NODE_INTEGER:

            //Load saved registers
            //rReg is not used in imm operation so in case it is left inherited we reload the rRegSave to the lReg  
            lReg = isLeftInherited ? rRegSave : lRegSave;

            

            //If the integer is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Foi necessário colocar aqui a mesma verificação que está na func generateALUOperation (se for operaçao menos trocar para ADD e negar o imediato)
                if ((parentOperatorType == OP_MINUS) && isLeftInherited)
                {
                    uint32_t immVal = pCurrentNode->nodeData.dVal;
                    emitAluInstruction(INST_ADD, true, -immVal, dReg, lReg, REG_NONE);
                    emitAluInstruction(INST_SUB, false, 0, dReg, REG_R0, dReg);
                }
                else
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), true, pCurrentNode->nodeData.dVal, dReg, lReg, REG_NONE);

            }
            else if(parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LDI, tempreg, REG_NONE, pCurrentNode->nodeData.dVal);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                     
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(1), while(1)...
            {
                emitMemoryInstruction(INST_LDI, dReg, REG_NONE, pCurrentNode->nodeData.dVal);
                dRegSave = dReg;
            }

            break;
        case NODE_FLOAT:
            break;
        case NODE_CHAR:
            break;
        case NODE_STRUCT:
            break;
        case NODE_IF:
            
            parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);
            
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);
            emitBranchInstruction(INST_BEQ, IF_FALSE, getLabelCounter(IF_FALSE));
            if (pCurrentNode->childNumber > 1)
                generateCode(&pCurrentNode->pChilds[1]);

            //If statement with else
            if (pCurrentNode->childNumber > 2)
            {
                emitBranchInstruction(INST_BRA, IF_EXIT, getLabelCounter(IF_EXIT));
                emitLabelInstruction(IF_FALSE, getPostIncLabelCounter(IF_FALSE), NULL);
                generateCode(&pCurrentNode->pChilds[2]);
            }

            emitLabelInstruction(IF_EXIT, getPostIncLabelCounter(IF_EXIT), NULL);

            break;
        case NODE_WHILE:
            emitLabelInstruction(WHILE_START, getLabelCounter(WHILE_START), NULL);
            generateCode(&L_CHILD(pCurrentNode));
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);
            emitBranchInstruction(INST_BEQ, WHILE_EXIT, getLabelCounter(WHILE_EXIT));

            //While can be empty
            if (pCurrentNode->childNumber > 1)
                generateCode(&R_CHILD(pCurrentNode));

            emitBranchInstruction(INST_BRA, WHILE_START, getPostIncLabelCounter(WHILE_START));
            emitLabelInstruction(WHILE_EXIT, getPostIncLabelCounter(WHILE_EXIT), NULL);
            break;

        case NODE_DO_WHILE:
            emitLabelInstruction(WHILE_START, getLabelCounter(WHILE_START), NULL);
            
            //Do can be empty
            //Gen code inside do
            if (pCurrentNode->childNumber > 1)
                generateCode(&R_CHILD(pCurrentNode));

            //Generate while condition
            generateCode(&L_CHILD(pCurrentNode));
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);
            emitBranchInstruction(INST_BNE, WHILE_START, getPostIncLabelCounter(WHILE_START));
            

            /*
            DO:
                (CODIGO)
                (CONDIITON)
                LD R,
                CMP R, #0
                BNE DO
                 
                 ...

            */

            break;
        case NODE_RETURN:
            // Place return values in R4
            if(L_CHILD_TYPE(pCurrentNode) == NODE_IDENTIFIER)
            {
                emitMemoryInstruction(INST_LD, REG_R4, REG_NONE, L_CHILD_MEM_LOC(pCurrentNode));
            }
            // @todo Verificar qual é o melhor metodo para expressões
            
            // Restore Registers
            for (reg_et i = REG_R23; i >= REG_R16; i--)
            {
                pop(i);
            }

            // Instruction to return to program flow before call
            break;
        case NODE_CONTINUE:
            break;
        case NODE_BREAK:
        
            if(parentNodeType != NODE_DEFAULT)
                emitBranchInstruction(INST_BRA, CASE_EXIT, getLabelCounter(CASE_EXIT));
        
            break;
        case NODE_GOTO:
            break;
        case NODE_LABEL:
            break;
        case NODE_SWITCH:
            //Generate code for expression inside switch     
             parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);
            
            // dRegSave
            
            reg_et compareReg = getNextAvailableReg();

            //generateCode(&R_CHILD(pCurrentNode));

            TreeNode_st *pCases, pDefault;
            pCases = &pCurrentNode->pChilds[1];

            int keepCounter = labelCounters[CASE];

            while(pCases->pSibling != NULL ){
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LDI, tempreg, REG_NONE, pCases->nodeData.dVal);
            
                emitAluInstruction(INST_CMP, false, 0, REG_NONE, dRegSave, tempreg);
                emitBranchInstruction(INST_BEQ, CASE, getPostIncLabelCounter(CASE));
                
                releaseReg(tempreg);                

                if(pCases->pSibling->nodeType == NODE_DEFAULT)
                {
                    emitBranchInstruction(INST_BRA, DEFAULT, getLabelCounter(DEFAULT));  
                }
                else if(pCases->pSibling == NULL)
                    emitBranchInstruction(INST_BRA, CASE_EXIT, getLabelCounter(CASE_EXIT));  

                pCases = pCases->pSibling;
            }

            labelCounters[CASE]= keepCounter;
            
            generateCode(&R_CHILD(pCurrentNode));
            
            emitLabelInstruction(CASE_EXIT, getPostIncLabelCounter(CASE_EXIT), NULL);

            break;
        case NODE_CASE:             
            //Emit Label for Case
            reg_et tempreg = getNextAvailableReg(); 
            emitLabelInstruction(CASE, getPostIncLabelCounter(CASE), NULL);
            //Gen the case Code 
            generateCode(&L_CHILD(pCurrentNode));
            

            releaseReg(tempreg);
            break;
        case NODE_DEFAULT:
            emitLabelInstruction(DEFAULT, getPostIncLabelCounter(DEFAULT), NULL);
            generateCode(&L_CHILD(pCurrentNode));
            break;
        case NODE_REFERENCE:
            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LDI, dReg, REG_NONE, memAddr);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LDI, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            break;
        case NODE_POINTER:
            break;
        case NODE_POINTER_CONTENT:

            

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                emitMemoryInstruction(INST_LDX, dReg, dReg, memAddr);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
                //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Will always be left inherited so the value to assign is always at rReg
                rReg = rRegSave;
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);

                //If its an assign with an operation (+=, -=), GenCode for the operation
                if (parentOperatorType != OP_ASSIGN)
                {
                    LOG_ERROR("Not implemented because its not suported by the parser");
                }
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                emitMemoryInstruction(INST_STX, rReg, dReg, 0);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                emitMemoryInstruction(INST_LDX, tempreg, tempreg, 0);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(*x), while(*x)...
            {
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0);
                dRegSave = dReg;
            }

            break;
        case NODE_TYPE_CAST:
            break;
        case NODE_POST_DEC:
            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }

                //If an assign wasnt found before, do the post inc here
                if(!delayPostIncDec)
                {
                    emitAluInstruction(INST_SUB, true, 1, dReg, dReg, REG_NONE);
                    emitMemoryInstruction(INST_ST, dReg, REG_NONE, memAddr);
                }
                else
                    PostIncListInsert(postIncList, true, memAddr);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                emitAluInstruction(INST_SUB, true, 1, tempreg, tempreg, REG_NONE);
                emitMemoryInstruction(INST_ST, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                releaseReg(tempreg);
            }
                //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its a dec statement (eg i--;)
            {
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                reg_et tReg = getNextAvailableReg();

                emitMemoryInstruction(INST_LD, tReg, REG_NONE, memAddr);
                emitAluInstruction(INST_SUB, true, 1, tReg, tReg, REG_NONE);
                emitMemoryInstruction(INST_ST, tReg, REG_NONE, memAddr);
                releaseReg(tReg);
            }
            break;
        case NODE_PRE_DEC:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);

                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                emitAluInstruction(INST_SUB, true, 1, dReg, dReg, REG_NONE);
                emitMemoryInstruction(INST_ST, dReg, REG_NONE, memAddr);


                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                emitAluInstruction(INST_SUB, true, 1, tempreg, tempreg, REG_NONE);
                emitMemoryInstruction(INST_ST, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                releaseReg(tempreg);
            }
            //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its a dec statement (eg --i;)
            {
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                reg_et tReg = getNextAvailableReg();

                emitMemoryInstruction(INST_LD, tReg, REG_NONE, memAddr);
                emitAluInstruction(INST_SUB, true, 1, tReg, tReg, REG_NONE);
                emitMemoryInstruction(INST_ST, tReg, REG_NONE, memAddr);
                releaseReg(tReg);
            }
            break;
        case NODE_POST_INC:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                    
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
                //If an assign wasnt found before, do the post inc here
                if(!delayPostIncDec)
                {
                    emitAluInstruction(INST_ADD, true, 1, dReg, dReg, REG_NONE);
                    emitMemoryInstruction(INST_ST, dReg, REG_NONE, memAddr);
                }
                else
                    PostIncListInsert(postIncList, true, memAddr);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                emitAluInstruction(INST_ADD, true, 1, tempreg, tempreg, REG_NONE);
                emitMemoryInstruction(INST_ST, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                releaseReg(tempreg);
            }
            //If is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //Is just an increment statement (ex i++;)
            {
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                reg_et tReg = getNextAvailableReg();

                emitMemoryInstruction(INST_LD, tReg, REG_NONE, memAddr);
                emitAluInstruction(INST_ADD, true, 1, tReg, tReg, REG_NONE);
                emitMemoryInstruction(INST_ST, tReg, REG_NONE, memAddr);
                releaseReg(tReg);
            }
            break;
        case NODE_PRE_INC:
            //If is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                emitMemoryInstruction(INST_LD, dReg, REG_NONE, memAddr);
                emitAluInstruction(INST_ADD, true, 1, dReg, dReg, REG_NONE);
                emitMemoryInstruction(INST_ST, dReg, REG_NONE, memAddr);


                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LD, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));
                emitAluInstruction(INST_ADD, true, 1, tempreg, tempreg, REG_NONE);
                emitMemoryInstruction(INST_ST, tempreg, REG_NONE, NODE_MEM_LOC(pCurrentNode));

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                
                releaseReg(tempreg);
            }
            //If is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its an inc statement (eg ++i)
            {
                uint32_t memAddr = NODE_MEM_LOC(pCurrentNode);
                reg_et tReg = getNextAvailableReg();

                emitMemoryInstruction(INST_LD, tReg, REG_NONE, memAddr);
                emitAluInstruction(INST_ADD, true, 1, tReg, tReg, REG_NONE);
                emitMemoryInstruction(INST_ST, tReg, REG_NONE, memAddr);
                releaseReg(tReg);
            }
            break;
        case NODE_ARRAY_DECLARATION:
            break;
        case NODE_ARRAY_INDEX:

            
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;             
                handleArrayIndexedExpressions(pCurrentNode, dReg);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            //If the array is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Dreg will have the value of the memory location of array[exp]
                handleArrayIndexedExpressions(pCurrentNode, dReg);

                //Will always be left inherited, if it was left inherited then the left child would also be a terminal one and that case is handled in ParseAssignOperation()
                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    //If array child is at the left we need to store to it
                    emitMemoryInstruction(INST_STX, rReg, dReg, 0);
                }

            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                handleArrayIndexedExpressions(pCurrentNode, tempreg);
                emitMemoryInstruction(INST_LDX, tempreg, tempreg, 0);
                
                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                
                releaseReg(tempreg);
            }
            else //used for while(array[x]), if (array[x])
            {
                handleArrayIndexedExpressions(pCurrentNode, dReg);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0);
                dRegSave = dReg;
            }

            break;
        case NODE_TYPE:
            break;
        case NODE_VAR_DECLARATION:
            break;
        case NODE_FUNCTION:
        
            /* if(pCurrentNode->childNumber != 3)
            {
                break; // Function node with no body
            }

            // Emit function Label

            // Save Saved Registers
            for (reg_et i = REG_R16; i <= REG_R23; i++)
            {
                push(i);
            }

            // Generate Body
            generateCode(pCurrentNode->pChilds + 2);
          
            // Emit Instruction to return for void functions as those won't have return statements
            if(pCurrentNode->nodeVarType != TYPE_VOID)
            {
                break;  
            } 
            
            for (reg_et i = REG_R23; i >= REG_R16; i--)
            {
                pop(i);
            }
            // Jump to addr in R1

            break; */
            generateCode(pCurrentNode->pChilds + 2);
            break;
        case NODE_FUNCTION_CALL:

            // @todo add expressions and numbers
            // Place Arguments
            TreeNode_st *pParameter = &pCurrentNode->pChilds[0];
            
            for (size_t i = 0; i < pCurrentNode->pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
            {
                if(pParameter)
                {
                    emitMemoryInstruction(INST_LD, REG_R4 + i, REG_NONE, pParameter->pSymbol->symbolContent_u.memoryLocation);
                    pParameter = pParameter->pSibling;
                }
            }
            
            // Save Register R1
            push(REG_R1);
            // Emit JMPL??
            // Emit NOP
            // Emit Branch

            
            // Restore R1
            pop(REG_R1);

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

/// @brief Function to push registers to stack. Updates Stack Pointer
/// @warning It assumes stack was correctly built and stack management is conducted properly,
/// as such, has no safeguards
/// @param reg register to save to stack
static void push(reg_et reg)
{
    emitAluInstruction(INST_SUB, 1, 1, REG_R3, REG_R3, REG_NONE);
    emitMemoryInstruction(INST_STX, reg, REG_R3, STACK_START_ADDR);
}

/// @brief Function to pop registers from stack. Updates Stack Pointer
/// @warning It assumes stack was correctly built and stack management is conducted properly,
/// as such, has no safeguards
/// @param reg register to get from stack
static void pop(reg_et reg)
{
    emitMemoryInstruction(INST_LDX, reg, REG_R3, STACK_START_ADDR);
    emitAluInstruction(INST_ADD, 1, 1, REG_R3, REG_R3, REG_NONE);
}

void codeGenerationTestUnit()
{
    reg_et reg;
    TreeNode_st treeRoot = {0};
    TreeNode_st *pLeftChild;
    TreeNode_st *pRightChild;
    TreeNode_st *pLeftGrandChild;
    TreeNode_st *pRightGrandChild;
    TreeNode_st *_pLeftGrandChild;
    TreeNode_st *_pRightGrandChild;
    TreeNode_st *pLeftGrandChild_;
    TreeNode_st *pRightGrandChild_;
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


/* TEST SIMPLE Arithmetic
 * M (Mem)-> Means it is an identifier 
 *
 *              -
 *             / \
 *         1       *X:0xF
 *           
 *       
 */

//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_MINUS;

//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

//    pRightChild->nodeData.dVal = 1;
//    pLeftChild->pSymbol = &symbolEntry2;


/* TEST SIMPLE BOOLEAN
 * M (Mem)-> Means it is an identifier 
 *
 *             &&
 *             / \
 *          1      X:0xF
 *           
 *       
 */

    treeRoot.nodeType = NODE_OPERATOR;
    treeRoot.nodeData.dVal = OP_LOGICAL_AND;

    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_INTEGER);
    NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

    pLeftChild->nodeData.dVal = 1;
    pRightChild->pSymbol = &symbolEntry2;



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
            M:0xF  #32 M:0xAB  -          M:0x20  + 
                              / \                / \
                            /     \             /   \        
                          #20      +           -     M:0xAB
                                  / \         / \  
                                 /   \       /   \
                           M:0xAB  M:0xCD   #1  M:0xF      
*/
// TreeNode_st *pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;
// TreeNode_st *pFourthLevelChild_1, *pFourthLevelChild_2, *pFourthLevelChild_3, *pFourthLevelChild_4;
// TreeNode_st *pFifthLevelChild_1, *pFifthLevelChild_2, *pFifthLevelChild_3, *pFifthLevelChild_4;     

//     treeRoot.nodeType = NODE_OPERATOR;
//     treeRoot.nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

//     pLeftChild->nodeData.dVal = OP_PLUS;
//     pRightChild->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
//     NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

//     pLeftGrandChild->nodeData.dVal = OP_MINUS;  
//     pRightGrandChild->nodeData.dVal = OP_PLUS;   

//     NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
//     NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

//     _pLeftGrandChild->nodeData.dVal = 255;
//     _pRightGrandChild->nodeData.dVal = OP_MINUS;  

//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

//     pThirdLevelChild_1->pSymbol = &symbolEntry2;
//     pThirdLevelChild_2->nodeData.dVal = 32;

//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_OPERATOR);

//     pThirdLevelChild_3->pSymbol = &symbolEntry3;
//     pThirdLevelChild_4->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_IDENTIFIER);
//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_OPERATOR);

//     pThirdLevelChild_5->pSymbol = &symbolEntry;
//     pThirdLevelChild_6->nodeData.dVal = OP_PLUS;

//     NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_3, NODE_OPERATOR);
//     NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_4, NODE_IDENTIFIER);

//     pFourthLevelChild_3->nodeData.dVal = OP_MINUS;
//     pFourthLevelChild_4->pSymbol = &symbolEntry3;

//     NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_3, NODE_INTEGER);
//     NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_4, NODE_IDENTIFIER);

//     pFifthLevelChild_3->nodeData.dVal = 1;
//     pFifthLevelChild_4->pSymbol = &symbolEntry2;

//     NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_1, NODE_INTEGER);
//     NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_2, NODE_OPERATOR);

//     pFourthLevelChild_1->nodeData.dVal = 20;
//     pFourthLevelChild_2->nodeData.dVal = OP_PLUS;

//     NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_2, NODE_IDENTIFIER);

//     pFifthLevelChild_1->pSymbol = &symbolEntry3;
//     pFifthLevelChild_2->pSymbol = &symbolEntry4;

/* TEST 9
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
            M:0xF  #32 M:0xAB  -          M:0x20  +
                              / \                / \
                            /     \             /   \        
                          #20      +           -     ++M:0xAB
                                  / \         / \  
                                 /   \       /   \
                           M:0xAB *M:0xCD   #1  ++M:0xF      
*/
    /* TreeNode_st *pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;
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
    NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_4, NODE_PRE_INC);

    pFourthLevelChild_3->nodeData.dVal = OP_MINUS;
    pFourthLevelChild_4->pSymbol = &symbolEntry3;

    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_3, NODE_INTEGER);
    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_4, NODE_PRE_INC);

    pFifthLevelChild_3->nodeData.dVal = 1;
    pFifthLevelChild_4->pSymbol = &symbolEntry2;

    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_1, NODE_INTEGER);
    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_2, NODE_OPERATOR);

    pFourthLevelChild_1->nodeData.dVal = 20;
    pFourthLevelChild_2->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_1, NODE_IDENTIFIER);
    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_2, NODE_POINTER_CONTENT);

    pFifthLevelChild_1->pSymbol = &symbolEntry3;
    pFifthLevelChild_2->pSymbol = &symbolEntry4; */


/*  ASSIGN TEST 1
 *                 =
 *              /     \
 *           M:0xF     #1    
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->nodeData.dVal = 1;


/*  ASSIGN TEST 2
 *                 =
 *              /     \
 *           M:0xF   M:0xAB       
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->pSymbol = &symbolEntry3;


/*  ASSIGN TEST 3
 *                 =
 *              /     \
 *          *p:0xF  &a:0xAB       
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
    // // NodeAddNewChild(&treeRoot, &pRightChild, NODE_REFERENCE);

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_REFERENCE);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->pSymbol = &symbolEntry3;







    generateCode(&treeRoot);
    //Release reg12 which is the one alloc'ed for the root
    releaseReg(REG_R12);

    //Test If there was a register that was not released  
    printf("\n");
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {

        if (regStateList[i].isFree == false)
        {
            LOG_ERROR("%s was not released\n", regNameLut[regStateList[i].regName]);
        }
    }

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