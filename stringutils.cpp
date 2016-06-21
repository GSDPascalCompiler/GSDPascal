#include "stringutils.h"

int string2Int(string s) {
	int ret;
	ret = atoi(s.c_str());
	return ret;
}

string int2string(int x)
{
	char tmp[16];
	_itoa(x, tmp, 10);
	return string(tmp);
}

string globalParaName(string name) {
	return "para_" + name;
}
