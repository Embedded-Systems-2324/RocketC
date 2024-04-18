#include <stdint.h>
#include <errno.h>
#include "../main.h"
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

static inline bool isSimpleType(ExpType type) { 
    return (type == EXP_VOID || type == EXP_INT || type == EXP_CHAR || type == EXP_FLOAT || type == EXP_DOUBLE);
}

static inline TreeNode_st* TreeNode(void *pointer) {
    return (TreeNode_st*)pointer;
}

//#define is_SimpleType(NODE) (NODE->nodeData.dVal == TYPE_CHAR || NODE->nodeData.dVal == TYPE_INT || NODE->nodeData.dVal == TYPE_FLOAT || NODE->nodeData.dVal == TYPE_DOUBLE)


static bool typeEqual (TreeNode_st* t1, TreeNode_st* t2)
{   
    int Type1 = t1->nodeData.dVal;
    int Type2 = t2->nodeData.dVal;
    bool temp;
    TreeNode_st *p1;
    TreeNode_st *p2;

    /// @cond If they are the same type  OR  If they are both a simple type(ex: int, int;  int,float --> TRUE)
    /// @return TRUE:
    if( (ExpType)t1 == (ExpType)t2 || (isSimpleType(t1) && isSimpleType(t2)) )  //after we need to decide what simple ops can be operated toghether                
        return true;

    /// @cond If both nodes are arrays
    /// @return TRUE: If NODE1->SIZE = NODE2->SIZE  AND  NODE1->TYPE = NODE2->TYPE
    /// @brief TreeNode(t1)->pChilds->pSibling =>  ARRAY second child, i.e the Size
    /// TreeNode(t1)->pChilds => ARRAY first child, i.e the type
    else if( TreeNode(t1)->type == EXP_ARRAY && TreeNode(t2)->type == EXP_ARRAY )          //ARRAY                                                                                          
        return (TreeNode(t1)->pChilds->pSibling == TreeNode(t2)->pChilds->pSibling  &&  typeEqual(TreeNode(t1)->pChilds, TreeNode(t2)->pChilds)); 

    /// @cond If both nodes are structs  OR If both nodes are unions
    /// @return
    else if(TreeNode(t1)->type==EXP_STRUCT && TreeNode(t2)->type==EXP_STRUCT || TreeNode(t1)->type==EXP_UNION && TreeNode(t2)->type==EXP_UNION)  //STRUCTS OR UNIONS
    {
      p1 = TreeNode(t1)->pChilds;                        //aponta pro primeiro membro das structs
      p2 = TreeNode(t2)->pChilds;
      temp = true;
      while(temp && p1!=NULL && p2!=NULL)                //ate ser falso ou ate chegar ao ultimo membro da struct
      {
        if(p1.name != p2.name)    //tabela de simbolos????                       //compara os nomes dos membros das mesmas posiçoes 
          temp = false;
        else if ( ! typeEqual(p1->pChilds, p2->pChilds)) //compara os tipos dos membros das mesmas posiçoes
          temp = false;
        else
        {                                                //itera para outro membro
          p1 = p1->pSibling;
          p2 = p2->pSibling;
        }
      }
      return temp && p1!=NULL && p2 !=NULL;
    }

    /// @cond If both nodes are pointers
    /// @return TRUE: IF they have the same type
    else if(TreeNode(t1)->type==EXP_POINTER && TreeNode(t2)->type==EXP_POINTER)                                         //POINTER
        return typeEqual(TreeNode(t1)->pChilds, TreeNode(t2)->pChilds);


    else if(TreeNode(t1)->type==EXP_FUNCTION && TreeNode(t2)->type==EXP_FUNCTION)                                      //FUNCTION
    { 
        p1 = TreeNode(t1)->pChilds; 
        p2 = TreeNode(t2)->pChilds; 
        temp = true;
        //precorre e compara todos os argumentos da funçao para ver se a chamada de funçao corresponde ao prototipo, ate nao serem iguais ou ate acabar os argumentos
        while(temp && p1!=NULL && p2!=NULL)
        {
        if ( ! typeEqual(p1->pChilds, p2->pChilds))
            temp = false;
        else
        {
            p1 = p1->pSibling;
            p2 = p2->pSibling;
        }
        }
        return temp && p1==NULL && p2 ==NULL && typeEqual(TreeNode(t1)->pChilds, TreeNode(t2)->pChilds);    //Se ambas as funçoes retornarem o mesmo tipo de dados podemos dizer q sao equivalentes
    }


    /*else if( t1 && t2 forem nomes de tipos)
        return typeEqual( getTypeExp(t1), getTypeExp(t2) );*/



    return false;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode_st* N)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"assignment of non-integer value");
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"write of non-integer value");
          break;
        case RepeatK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
