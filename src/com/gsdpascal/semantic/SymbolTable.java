package com.gsdpascal.semantic;

import com.gsdpascal.astree.DeclarationKind;
import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.TreeNode;
import com.gsdpascal.astree.TypeKind;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;

/**
 * Created by gsdpascal on 15/6/30.
 */
public class SymbolTable {

    private final static int ERROR_RETURN = 0xffff;
    private final static int OFFSET_INC = 4;
    private final static int MAXSIZE = 256;

    private static int currentNestLevel = 0;
    private static int offset = 0;

    private static HashMap<String, LinkedList<VariableDefinition> > VariableDefinitionHashMap = new HashMap<>();

    private static HashMap<String, LinkedList<TypeDefinition> > TypeDefinitionHashMap = new HashMap<>();

    private static HashMap<String, LinkedList<FunctionDefinition> > FunctionDefinitionHashMap = new HashMap<>();

    private static HashMap<String, LinkedList<ProcedureDefinition> > ProcedureDefinitionHashMap = new HashMap<>();

    private static int[] totalOffset = new int[MAXSIZE];

    public static int addProcOrFunc(TreeNode headNode) {
        boolean isFunc = (headNode.getNodeType() == DeclarationKind.FUNCTIONHEAD);
        String name = (String)headNode.getAttribute();
        int nestLevel = currentNestLevel;
        int paraNestLevel = nestLevel + 1;
        int offset = 4;

        LinkedList<SimpleType> paraList = new LinkedList<>();
        TreeNode paraDeclListNode = headNode.getChildren().get(0);

        while (paraDeclListNode != null) {
            TreeNode nameListNode = paraDeclListNode.getChildren().get(0);
            TreeNode typeNode = paraDeclListNode.getChildren().get(1);
            boolean isVar;
            if (paraDeclListNode.getNodeType() == DeclarationKind.VAR_PARA) { // 是传递实参还是形参
                isVar = true;
            } else {
                isVar = false;
            }
            while (nameListNode != null) {
                SimpleType para = new SimpleType((String)nameListNode.getAttribute(), typeNode.getExpType(), isVar);
                paraList.add(para);
                insertVariable(new VariableDefinition(para.name, para.type, false, paraNestLevel, null, offset), headNode.getLineNumber());
                offset += OFFSET_INC;
                nameListNode = nameListNode.getSibling();
            }
            paraDeclListNode = paraDeclListNode.getSibling();
        }
        if (paraList.size() == 0) {
            paraList = null;
        }

        if (isFunc) {
            // 插入函数返回值
            ExpressionType retType = headNode.getChildren().get(1).getExpType();
            insertVariable(new VariableDefinition((String)headNode.getAttribute(), retType, false, paraNestLevel, null, offset), headNode.getLineNumber());
            offset += OFFSET_INC;

            // 插入函数
            LinkedList<FunctionDefinition> FunctionDefinitions = FunctionDefinitionHashMap.get(name);
            if (FunctionDefinitions == null) {
                FunctionDefinitions = new LinkedList<>();
                FunctionDefinitionHashMap.put(name, FunctionDefinitions);
            }
            FunctionDefinitions.addFirst(new FunctionDefinition(name, paraList, retType, nestLevel));

        } else {
            LinkedList<ProcedureDefinition> ProcedureDefinitions = ProcedureDefinitionHashMap.get(name);
            if (ProcedureDefinitions == null) {
                ProcedureDefinitions = new LinkedList<>();
                ProcedureDefinitionHashMap.put(name, ProcedureDefinitions);
            }
            ProcedureDefinitions.addFirst(new ProcedureDefinition(name, paraList, nestLevel));
        }

        return offset;
    }

    private static void insertVariable(VariableDefinition VariableDefinition, int lineNumber) {
        String name = VariableDefinition.name;
        LinkedList<VariableDefinition> definedVar = VariableDefinitionHashMap.get(name);
        if (definedVar == null) {
            definedVar = new LinkedList<>();
            VariableDefinitionHashMap.put(name, definedVar);
        }
        int nestLevel = VariableDefinition.nestLevel;
        if (definedVar.size() == 0 || nestLevel > definedVar.getFirst().nestLevel) {
            definedVar.addFirst(VariableDefinition);
        } else {
            System.err.println("Redefine variable: " + name + " in line " + lineNumber);
        }
    }

