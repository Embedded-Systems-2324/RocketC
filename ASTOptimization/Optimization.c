#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../SemanticAnalyzer/traverse.h"
#include "../ASTOptimization/Optimization.h"

static void optimizeAST(TreeNode_st* pTreeRoot);
static int operationInt(int a, int b, long op);
static double operationDouble(double a, double b, long op);

static void optimizeAST(TreeNode_st* pTreeRoot)
{   
    TreeNode_st* pChild1;
    TreeNode_st* pChild2;

    pChild1 = &pTreeRoot->pChilds[0];
    pChild2 = &pTreeRoot->pChilds[1]; 

        if(pTreeRoot->nodeType == NODE_OPERATOR) {
            switch(pTreeRoot->nodeData.dVal){

                case OP_BITWISE_NOT:
                    if(pChild1->nodeType == NODE_INTEGER)
                    {	
                        pTreeRoot->nodeType = NODE_INTEGER;
                        pTreeRoot->nodeData.dVal = operationInt(pChild1->nodeData.dVal, 0, pTreeRoot->nodeData.dVal);
                        free(pTreeRoot->pChilds);
                        pTreeRoot->childNumber = 0;
                    }
                break;

                case OP_PLUS:
                case OP_MINUS:
                case OP_MULTIPLY:
                case OP_DIVIDE:
                case OP_REMAIN:

                    if(pChild1->nodeType == NODE_INTEGER && pChild2->nodeType == NODE_INTEGER)
                    {	
                        pTreeRoot->nodeType = NODE_INTEGER;
                        pTreeRoot->nodeData.dVal = operationInt(pChild1->nodeData.dVal, pChild2->nodeData.dVal, pTreeRoot->nodeData.dVal);
                        free(pTreeRoot->pChilds);
                        pTreeRoot->childNumber = 0;
                        
                    }else if(pChild1->nodeType == NODE_FLOAT && pChild2->nodeType == NODE_FLOAT){

                        pTreeRoot->nodeType = NODE_FLOAT;
                        pTreeRoot->nodeData.fVal = operationDouble(pChild1->nodeData.fVal, pChild2->nodeData.fVal, pTreeRoot->nodeData.dVal);
                        free(pTreeRoot->pChilds);
                        pTreeRoot->childNumber = 0;
                    }
                break;

                case OP_RIGHT_SHIFT:
                case OP_LEFT_SHIFT:
                case OP_BITWISE_AND:
                case OP_BITWISE_OR:
                case OP_BITWISE_XOR:

                    if(pChild1->nodeType == NODE_INTEGER && pChild2->nodeType == NODE_INTEGER)
                    {	
                        pTreeRoot->nodeType = NODE_INTEGER;
                        pTreeRoot->nodeData.dVal = operationInt(pChild1->nodeData.dVal, pChild2->nodeData.dVal, pTreeRoot->nodeData.dVal);
                        free(pTreeRoot->pChilds);
                        pTreeRoot->childNumber = 0;
                        
                    }
                break;

                default:
                    break;
            }
        }
    return;
}

static double operationDouble(double a, double b, long op){

    switch(op) {
        case OP_PLUS:
            return a + b;
        case OP_MINUS:
            return a - b;
        case OP_MULTIPLY:
            return a * b;
        case OP_DIVIDE:
            if (b != 0) {
                return a / b;
            } else {
                LOG_ERROR_SHORT("Cant divide by 0\n");
                return 0.0;
            }
        default:
            LOG_ERROR_SHORT("Invalid Operation\n");
            return 0.0;
    }
}

static int operationInt(int a, int b, long op) {
    switch(op) {
        case OP_PLUS:
            return a + b;
        case OP_MINUS:
            return a - b;
        case OP_RIGHT_SHIFT:
            return a >> b;
        case OP_LEFT_SHIFT:
            return a << b;
        case OP_MULTIPLY:
            return a * b;
        case OP_DIVIDE:
            if (b != 0) {
                return a / b;
            } else {
                LOG_ERROR_SHORT("Cant divide by 0\n");
                return 0.0;
            }
        case OP_REMAIN:
            return a % b;
        case OP_BITWISE_AND:
            return a & b;
        case OP_BITWISE_NOT:
            return ~a;
        case OP_BITWISE_OR:
            return a | b;
        case OP_BITWISE_XOR:
            return a ^ b;
        default:
            LOG_ERROR_SHORT("Invalid Operation\n");
            return 0.0;
    }
}

int executeOptimization(TreeNode_st* pTreeRoot)
{       
        if (!pTreeRoot)
        return -EINVAL;

        traverse(pTreeRoot,nullProc,optimizeAST);
        return 0;
}