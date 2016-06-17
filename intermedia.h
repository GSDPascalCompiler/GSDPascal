#pragma once
#include <vector>
#include "global.h"

using namespace std;

typedef enum { OP_RD, OP_GT, OP_IF_F, OP_ASN, OP_LAB, OP_MUL, OP_SUB, OP_EQ, OP_WRI, OP_HALT } OpKind;
typedef enum { ADDR_EMPTY, ADDR_INTCONST, ADDR_STRING } AddrKind;

class Quad {
public:
	OpKind op;
	AddrKind addr1, addr2, addr3;
};

vector<Quad *> vecTAC;

void generateTAC(YYSTYPE & root)
{
	switch (root.data.treeNode->nodeType)
	{
	case NODE_EXP: break;
	case NODE_STMT: break;
	case NODE_TOKEN: break;
	}
}

void generateTACStmtKind(YYSTYPE & root)
{
	switch (root.data.treeNode->typeValue.stmtType)
	{
	default:
		break;
	}
}

void generateTACExpKind(YYSTYPE & root)
{
	switch (root.data.treeNode->typeValue.expType)
	{
	case E_GE:
		break;
	case E_GT:
		break;
	case E_LE:
		break;
	case E_LT:
		break;
	case E_EQUAL:
		break;
	case E_UNEQUAL:
		break;
	case E_PLUS:
		break;
	case E_MINUS:
		break;
	case E_OR:
		break;
	case E_MUL:
		break;
	case E_DIV:
		break;
	case E_MOD:
		break;
	case E_AND:
		break;
	}
}