package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;

public class TypeDefinition implements Comparable {
	public String name; // 用在typeHashTable里面的时候，name表示类型的名称，用在RecordNode中的时候，name表示record成员变量的名字
	public ExpressionType type;
	public int nestLevel;
	public Object pAttr;
	public int size;

	public TypeDefinition(String name) {
		this.name = name;
	}

	public TypeDefinition(String name, ExpressionType type, int nestLevel, Object pAttr, int size) {
		this.name = name;
		this.type = type;
		this.nestLevel = nestLevel;
		this.pAttr = pAttr;
		this.size = size;
	}

	@Override
	public int compareTo(Object o) {
		if (o instanceof TypeDefinition) {
			TypeDefinition another = (TypeDefinition)o;
			return name.compareTo(another.name);
		} else {
			return -1;
		}
	}

	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof TypeDefinition)) {
			return false;
		}
		TypeDefinition another = (TypeDefinition)obj;
		return name.equals(another.name);
	}
}