#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#define MAX_STR_LEN 256
#define MAX_CHILD_NUM 10

enum NodeType{NODE_TOKEN, NODE_EXP, NODE_STMT};

enum TokeType{T_READ, T_TYPE, //
 T_LP, T_RP, T_LB, T_RB, //
 T_PLUS, T_MINUS, T_MUL, T_DIV, MOD, AND, OR, NOT, ASSIGN, //
 T_GE, T_GT, T_LE, T_LT, T_EQUAL, T_UNEQUAL, //
 T_INTEGER, T_REAL, T_CHAR, T_STRING, T_CONST, T_ARRAY, //Leaf
 T_SYS_CON, T_SYS_TYPE, T_SYS_PROC, T_SYS_FUNCT, //
 T_PROGRAM, T_FUNCTION, T_PROCEDURE, T_RECORD, T_ID,T_NAME, T_VAR,//
 T_DOT, T_SEMI, T_COLON, T_COMMA,//
 T_OF, T_BEG, T_END, T_TO, T_DOWNTO,//
 T_IF, T_THEN, T_ELSE, T_REPEAT, T_UNTIL, T_WHILE, T_DO, T_FOR, T_GOTO, T_CASE,
 T_NONLEAF};

 enum StmtType{S_PROGRAM, S_PROGRAM_HEAD, S_ROUTINE, S_ROUTINE_HEAD, S_LABEL_PART_NULL,
 	S_CONST_PART_NULL, S_CONST_EXPR_MULT_LIST, S_CONST_EXPR_LIST, S_TYPE_PART, S_TYPE_PART_NULL, S_TYPE_DECL_LIST,
 	S_TYPE_DEFINITION, S_SIMPLE_TYPE_DECL_CDC, S_SIMPLE_TYPE_DECL_MCDC, S_SIMPLE_TYPE_DECL_IDI,
 	S_ARRAY_TYPE_DECL, S_FILED_DECL_LIST, S_FILED_DECL, S_NAME_LIST, S_VAR_DECL_LIST,
 	S_VAR_DEL, S_ROUTINE_PART_FUNC_LIST, S_ROUTINE_PART_PROC_LIST, S_ROUTINE_NULL, S_FUNCTION_DECL,
 	S_FUNCTION_HEAD, S_PROCEDURE_DECL, S_PROCEDURE_HEAD, S_PARAMETERS_NULL,
 	S_PARA_DECL_MULTI_LIST, S_PARA_TYPE_LIST_VAR, S_PARA_TYPE_LIST_VAL, };

enum SysConVal{FALSE, MAXINT, TRUE};
enum SysFunctVal{ABS, CHR, ODD, ORD, PRED, SQR, SQRT, SUCC};
enum SysProcVal{WRITE, WRITELN};
enum SysType{BOOLEAN, CHAR, INTEGER, REAL};

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
	char s[MAX_STR_LEN];
}NodeString;

/*The node for IDENTIFIER*/
typedef struct{
	char id[MAX_STR_LEN];
}NodeId;

typedef struct{
  SysConVal sysConVal;
}NodeSysConVal;

typedef struct{
  SysConVal sysConVal;
}NodeSysFunctVal;

typedef struct{
  SysConVal sysConVal;
}NodeSysProcVal;

typedef struct{
  SysConVal sysConVal;
}NodeSysTypeVal;

typedef struct TagTreeNode TreeNode;

/*Non-leaf node types*/
typedef struct TagNonleaf{
	TagTreeNode *child[MAX_CHILD_NUM];
}NodeNonleaf;

/*The general node in parsetree*/
typedef struct TagTreeNode{
	NodeType nodeType;
	union{
			TokenType tokenType;
			ExpType expType;
			StmtType stmtType;
	}typeValue;
	int lineno;
	int column;
	union{
		NodeInteger nodeInteger;
		NodeReal nodeReal;
		NodeChar nodeChar;
		NodeString nodeString;
		NodeId nodeId;
    NodeSysConVal nodeSysConVal;
    NodeSysFunctVal nodeSysFunctVal;
    NodeSysTypeVal nodeSysTypeVal;
    NodeSysProcVal nodeSysProcVal;
    NodeSysTypeVal nodeSysTypeVal;
		NodeNonleaf nodeNonleaf;
	}value;
}TreeNode;

typedef struct{
	union{
		TreeNode *treeNode;
		double r;
		int i;
		char c;
		char s[MAX_STR_LEN];
    SysConVal sysConVal;
    SysFunctVal sysFunctVal;
    SysProcVal sysProcVal;
    SysTypeVal sysTypeVal;
	}data;
  TokeType tokenType;
	int lineno;
	int column;
}Value;

#define YYSTYPE Value;
#endif
