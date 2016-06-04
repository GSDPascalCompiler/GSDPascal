#include "util.h"

void printTreeNodes(TreeNode root, int level){
  if(root.nodeType == NODE_TOKEN){
    for(int i = 0; i < level; ++i)
      printf("----");
    printf("token:");
    switch (root.typeValue.tokenType)
    {
        case T_INTEGER:
          printf("%d\n", root.value.nodeInteger.i);
          break;
        case T_REAL:
          printf("%lf\n", root.value.nodeReal.r);
          break;
        case T_CHAR:
          printf("%c\n", root.value.nodeChar.c);
          break;
        case T_STRING:
          printf("%s\n", root.value.nodeString.s);
          break;
        case T_ID:
          printf("%s\n", root.value.nodeId.id);
          break;
        default:
          printf("others\n");
          ;
    }
  }
  else{
    for(int i = 0; i < 10; ++i){
      if(root.value.nodeNonleaf.child[i] != nullptr){
        printTreeNodes(*root.value.nodeNonleaf.child[i], level+1);
      }
    }
  }
}

void printParseTree(TreeNode *root)
{
  
}
