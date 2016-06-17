typedef enum { OP_RD, OP_GT, OP_IF_F, OP_ASN, OP_LAB, OP_MUL, OP_SUB, OP_EQ, OP_WRI, OP_HALT } OpKind;
typedef enum { ADDR_EMPTY, ADDR_INTCONST, ADDR_STRING } AddrKind;

struct Quad {
	OpKind op;
	AddrKind addr1, addr2, addr3;
};