#ifndef _GLOBAL_H_
#define _GLOBAL_H_

enum TokeType{ N_READ, N_TYPE, //
 N_LP, N_RP, N_LB, N_RB, //
 N_PLUS, N_MINUS, N_MUL, N_DIV, MOD, AND, OR, NOT, ASSIGN, //
 N_GE, N_GT, N_LE, N_LT, N_EQUAL, N_UNEQUAL, //
 N_INTEGER, N_REAL, N_CHAR, N_STRING, N_CONST, N_ARRAY, //Leaf
 N_SYS_CON, N_SYS_TYPE, N_SYS_PROC, N_SYS_FUNCT, //
 N_PROGRAM, N_FUNCTION, N_PROCEDURE, N_RECORD, N_ID,N_NAME, N_VAR,//
 N_DOT, N_SEMI, N_COLON, N_COMMA,//
 N_OF, N_BEG, N_END, N_TO, N_DOWNTO,//
 N_IF, N_THEN, N_ELSE, N_REPEAT, N_UNTIL, N_WHILE, N_DO, N_FOR, N_GOTO, N_CASE};

/*Leaf node types*/
/*The node for INTEGER*/
typedef struct{
	int i;
}NodeInteger;

/*The node for REAL*/
typedef struct{
	double r;
}NodeReal;

/*The node for CHAR*/
typedef struct{
	char c;
}NodeChar;

/*The node for std::string*/
typedef struct{
	char s[256];
}NodeString;

/*The node for IDENTIFIER*/
typedef struct{
	char id[256];
}NodeId;

typedef struct TagTreeNode TreeNode;

/*Non-leaf node types*/
typedef struct TagNonleaf{
	TagTreeNode *child;
}NodeNonleaf;

/*The general node in parsetree*/
typedef struct tag_pnode{
	TokenType tokenType;
	union{
		NodeInteger nodeInteger;
		NodeReal nodeReal;
		NodeChar nodeChar;
		NodeString nodeString;
		NodeId nodeId;
		NodeNonleaf nodeNonleaf;
	}value;
}TreeNode;

#define YYSTYPE TreeNode

#endif