    private static void insertType(TypeDefinition TypeDefinition, int lineNumber) {
        String name = TypeDefinition.name;
        LinkedList<TypeDefinition> definedType = TypeDefinitionHashMap.get(name);
        if (definedType == null) {
            definedType = new LinkedList<>();
            TypeDefinitionHashMap.put(name, definedType);
        }
        int nestLevel = TypeDefinition.nestLevel;
        if (definedType.size() == 0 || nestLevel > definedType.getFirst().nestLevel) {
            definedType.add(TypeDefinition);
        } else {
            System.err.println("Redefine type: " + name + " in line " + lineNumber);
        }
    }

    public static VariableDefinition lookupVar(String name) {
        LinkedList<VariableDefinition> varInfos = VariableDefinitionHashMap.get(name);
        if (varInfos == null || varInfos.size() == 0) {
            return null;
        } else {
            VariableDefinition ret = varInfos.getFirst();
            ret.memPos.basePos = currentNestLevel - ret.nestLevel;
            return ret;
        }
    }

    public static TypeDefinition lookupType(String name) {
        LinkedList<TypeDefinition> TypeDefinitions = TypeDefinitionHashMap.get(name);
        if (TypeDefinitions == null || TypeDefinitions.size() == 0) {
            return null;
        } else {
            return TypeDefinitions.getFirst();
        }
    }

    public static ProcedureDefinition lookupProc(String name) {
        LinkedList<ProcedureDefinition> ProcedureDefinitions = ProcedureDefinitionHashMap.get(name);
        if (ProcedureDefinitions == null || ProcedureDefinitions.size() == 0) {
            return null;
        } else {
            return ProcedureDefinitions.getFirst();
        }
    }

    public static FunctionDefinition lookupFunc(String name) {
        LinkedList<FunctionDefinition> FunctionDefinitions = FunctionDefinitionHashMap.get(name);
        if (FunctionDefinitions == null || FunctionDefinitions.size() == 0) {
            return null;
        } else {
            return FunctionDefinitions.getFirst();
        }
    }

    public static LookupReturn lookupRecord(String rec, String a) {
        VariableDefinition l = lookupVar(rec);
        LinkedList<TypeDefinition> members;
        LookupReturn ret = new LookupReturn(ERROR_RETURN, ERROR_RETURN, ExpressionType.VOID);
        if (l.type != ExpressionType.RECORD || l.pAttr == null) {
            return ret;
        }
        members = ((RecordDefinition)l.pAttr).ptr;
        int size = members.indexOf(new TypeDefinition(a));
        if (size >= 0) {
            ret.totalOff = size * OFFSET_INC + l.memPos.offset;
            ret.jumpLevel = currentNestLevel - l.nestLevel;
            ret.type = members.get(size).type;
        }
        return ret;
    }

    public static void initScope() {
        currentNestLevel = -1;
        VariableDefinitionHashMap.clear();
        TypeDefinitionHashMap.clear();
        FunctionDefinitionHashMap.clear();
        ProcedureDefinitionHashMap.clear();
    }

    public static int enterNewScope(TreeNode t) {
        currentNestLevel += 1;
        totalOffset[currentNestLevel] = updateSymbolTable(t);
        return totalOffset[currentNestLevel];
    }

    public static int leaveScope() {
        int retValue = totalOffset[currentNestLevel];
        currentNestLevel--;

        for (Iterator<Map.Entry<String, LinkedList<VariableDefinition> > >  it = VariableDefinitionHashMap.entrySet().iterator(); it.hasNext(); ) {
            Map.Entry<String, LinkedList<VariableDefinition> > entry = it.next();
            LinkedList<VariableDefinition> VariableDefinitions = entry.getValue();
            while (VariableDefinitions.size() != 0 && VariableDefinitions.getFirst().nestLevel > currentNestLevel) {
                VariableDefinitions.removeFirst();
            }
            if (VariableDefinitions.size() == 0) {
                it.remove();
            }
        }

        for (Iterator<Map.Entry<String, LinkedList<TypeDefinition> > >  it = TypeDefinitionHashMap.entrySet().iterator(); it.hasNext(); ) {
            Map.Entry<String, LinkedList<TypeDefinition> > entry = it.next();
            LinkedList<TypeDefinition> TypeDefinitions = entry.getValue();
            while (TypeDefinitions.size() != 0 && TypeDefinitions.getFirst().nestLevel > currentNestLevel) {
                TypeDefinitions.removeFirst();
            }
            if (TypeDefinitions.size() == 0) {
                it.remove();
            }
        }

        return retValue;
    }

    private static int updateSymbolTable(TreeNode syntaxTree) {
        offset = -4;
        if (syntaxTree != null && syntaxTree.getChildren().size() >= 4) {
            for (int i = 0; i < 4; i++) {
                insertNode(syntaxTree.getChildren().get(i));
            }
        }
        return -offset;
    }

