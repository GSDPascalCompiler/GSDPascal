package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

public class SimpleType {
	public String name;
	public ExpressionType type;
	public boolean isVar;

	public SimpleType(String name, ExpressionType type, boolean isVar) {
		this.name = name;
		this.type = type;
		this.isVar = isVar;
	}
}

