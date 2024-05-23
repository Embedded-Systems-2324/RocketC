#include "../Util/Logger.h"
#include "CodeGeneration.h"
#include "CodeGenerationTypes.h"

#define MAX_IMMED_ALU ((1 << 16) - 1)
#define MAX_IMMED_LD  ((1 << 23) - 1)
#define MAX_IMMED_LDI ((1 << 23) - 1)
#define MAX_IMMED_LDX ((1 << 18) - 1)
#define MAX_IMMED_ST  ((1 << 23) - 1)
#define MAX_IMMED_STX ((1 << 18) - 1)

#define INSTRUCTION(x) (instructionLut[(x)])
#define REGISTER(x) (regNameLut[(x)])
#define L_CHILD_TYPE(p) ((p)->pChilds[0].nodeType)
#define R_CHILD_TYPE(p) ((p)->pChilds[1].nodeType)
#define L_CHILD_DVAL(p) ((p)->pChilds[0].nodeData.dVal)
#define R_CHILD_DVAL(p) ((p)->pChilds[1].nodeData.dVal)
#define SYMB_MEM_LOC(p) ((p)->symbolContent_u.memoryLocation)
#define L_CHILD(p) ((p)->pChilds[0])
#define R_CHILD(p) ((p)->pChilds[1])
#define VALID_ALU_IMMED(x) ((x) <= MAX_IMMED_ALU)
#define VALID_LDI_IMMED(x) ((x) <= MAX_IMMED_LDI)

typedef struct
{
    reg_et regName;
    bool isFree;
}reg_state_st;

typedef struct
{
    OperatorType_et operatorType;
    asm_instr_et asmInstruction;
}operator_pair_st;

static FILE* pAsmFile;
static int generateCode(TreeNode_st* pTreeNode);
static int parseNode(TreeNode_st* pTreeNode);

static reg_et getNextAvailableReg();
static int releaseReg(reg_et reg);
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
    {.operatorType = OP_PLUS, .asmInstruction = INST_ADD},
    {.operatorType = OP_MINUS, .asmInstruction = INST_SUB},
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

int executeCodeGeneration(TreeNode_st* pTreeRoot, const char* pDestFile)
{
    if (!pTreeRoot || !pDestFile)
        return -EINVAL;

    pAsmFile = fopen(pDestFile, "w");
    if (!pAsmFile)
        return -EIO;

    return 0;
}

static int generateCode(TreeNode_st* pTreeNode)
{
    TreeNode_st* pSib;
    int ret = parseNode(pTreeNode);
    if (ret < 0)
        return ret;

    pSib = pTreeNode->pSibling;
    while (pSib)
    {
        parseNode(pSib);
        pSib = pSib->pSibling;
    }

    return 0;
}

static int emitAluInstruction(asm_instr_et instructionType,
                              uint8_t isImed,
                              uint32_t imedValue,
                              reg_et resultReg,
                              reg_et leftOperand,
                              reg_et rightOperand)
{
    //Check if it is a valid ALU instruction
    if (instructionType > INST_XOR)
        return -EINVAL;

    //NOT instruction can't use immediate as a parameter
    if ((instructionType == INST_NOT) && (isImed))
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
/// \param dVal Immediate value sued for the memory operation
/// \return -EINVAL if invalid arguments are passed, -EPERM if the passed instruction is not a valid memory instruction
/// returns 0 on success.
static int emitMemoryInstruction(asm_instr_et instructionType, reg_et reg, reg_et idx, uint32_t dVal)
{
    if (reg >= REG_NONE)
        return -EINVAL;

    if ((instructionType == INST_LD) || (instructionType == INST_LDI) || (instructionType == INST_ST))
    {
        fprintf(pAsmFile, "%s %s,#%d\n",
                INSTRUCTION(instructionType),
                REGISTER(reg),
                dVal & MAX_IMMED_LDI);
    }
    else if ((instructionType == INST_LDX) || (instructionType == INST_STX))
    {
        if (idx >= REG_NONE)
            return -EINVAL;

        fprintf(pAsmFile, "%s %s,%s,#%d\n",
                INSTRUCTION(instructionType),
                REGISTER(reg),
                REGISTER(idx),
                dVal & MAX_IMMED_LDX);
    }
    else
    {
        return -EPERM;
    }

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

static int loadImmOptimized(uint32_t dVal, reg_et destReg)
{
    int ret;

    if (VALID_LDI_IMMED(dVal))
    {
        ret = emitMemoryInstruction(INST_LDI, destReg, REG_NONE, dVal);
    }
    else
    {
        ret = loadImm32(dVal, destReg);
    }

    return ret;
}

static int generateAluOperation(OperatorType_et opType, TreeNode_st* pTreeNode, reg_et destReg)
{
    uint32_t memAddr;
    reg_et lReg = getNextAvailableReg();
    reg_et rReg = getNextAvailableReg();
    asm_instr_et asmInstruction = mapInstructionFromOperator(opType);

    if (L_CHILD_TYPE(pTreeNode) == NODE_INTEGER && R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
    {
        if (VALID_ALU_IMMED(L_CHILD_DVAL(pTreeNode)))
        {
            emitAluInstruction(asmInstruction, true, L_CHILD_DVAL(pTreeNode), destReg, lReg, REG_NONE);
        }
        else
        {

        }
    }
    else if (L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER && R_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
    {
        LOG_DEBUG("Un-Implemented condition!\n");
    }
    else
    {
        LOG_DEBUG("Un-Implemented condition!\n");
    }

    releaseReg(lReg);
    releaseReg(rReg);

    return 0;
}

static int parseOperatorNode(TreeNode_st* pTreeNode)
{
    reg_et lReg, rReg, dReg;
    OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;

    switch (opType)
    {
        case OP_PLUS:
        {

            break;
        }
        case OP_MINUS:
            break;
        case OP_RIGHT_SHIFT:
            break;
        case OP_LEFT_SHIFT:
            break;
        case OP_MULTIPLY:
            break;
        case OP_DIVIDE:
            break;
        case OP_REMAIN:
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
}

static int parseNode(TreeNode_st* pTreeNode)
{
    switch (pTreeNode->nodeType)
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
            parseOperatorNode(pTreeNode);
            break;
        case NODE_TERNARY:
            break;
        case NODE_IDENTIFIER:
            break;
        case NODE_STRING:
            break;
        case NODE_INTEGER:
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
}

/// \brief This function gets the first available register of the working register list
/// \return Register number or REG_NONE if no register is available
static reg_et getNextAvailableReg()
{
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {
        if (regStateList[i].isFree)
            return regStateList[i].regName;
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