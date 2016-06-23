package com.gsdpascal.semantic;

import java.util.LinkedList;

public class RecordDefinition {
	public RecordType type;
	public LinkedList<TypeDefinition> ptr; // Attribute in the record

	public RecordDefinition(RecordType type, LinkedList<TypeDefinition> ptr) {
		this.type = type;
		this.ptr = ptr;
	}
}