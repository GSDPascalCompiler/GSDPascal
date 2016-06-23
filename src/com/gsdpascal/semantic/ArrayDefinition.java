package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

public class ArrayDefinition {
	public ExpressionType arrayType;
	public SubBoundDefinition subBound;

	public ArrayDefinition(ExpressionType arrayType, ExpressionType boundType, Object upper, Object lower) {
		this.arrayType = arrayType;
		this.subBound = new SubBoundDefinition(boundType, upper, lower);
	}
}
