#include "globals.h"
#include "useful.h"

TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",linenum);
  else {
    //printf(" [DEBUG: New Statement Created]\n");
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = linenum;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",linenum);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = linenum;
    t->type = Void;
  }
  return t;
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;

  //INDENT;
  while (tree != NULL) {
    //printSpaces();
    if (tree->nodekind==StmtK)
    { 
      switch (tree->kind.stmt) {
        case GotoK:
          printf("Tree: GoTo\n");
          break;
        case LabelK:
          printf("Tree: Label\n");
          break;
        case IfK:
          printf("Tree: If\n");
          break;
        case ForK:
          printf("Tree: For\n");
          break;
        case WhileK:
          printf("Tree: While\n");
          break;
        case SwitchK:
          printf("Tree: Switch\n");
          break;
        case DowhileK:
          printf("Tree: Do While\n");
          break;
        case ReturnK:
          printf("Tree: Return\n");
          break;
        case DeclarationK:
          printf("Tree: Declaration\n");
          break;
        case AssignmentK:
          printf("Tree: Assign\n");
          break;
        case InstantiationK:
          printf("Tree: Instantiation\n");
          break;
        case ContinueK:
          printf("Tree: Continue\n");
          break;
        case BreakK:
          printf("Tree: Break\n");
          break;
        case COMPOUNDK:
          printf("Tree: Compound statements\n");
          break;
        case FuncDeclarationK:
          printf("Tree: Function Declaration\n");
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          printf("Op: ");
          //printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          printf("Const: %d\n",tree->attr.val);
          break;
        case IdK:
          printf("Id: %s\n",tree->attr.name);
          break;
        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else printf("Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  //UNINDENT;
}