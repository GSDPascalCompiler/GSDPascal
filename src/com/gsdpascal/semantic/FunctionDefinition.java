package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

import java.util.LinkedList;

public class FunctionDefinition {
	public String name;
	public LinkedList<SimpleType> paraList;
	public ExpressionType retType; /*record the return type*/
	public int nestLevel;

	public FunctionDefinition(String name, LinkedList<SimpleType> paraList, ExpressionType retType, int nestLevel) {
		this.name = name;
		this.paraList = paraList;
		this.retType = retType;
		this.nestLevel = nestLevel;
	}
}
