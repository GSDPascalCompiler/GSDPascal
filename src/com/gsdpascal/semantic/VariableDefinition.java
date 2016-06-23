package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

/*record the definition of each variable*/
public class VariableDefinition {
	public String name;
	public ExpressionType type;
	public boolean isConst;
	public int nestLevel;
	public Object pAttr;
	public MemPos memPos;

	public VariableDefinition(String name, ExpressionType type, boolean isConst, int nestLevel, Object pAttr, int offset) {
		this.name = name;
		this.type = type;
		this.isConst = isConst;
		this.nestLevel = nestLevel;
		this.pAttr = pAttr;
		this.memPos = new MemPos(0, offset);
	}
}
