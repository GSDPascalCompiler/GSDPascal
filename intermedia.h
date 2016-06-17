#pragma once
#include <vector>
#include <iostream>
#include "global.h"
#include "util.h"

using namespace std;

typedef enum { OP_GE, OP_GT, OP_LE, OP_LT, OP_EQUAL, OP_UNEQUAL, OP_PLUS, OP_MINUS, OP_OR, OP_MUL, OP_DIV, OP_MOD, OP_AND} OpKind;

class Quad {
public:
	OpKind op;
	Attribute addr1, addr2, addr3;
	Quad(OpKind opKind, Attribute a1, Attribute a2, Attribute a3) :op(opKind), addr1(a1), addr2(a2), addr3(a3) {}
};

vector<Quad *> vecTAC;

void printAttr(Attribute &attr)
{
	cout << attr.attrName << ":";
	switch (attr.attrType)
	{
	case A_VOID: cout << "A_VOID"; break;
	case A_BOOLEAN: cout << "A_BOOLEAN"; break;
	case A_INTEGER: cout << "A_INTEGER"; break;
	case A_REAL:cout << "A_REAL"; break;
	case A_CHAR:cout << "A_CHAR"; break;
	case A_STRING:cout << "A_STRING"; break;
	case A_ARRAY:cout << "A_ARRAY"; break;
	case A_RECORD:cout << "A_RECORD"; break;
	case A_TYPE:cout << "A_TYPE"; break;
	}
	cout << " ";
}

void printVecTAC()
{
	cout << endl;
	for (auto quad : vecTAC)
	{
		switch (quad->op)
		{
		case OP_GE: cout << "GE" ; break;
		case OP_GT: cout << "GT"; break;
		case OP_LE: cout << "LE"; break;
		case OP_LT:cout << "LT"; break;
		case OP_EQUAL:cout << "EQUAL"; break;
		case OP_UNEQUAL:cout << "UNEQUAL" ; break;
		case OP_PLUS:cout << "PLUS"; break;
		case OP_MINUS:cout << "MINUS" ; break;
		case OP_OR:cout << "OR" ; break;
		case OP_MUL:cout << "MUL" ; break;
		case OP_DIV: cout << "DIV" ; break;
		case OP_MOD:cout << "MOD" ; break;
		case OP_AND:cout << "AND" ; break;
		}
		cout << " ";
		printAttr(quad->addr1);
		printAttr(quad->addr2);
		printAttr(quad->addr3);
		cout << endl;
	}
}

void generateTACStmtKind(YYSTYPE & root)
{
	auto rootNode = root.data.treeNode;
	auto left = getNthChild(root, 1);
	auto right = getNthChild(root, 2);
	Attribute none;
	none.attrName = "";
	none.attrType = A_VOID;
	switch (root.data.treeNode->typeValue.stmtType)
	{
		case S_ASSIGN:
			vecTAC.push_back(new Quad(OP_PLUS, left->attribute, right->attribute, none)); break;
	default:
		break;
	}
}

void generateTACExpKind(YYSTYPE & root)
{
	auto rootNode = root.data.treeNode;
	auto left = getNthChild(root, 1);
	auto right = getNthChild(root, 2);
	switch (root.data.treeNode->typeValue.expType)
	{
	case E_GE:
		vecTAC.push_back(new Quad(OP_GE, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_GT:
		vecTAC.push_back(new Quad(OP_GT, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_LE:
		vecTAC.push_back(new Quad(OP_LE, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_LT:
		vecTAC.push_back(new Quad(OP_LT, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_EQUAL:
		vecTAC.push_back(new Quad(OP_EQUAL, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_UNEQUAL:
		vecTAC.push_back(new Quad(OP_UNEQUAL, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_PLUS:
		vecTAC.push_back(new Quad(OP_PLUS, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_MINUS:
		vecTAC.push_back(new Quad(OP_MINUS, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_OR:
		vecTAC.push_back(new Quad(OP_OR, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_MUL:
		vecTAC.push_back(new Quad(OP_MUL, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_DIV:
		vecTAC.push_back(new Quad(OP_DIV, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_MOD:
		vecTAC.push_back(new Quad(OP_MOD, rootNode->attribute, left->attribute, right->attribute));
		break;
	case E_AND:
		vecTAC.push_back(new Quad(OP_AND, rootNode->attribute, left->attribute, right->attribute));
		break;
	}
}

void generateTAC(YYSTYPE & root)
{
	switch (root.data.treeNode->nodeType)
	{
	case NODE_EXP: generateTACExpKind(root); break;
	case NODE_STMT: generateTACStmtKind(root); break;
	}
}