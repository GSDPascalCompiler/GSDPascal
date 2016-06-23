package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

public class SubBoundDefinition {
	public ExpressionType boundType;
	public Object LowerBound;
	public Object UpperBound;

	public SubBoundDefinition(ExpressionType boundType, Object lowerBound, Object upperBound) {
		this.boundType = boundType;
		LowerBound = lowerBound;
		UpperBound = upperBound;
	}
}