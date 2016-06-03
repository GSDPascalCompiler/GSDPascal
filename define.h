#include <stdio>
#include <vector>
#include <string>

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

/*The node for STRING*/
typedef struct{
	string s;
}node_string;

/*The node for CONST*/
typedef struct{
	union{
		int i;
		double r;
		char c;
		string s;
	}
}node_const;

/*The node for ARR*/
typedef struct{
	string arrname;
}node_array;

/*The node for IDENTIFIER*/
typedef struct{
	string id;
}node_id;

/*The node for VARIOUS TYPES*/
typedef struct{
	int type;
}node_type;

typedef struct node;

/*Non-leaf node types*/
typedef struct{
	node *child;
}node_nonleaf;

/*The general node in parsetree*/
typedef struct{
	int type;
	union{
		node_integer n_integer;
		node_real n_real;
		node_char n_char;
		node_string n_string;
		node_const n_const;
		node_array n_array;
		node_id n_id;
		node_type n_type;
		node_nonleaf node_nonleaf;
	}data;
}pnode;

#define YYSTYPE pnode;