    private static void insertNode(TreeNode t) {
        if (t == null)
            return;
        if (!(t.getNodeType() instanceof DeclarationKind)) {
            return;
        }
        int lineNumber = t.getLineNumber();
        switch ((DeclarationKind)t.getNodeType()) {
            case CONST: {
                while (t != null) {
                    offset -= OFFSET_INC;
                    insertVariable(new VariableDefinition((String)t.getAttribute(), t.getExpType(), true, currentNestLevel, null, offset), lineNumber);
                    t = t.getSibling();
                }
                break;
            }
            case VAR: {
                while (t != null) {
                    TreeNode pname = t.getChildren().get(0);
                    TreeNode ptype = t.getChildren().get(1);
                    while (pname != null) {
                        switch ((TypeKind)ptype.getNodeType()) {
                            case SIMPLE_ID: {
                                TypeDefinition l = lookupType((String) ptype.getAttribute());
                                switch (l.type) {
                                    case ARRAY:
                                    case RECORD: {
                                        offset -= l.size;
                                        break;
                                    }
                                    default: {
                                        offset -= OFFSET_INC;
                                        break;
                                    }
                                }
                                insertVariable(new VariableDefinition((String)pname.getAttribute(), l.type, false, currentNestLevel, l.pAttr, offset), lineNumber);
                                break;
                            }
                            case SIMPLE_ENUM: {
                                LinkedList eptr = new LinkedList();
                                while (ptype != null) {
                                    eptr.add(ptype.getAttribute());
                                    ptype = ptype.getSibling();
                                }
                                offset -= OFFSET_INC;
                                insertVariable(new VariableDefinition((String)pname.getAttribute(), ExpressionType.SIMPLE_ENUM, false, currentNestLevel, eptr, offset), lineNumber);

                                break;
                            }
                            case SIMPLE_LIMIT: {
                                SubBoundDefinition sub = new SubBoundDefinition(ptype.getChildren().get(0).getExpType(), ptype.getChildren().get(0).getAttribute(), ptype.getChildren().get(1).getAttribute());
                                offset -= OFFSET_INC;
                                insertVariable(new VariableDefinition((String)pname.getAttribute(), ExpressionType.SIMPLE_LIMIT, false, currentNestLevel, sub, offset), lineNumber);
                                break;
                            }
                            case SIMPLE_SYS: {
                                offset -= OFFSET_INC;
                                insertVariable(new VariableDefinition((String)pname.getAttribute(), ptype.getExpType(), false, currentNestLevel, null, offset), lineNumber);
                                break;
                            }
                            case ARRAY: {
                                int arraySize = 0;
                                if (ptype.getChildren().get(0).getExpType() == ExpressionType.SIMPLE_LIMIT) { // 目前只能处理数组下标为子界的情况
                                    arraySize = (Integer) ptype.getChildren().get(0).getChildren().get(1).getAttribute() - (Integer) ptype.getChildren().get(0).getChildren().get(0).getAttribute() + 1;
                                    ArrayDefinition pAttr = new ArrayDefinition(ptype.getChildren().get(1).getExpType(), ptype.getChildren().get(0).getChildren().get(0).getExpType(), ptype.getChildren().get(0).getChildren().get(0).getAttribute(), ptype.getChildren().get(0).getChildren().get(1).getAttribute());
                                    offset -= (OFFSET_INC * arraySize);
                                    insertVariable(new VariableDefinition((String) pname.getAttribute(), ptype.getExpType(), false, currentNestLevel, pAttr, offset), lineNumber);
                                }
                                break;
                            }
                            case RECORD: { // 暂不支持嵌套record
                                LinkedList<TypeDefinition> TypeDefinitionList = new LinkedList<>();
                                while (ptype != null) {
                                    TreeNode nameNode = ptype.getChildren().get(0);
                                    TreeNode typeNode = ptype.getChildren().get(1);
                                    while (nameNode != null) {
                                        offset -= OFFSET_INC;
                                        TypeDefinitionList.add(new TypeDefinition((String)nameNode.getAttribute(), typeNode.getExpType(), currentNestLevel, null, OFFSET_INC));
                                        nameNode = nameNode.getSibling();
                                    }
                                }
                                RecordDefinition r = new RecordDefinition(RecordType.ANONYMOUS, TypeDefinitionList);
                                insertVariable(new VariableDefinition((String)pname.getAttribute(), ExpressionType.RECORD, false, currentNestLevel, r, offset), lineNumber);
                                break;
                            }
                            default:
                                break;
                        }
                        pname = pname.getSibling();
                    }
                    t = t.getSibling();
                }
                break;
            }
            case TYPE: {
                while (t != null) {
                    switch ((TypeKind) t.getChildren().get(1).getNodeType()) {
                        case SIMPLE_ID: {
                            String definedTypeName = (String)t.getChildren().get(1).getAttribute();
                            TypeDefinition definedType = lookupType(definedTypeName);
                            if (definedType == null) {
                                System.err.println("No such type: " + definedTypeName + " in line " + lineNumber);
                                System.exit(1);
                            }
                            insertType(new TypeDefinition((String)t.getChildren().get(0).getAttribute(), definedType.type, currentNestLevel, definedType.pAttr, OFFSET_INC), lineNumber);
                            break;
                        }
                        case SIMPLE_ENUM: {
                            TreeNode eList = t.getChildren().get(1).getChildren().get(0);
                            LinkedList eptr = new LinkedList();
                            while (eList != null) {
                                eptr.add(eList.getAttribute());
                                eList = eList.getSibling();
                            }
                            offset -= OFFSET_INC;
                            insertType(new TypeDefinition((String)t.getChildren().get(0).getAttribute(), ExpressionType.SIMPLE_ENUM, currentNestLevel, eptr, OFFSET_INC), lineNumber);
                            // (String) t.getChildren().get(0).getAttribute()是这个枚举类型的名字
                            break;
                        }
                        case SIMPLE_LIMIT: {
                            SubBoundDefinition sub = new SubBoundDefinition(t.getChildren().get(1).getChildren().get(0).getExpType(), t.getChildren().get(1).getChildren().get(0).getAttribute(), t.getChildren().get(1).getChildren().get(1).getAttribute());
                            insertType(new TypeDefinition((String)t.getChildren().get(0).getAttribute(), ExpressionType.SIMPLE_LIMIT, currentNestLevel, sub, OFFSET_INC), lineNumber);
                            // (String)t.getChildren().get(0).getAttribute()是这个类型的名字
                            break;
                        }
                        case SIMPLE_SYS: {
                            insertType(new TypeDefinition((String)t.getChildren().get(0).getAttribute(), t.getChildren().get(1).getExpType(), currentNestLevel, null, OFFSET_INC), lineNumber);
                            break;
                        }
                        case ARRAY: {
                            TreeNode atype = t.getChildren().get(1);
                            if (atype.getChildren().get(0).getExpType() == ExpressionType.SIMPLE_LIMIT) { // 目前只能处理数组下标为子界的情况
                                ArrayDefinition pAttr = new ArrayDefinition(atype.getChildren().get(1).getExpType(), atype.getChildren().get(0).getChildren().get(0).getExpType(), atype.getChildren().get(0).getChildren().get(0).getAttribute(), atype.getChildren().get(0).getChildren().get(1).getAttribute());
                                int size = ((Integer)(atype.getChildren().get(0).getChildren().get(1).getAttribute()) - (Integer) atype.getChildren().get(0).getChildren().get(0).getAttribute() + 1) * OFFSET_INC;
                                insertType(new TypeDefinition((String)t.getChildren().get(0).getAttribute(), t.getChildren().get(1).getExpType(), currentNestLevel, pAttr, size), lineNumber);
                            }
                            break;
                        }
                        case RECORD: { // 暂不支持嵌套record
                            TreeNode pname = t.getChildren().get(0);
                            TreeNode ptype = t.getChildren().get(1);
                            LinkedList<TypeDefinition> TypeDefinitionList = new LinkedList<>();
                            int size = 0;
                            while (ptype != null) {
                                TreeNode nameNode = ptype.getChildren().get(0);
                                TreeNode typeNode = ptype.getChildren().get(1);
                                while (nameNode != null) {
                                    size++;
                                    TypeDefinitionList.add(new TypeDefinition((String)nameNode.getAttribute(), typeNode.getExpType(), currentNestLevel, null, OFFSET_INC));
                                    nameNode = nameNode.getSibling();
                                }
                                ptype = ptype.getSibling();
                            }
                            RecordDefinition r = new RecordDefinition(RecordType.DEFINED, TypeDefinitionList);
                            insertType(new TypeDefinition((String)pname.getAttribute(), ExpressionType.RECORD, currentNestLevel, r, size * OFFSET_INC), lineNumber);
                            break;
                        }
                        default:
                            break;
                    }
                    t = t.getSibling();
                }
                break;
            }
            // function和procedure在代码生成进入到相应节点的时候再插入，不然如果同级的不同函数之间有相同的变量的话，这种冲突是解决不了的
            default:
                break;
        }
    }

}
