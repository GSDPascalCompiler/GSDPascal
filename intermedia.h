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

extern vector<Quad *> vecTAC;

void generateTAC(YYSTYPE & root);
void generateTACExpKind(YYSTYPE & root);
void generateTACStmtKind(YYSTYPE & root);
void printVecTAC();
void printAttr(Attribute &attr);