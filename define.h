#ifndef _DEFINE_H_
#define _DEFINE_H_

enum{N_INTEGER,N_REAL,N_CHAR,N_STRING,N_CONST,N_ARRAY,N_ID,N_TYPE,N_NONLEAF}NODE_TYPE;

/*Leaf node types*/
/*The node for INTEGER*/
typedef struct{
	int i;
}node_integer;

/*The node for REAL*/
typedef struct{
	double r;
}node_real;

/*The node for CHAR*/
typedef struct{
	char c;
}node_char;

/*The node for std::string*/
typedef struct{
	char s[256];
}node_string;

/*The node for CONST*/
typedef struct{
	union{
		int i;
		double r;
		char c;
		char s[256];
	}data;
}node_const;

/*The node for ARR*/
typedef struct{
	char s[256];
}node_array;

/*The node for IDENTIFIER*/
typedef struct{
	char id[256];
}node_id;

/*The node for VARIOUS TYPES*/
typedef struct{
	int type;
}node_type;

typedef struct tag_pnode pnode;

/*Non-leaf node types*/
typedef struct tag_nonleaf{
	tag_pnode *child;
}node_nonleaf;

/*The general node in parsetree*/
typedef struct tag_pnode{
	NODE_TYPE node_type;
	union{
		node_integer n_integer;
		node_real n_real;
		node_char n_char;
		node_string n_string;
		node_const n_const;
		node_array n_array;
		node_id n_id;
		node_type n_type;
		node_nonleaf n_nonleaf;
	}data;
}pnode;

#define YYSTYPE pnode;

#endif;
