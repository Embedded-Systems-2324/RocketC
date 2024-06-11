#include "fsm.h"

#include <stdio.h>
#include <stdint-gcc.h>
#include <stdbool.h>
#include <asm-generic/errno.h>
#include <stdlib.h>
#include <memory.h>
#include "Types/Instructions.h"
#include "Types/Registers.h"
#include "Log/Logger.h"
#include "Types/Branches.h"

#define IS_BIT_SET(x, n) (((x) >> (n)) & 0b1)

#define MAX_BREAK_POINTS 16

#define CODE_MEM_SIZE_BYTES 32768U

#define DATA_MEM_SIZE_WORDS 1024U

#define INT_CTRL_START      (DATA_MEM_SIZE_WORDS)
#define INT_CTRL_SIZE_WORDS 4U
#define INT_CTRL_END        (INT_CTRL_START + INT_CTRL_SIZE_WORDS)

#define GPIO_START          (INT_CTRL_END)
#define GPIO_SIZE_WORDS     4U
#define GPIO_END            (GPIO_START + GPIO_SIZE_WORDS)

#define UART_START          (GPIO_END)
#define UART_SIZE_WORDS     4U
#define UART_END            (UART_START + UART_SIZE_WORDS)

#define PS2_START           (UART_END)
#define PS2_SIZE_WORDS      4U
#define PS2_END             (PS2_START + PS2_SIZE_WORDS)

#define RESERVED            8U
#define TIMER_SIZE_WORDS    8U

#define CODE_MEM_SIZE_WORDS (CODE_MEM_SIZE_BYTES / 4U)

typedef enum
{
    ST_INIT,
    ST_MENU,
    ST_RUN,
    ST_ERROR
}fsm_state_et;

static fsm_state_et nextState;
static fsm_state_et currentState;

static uint8_t codeMem[CODE_MEM_SIZE_BYTES] = {0};
static uint32_t dataMem[DATA_MEM_SIZE_WORDS] = {0};

static uint32_t regFile[REG_NONE] = {0};
static uint32_t programCounter = 0;

static uint32_t breakpointList[MAX_BREAK_POINTS] = {0};
static size_t nofBreakpoints = 0;

static uint8_t zeroFlag = 0;
static uint8_t carryFlag = 0;
static uint8_t negativeFlag = 0;
static uint8_t overflowFlag = 0;

static bool haltFound = false;
static bool bKeepRunning = true;
static bool bEnableBreakpoints = false;

static const char* codeFileName;

static int64_t executeNextInstruction();
static void updateFlags(uint32_t leftOp, uint32_t rightOp, uint64_t resVal, uint8_t isSub);
static int64_t loadCodeFile(const char* srcFile);

static int64_t executeNop(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeAdd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeSub(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeOr(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeAnd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeNot(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeXor(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeRotateRight(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeRotateLeft(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeCmp(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeBxx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeJmp(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeLd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeLdi(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeLdx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeSt(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);
static int64_t executeStx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal);

static uint32_t readMem(uint32_t memAddr);
static void writeMem(uint32_t memAddr, uint32_t memVal);

static void stateInit();
static void stateMenu();
static void stateRun();
static void stateError();


static int64_t (*executeLut[])(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal) =
{
    executeNop,
    executeAdd,
    executeSub,
    executeOr,
    executeAnd,
    executeNot,
    executeXor,
    executeCmp,
    executeBxx,
    executeJmp,
    executeLd,
    executeLdi,
    executeLdx,
    executeSt,
    executeStx,
    executeRotateRight,
    executeRotateLeft
};

static int64_t loadCodeFile(const char* srcFile)
{
    int64_t ret;
    uint32_t codeAddr;
    uint32_t instructionData[4];

    if (!srcFile)
        return -EINVAL;

    FILE* fileDescriptor = fopen(srcFile, "r");
    if (!fileDescriptor)
        return -EIO;

    while (true)
    {
        ret = fscanf(fileDescriptor, "@%x %x %x %x %x\n",
                     &codeAddr,
                     &instructionData[0],
                     &instructionData[1],
                     &instructionData[2],
                     &instructionData[3]);

        if (ret != 5)
            break;

        if (codeAddr >= CODE_MEM_SIZE_BYTES)
            return -EPERM;

        codeMem[codeAddr]     = instructionData[3];
        codeMem[codeAddr + 1] = instructionData[2];
        codeMem[codeAddr + 2] = instructionData[1];
        codeMem[codeAddr + 3] = instructionData[0];
    }

    fclose(fileDescriptor);

    return 0;
}

static uint32_t signExtend(uint32_t x, uint32_t n)
{
    uint32_t mask = 1U << (n - 1);
    return (x ^ mask) - mask;
}

static int64_t executeNextInstruction()
{
    if (programCounter >= CODE_MEM_SIZE_BYTES)
    {
        LOG_ERROR("Program counter would exceed code memory size! Resetting CPU\n");
        return -EPERM;
    }

    uint32_t currentInstruction = (*(uint32_t*)&codeMem[programCounter]);
    opcode_et currentOpcode = (opcode_et) (currentInstruction >> 27);

    LOG_DEBUG("Current opcode: %d\n", currentOpcode);

    if (currentOpcode > OP_RL)
    {
        if (currentOpcode != OP_HALT)
            LOG_ERROR("Invalid Opcode! Resetting CPU\n");
        else
        {
            printf("HALT found! Stopping CPU!\n");
            haltFound = true;
            return programCounter;
        }
        return -EPERM;
    }

    register_et regDest = (register_et) ((currentInstruction >> 22) & 0b11111);
    register_et regLeft = (register_et) ((currentInstruction >> 17) & 0b11111);
    register_et regRight = (register_et) ((currentInstruction >> 11) & 0b11111);
    bool isImed = (currentInstruction >> 16) & 0b1;

    uint32_t imedVal = 0;

    if ((currentOpcode <= OP_CMP) || (currentOpcode == OP_JMP) || (currentOpcode == OP_RR) || (currentOpcode == OP_RL))
    {
        imedVal = signExtend(currentInstruction & 0b1111111111111111, 16);
    }
    else if ((currentOpcode < OP_LDX) || (currentOpcode == OP_ST))
    {
        imedVal = signExtend(currentInstruction & 0b1111111111111111111111, 22);
    }
    else
    {
        imedVal = signExtend(currentInstruction & 0b11111111111111111, 17);
    }

    return executeLut[currentOpcode](regDest, regLeft, regRight, isImed, imedVal);
}

static int64_t executeAdd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] + rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeSub(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] - rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, true);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeOr(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] | rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeAnd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] & rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeNot(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal = ~regFile[regLeft];
    updateFlags(regFile[regLeft], 0, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeXor(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] ^ rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeRotateRight(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;
    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] >> rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeRotateLeft(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;
    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] << rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);
    regFile[regDest] = tempVal;

    return programCounter + 4U;
}

static int64_t executeCmp(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint64_t tempVal;
    uint32_t rightOp;

    rightOp = isImed ? imedVal : regFile[regRight];
    tempVal = regFile[regLeft] - rightOp;
    updateFlags(regFile[regLeft], rightOp, tempVal, false);

    return programCounter + 4U;
}

static int64_t executeLd(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    regFile[regDest] = readMem(imedVal);

    return programCounter + 4U;
}

static int64_t executeLdi(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    regFile[regDest] = imedVal;

    return programCounter + 4U;
}

static int64_t executeLdx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint32_t targetAddress = regFile[regLeft] + (int32_t) imedVal;

    regFile[regDest] = readMem(targetAddress);

    return programCounter + 4U;
}

static int64_t executeSt(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    writeMem(imedVal, regFile[regDest]);

    return (int64_t) programCounter + 4U;
}

static int64_t executeStx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint32_t targetAddress = regFile[regLeft] + (int32_t) imedVal;

    writeMem(targetAddress, regFile[regDest]);

    return (int64_t) programCounter + 4U;
}

static int64_t executeNop(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    return (int64_t) programCounter + 4U;
}

static int64_t executeJmp(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint32_t targetAddress = regFile[regLeft] + imedVal;
    if (targetAddress >= CODE_MEM_SIZE_BYTES)
    {
        LOG_ERROR("Trying to jump to illegal address! Resetting CPU!\n");
        return -EPERM;
    }
    if (isImed)
        regFile[regDest] = programCounter + 4;

    return (int64_t) targetAddress;
}

static int64_t executeBxx(register_et regDest, register_et regLeft, register_et regRight, bool isImed, uint32_t imedVal)
{
    uint32_t currentInstruction = (*(uint32_t*)&codeMem[programCounter]);
    int32_t branchOffset = (int32_t) signExtend(currentInstruction & 0b11111111111111111111111, 23);
    branch_cond_et branchCondition = (branch_cond_et) ((currentInstruction >> 23) & 0b1111);

    bool isBranchTaken = false;

    switch (branchCondition)
    {
        case COND_BRA:
            isBranchTaken = true;
            break;
        case COND_BNV:
            isBranchTaken = false;
            break;
        case COND_BCC:
            isBranchTaken = !carryFlag;
            break;
        case COND_BCS:
            isBranchTaken = carryFlag;
            break;
        case COND_BVC:
            isBranchTaken = !overflowFlag;
            break;
        case COND_BVS:
            isBranchTaken = overflowFlag;
            break;
        case COND_BEQ:
            isBranchTaken = zeroFlag;
            break;
        case COND_BNE:
            isBranchTaken = !zeroFlag;
            break;
        case COND_BGE:
            isBranchTaken = ((!negativeFlag) && (!overflowFlag)) || (negativeFlag && overflowFlag);
            break;
        case COND_BLT:
            isBranchTaken = (negativeFlag && (!overflowFlag)) || ((!negativeFlag) && overflowFlag);
            break;
        case COND_BGT:
            isBranchTaken = (!zeroFlag) && ((!negativeFlag && !overflowFlag) || (negativeFlag && overflowFlag));
            break;
        case COND_BLE:
            isBranchTaken = zeroFlag || ((negativeFlag && (!overflowFlag)) || ((!negativeFlag) && overflowFlag));
            break;
        case COND_BPL:
            isBranchTaken = !negativeFlag;
            break;
        case COND_BMI:
            isBranchTaken = negativeFlag;
            break;
        default:
            LOG_ERROR("Invalid branch condition received!\n");
    }

    if (isBranchTaken)
        return programCounter + branchOffset + 4;

    return programCounter + 4;
}

static void updateFlags(uint32_t leftOp, uint32_t rightOp, uint64_t resVal, uint8_t isSub)
{
    overflowFlag = IS_BIT_SET(resVal, 32);
    carryFlag = IS_BIT_SET(resVal, 32);
    negativeFlag = IS_BIT_SET(resVal, 31);
    zeroFlag = resVal == 0;
}

static void writeMem(uint32_t memAddr, uint32_t memVal)
{
    if (memAddr < DATA_MEM_SIZE_WORDS)
    {
        dataMem[memAddr] = memVal;
    }
    else
    {
        LOG_ERROR("Un-handled memory address: 0x%x!\n", memAddr);
    }
}

static uint32_t readMem(uint32_t memAddr)
{
    uint32_t tempVal;
    char msgBuffer[16];

    if (memAddr < DATA_MEM_SIZE_WORDS)
        return dataMem[memAddr];

    //TODO: Improve this. Really simple example on how to mock a peripheral
    if (memAddr == (UART_START + 0x03))
    {
        printf("Waiting on UART RX value...\n");
        fgets(msgBuffer, 16, stdin);
        sscanf(msgBuffer, "%x\n", &tempVal);
        return tempVal;
    }

    LOG_ERROR("Un-handled memory address: 0x%x!\n", memAddr);

    return 0;
}

static int32_t setBreakPoint(uint32_t memAddr)
{
    if ((memAddr % 4) != 0)
        return -EINVAL;

    if (nofBreakpoints >= MAX_BREAK_POINTS)
        return -ENOBUFS;

    for (size_t i = 0; i < nofBreakpoints; ++i)
    {
        if (memAddr == breakpointList[nofBreakpoints])
        {
            LOG_ERROR("Trying to insert breakpoint at already set address!\n");
            return -EPERM;
        }
    }

    breakpointList[nofBreakpoints] = memAddr;
    nofBreakpoints++;

    return 0;
}

void fsmInit(const char* fileName)
{
    codeFileName = fileName;
    nextState = ST_INIT;
}

void fsmEncode()
{
    while (bKeepRunning)
    {
        currentState = nextState;
            switch (currentState)
        {
            case ST_INIT:
                stateInit();
                break;
            case ST_MENU:
                stateMenu();
                break;
            case ST_RUN:
                if (haltFound)
                    nextState = ST_MENU;
                else stateRun();
                break;
            case ST_ERROR:
                stateError();
                break;
        }
    }
}

static void stateInit()
{
    memset(codeMem, OP_HALT, sizeof(codeMem));

    int64_t ret = loadCodeFile(codeFileName);

    if (ret != 0)
    {
        LOG_ERROR("Failed to open code file!\n");
        nextState = ST_ERROR;
    }
    else
    {
        nextState = ST_MENU;
    }
}
static void stateMenu()
{
    int32_t ret;
    uint32_t menuOption;
    uint32_t targetAddress;
    uint32_t startAddress;
    uint32_t endAddress;

    char msgBuffer[128];

    printf("1. Free Run\n"
           "2. Goto next breakpoint\n"
           "3. Set breakpoint\n"
           "4. Dump registers\n"
           "5. Dump memory\n"
           "6. Exit\n");

    fflush(stdin);
    fgets(msgBuffer, 128, stdin);
    ret = sscanf(msgBuffer, "%d", &menuOption);
    if ((ret != 1) || (menuOption > 6) || (menuOption < 1))
    {
        printf("Invalid option provided!\n");
        nextState = ST_MENU;
        return;
    }

    switch (menuOption)
    {
        case 1:
            bEnableBreakpoints = false;
            nextState = ST_RUN;
            break;
        case 2:
            bEnableBreakpoints = true;
            nextState = ST_RUN;
            break;
        case 3:
            ret = sscanf(msgBuffer, "%d 0x%x\n", &menuOption, &targetAddress);
            if (ret != 2)
            {
                printf("Invalid syntax used! Example to set a breakpoint at memory address 0x100: 3 0x100\n");
            }
            else
            {
                ret = setBreakPoint(targetAddress);
                if (ret == 0)
                {
                    printf("Breakpoint set at address: 0x%x\n", targetAddress);
                }
                nextState = ST_MENU;
            }
            break;
        case 4:
            for (uint8_t i = 0;  i < 32; ++ i)
                printf("R%d -> %u\n", i, regFile[i]);

            printf("PC -> %u\n", programCounter);
            nextState = ST_MENU;
            break;
        case 5:
            ret = sscanf(msgBuffer, "%d 0x%x 0x%x\n", &menuOption, &startAddress, &endAddress);
            if (ret != 3)
            {
                printf("Invalid syntax used! Example to dump memory from 0x0 to 0x10: 5 0x0 0x10\n");
            }
            else
            {
                if (endAddress >= DATA_MEM_SIZE_WORDS)
                    endAddress = DATA_MEM_SIZE_WORDS - 1;

                for (uint32_t i = startAddress; i < endAddress; ++i)
                    printf("Memory @ 0x%x -> %u\n", i, dataMem[i]);
            }

            nextState = ST_MENU;
            break;
        case 6:
            bKeepRunning = false;
            break;
        default:
            LOG_ERROR("Invalid menu option!\n");
            nextState = ST_MENU;
    }
}

static void stateRun()
{
    int64_t ret;
    static uint32_t lastBreakpointHit = 0xFFFFFFFF;

    if (bEnableBreakpoints)
    {
        for (size_t i = 0; i < nofBreakpoints; ++i)
        {
            if ((breakpointList[i] == programCounter) && (programCounter != lastBreakpointHit))
            {
                lastBreakpointHit = programCounter;
                printf("Breakpoint hit at code address: 0x%x!\n", programCounter);
                nextState = ST_MENU;
                return;
            }
        }
        nextState = ST_MENU;
    }

    ret = executeNextInstruction();
    if (ret < 0)
    {
        nextState = ST_ERROR;
    }
    else
    {
        programCounter = ret;
        nextState = ST_RUN;
    }

}

static void stateError()
{
    LOG_ERROR("Entered error state!\n");
    bKeepRunning = false;
}
