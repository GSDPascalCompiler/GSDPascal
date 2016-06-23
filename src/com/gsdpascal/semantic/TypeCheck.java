package com.gsdpascal.semantic;

import java.util.LinkedList;

import com.gsdpascal.astree.DeclarationKind;
import com.gsdpascal.astree.ExpressionKind;
import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.StatementKind;
import com.gsdpascal.astree.TreeNode;


public class TypeCheck {
	/*counter for variable memory Posation*/
	static int base = 0;
	static int offset = 0;

	/*trace*/
	static int TraceAnalyze = 1;
	
	/*error*/
	static int Error = 0;
	
	/*typecheck*/
	static int inTypeCheck = 0;
	protected static TypeCheck instance;
	public TypeCheck(){
		
	}
    public static TypeCheck getExpTypeCheck() {  // Singleton pattern
        if (instance == null) {
            instance = new TypeCheck();
        }
        return instance;
    }

	public void typeCheck(TreeNode syntaxTree){
		inTypeCheck = 1;
		SymbolTable.initScope();
		checkNode(syntaxTree);
		SymbolTable.leaveScope();
		inTypeCheck = 0;
	}

	private boolean compoundTypeEqual(TreeNode t1,TreeNode t2) {
		VariableDefinition l1,l2;
		l1 = SymbolTable.lookupVar((String)t1.getAttribute());
		l2 = SymbolTable.lookupVar((String)t1.getAttribute());
		if(l1 == null){
			System.out.println("Line "+t1.getLineNumber()+", Error: "+(String)(t1.getChildren().get(0)).getAttribute()+" is not declare.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}
		if(l2 == null){
			System.out.println("Line "+t2.getLineNumber()+", Error: "+(String)(t2.getChildren().get(0)).getAttribute()+" is not declare.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}
		return (l1.pAttr == l2.pAttr);
	}
	private boolean nodeTypeEqual(TreeNode t1,TreeNode t2) {
		if(t1.getRunTimeType() == t2.getRunTimeType()){
			if(t1.getRunTimeType() == ExpressionType.VOID ||
			   t1.getRunTimeType() == ExpressionType.INT || 
			   t1.getRunTimeType() == ExpressionType.REAL || 
			   t1.getRunTimeType() == ExpressionType.CHAR || 
			   t1.getRunTimeType() == ExpressionType.STRING ||
			   t1.getRunTimeType()== ExpressionType.BOOL)
			   return true;
			else	
				return compoundTypeEqual(t1,t2);
		}
		else
			return false;
	}

	private void checkNodeExpression(TreeNode pnode) {
		if(pnode.getNodeType()==ExpressionKind.ID){
			checkExpId(pnode);
		}else if(pnode.getNodeType()==ExpressionKind.OP){
			checkExpOp(pnode);
		}else if(pnode.getNodeType()==ExpressionKind.CONST){
			checkExpConst(pnode);
		}else if(pnode.getNodeType()==ExpressionKind.CASE){
			checkExpCase(pnode);
		}else if(pnode.getNodeType()==ExpressionKind.FUNC_ID){
			checkExpFunc(pnode);
		}
	
	}
	private void checkExpId(TreeNode pnode) {
		VariableDefinition ssvar=SymbolTable.lookupVar((String)pnode.getAttribute());
		ExpressionType checkType;
		LookupReturn ret;

		if (ssvar==null){
	 		System.out.println("Line "+pnode.getLineNumber()+", Error: The variable "+(String)pnode.getAttribute()+" is not declared.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
	 	}
	 	checkType = ssvar.type;
	 	switch(checkType){
	 		case ARRAY:
	 			//�����index�Ƿ����
	 			if(pnode.getChildren().get(0)==null){
	 				//ֻ������
	 				pnode.setRunTimeType(checkType);
	 			}
	 			else{
	 				//������Ԫ��
	 				pnode.setRunTimeType(((ArrayDefinition)(ssvar.pAttr)).arrayType);
	 			}
	 			break;
	 		case RECORD:
	 			if(pnode.getChildren().get(0)==null){
	 				//ֻ��record
	 				pnode.setRunTimeType(checkType); 
	 			}
	 			else{
	 				ret = SymbolTable.lookupRecord((String)pnode.getAttribute(),(pnode.getChildren().get(0)).getAttribute().toString());
	 				if(ret.type == ExpressionType.VOID){
	 					System.out.println("Line "+pnode.getLineNumber()+", Error: The variable "+(String)pnode.getAttribute()+"."+(pnode.getChildren().get(0)).getAttribute().toString()+" is not declare.\n");
	 					//fflush(stdout);
	 					typeError();
	 					// error = True;
	 				}
	 				pnode.setRunTimeType(ret.type);
	 			}
	 			break;
	 		case BOOL:
	 			pnode.setRunTimeType(ExpressionType.INT);
	 		default:
	 			pnode.setRunTimeType(checkType);
	 			break;
	 	}
	}
	private void checkExpOp(TreeNode pnode) {
		if ((pnode.getChildren().get(0))!=null && (pnode.getChildren().get(1))!=null){
			//����﷨���󣬲�ΪRunningType��ֵ
			checkNode((pnode.getChildren().get(0)));
			checkNode((pnode.getChildren().get(1)));


			if ((pnode.getChildren().get(0)).getRunTimeType() != ((pnode.getChildren().get(1))).getRunTimeType()){
	 			System.out.println("Line "+pnode.getLineNumber()+", Error: Different type can not be calculated.\n");
	 			//fflush(stdout);	
	 			typeError();
	 			// error = True;			
	 		}
	 		
			if ((pnode.getChildren().get(0)).getRunTimeType()==ExpressionType.REAL && (pnode.getChildren().get(1)).getRunTimeType()==ExpressionType.REAL)
				pnode.setRunTimeType(ExpressionType.REAL);
			else if((pnode.getChildren().get(0)).getRunTimeType()==ExpressionType.INT &&(pnode.getChildren().get(1)).getRunTimeType()==ExpressionType.INT)
				pnode.setRunTimeType(ExpressionType.INT); 
			else if((pnode.getChildren().get(0)).getRunTimeType()==ExpressionType.CHAR && (pnode.getChildren().get(1)).getRunTimeType()==ExpressionType.CHAR){
				System.out.println("Line "+pnode.getLineNumber()+", Error: Char can not be calculated.\n");
	 			//fflush(stdout);
	 			typeError();
	 			// error = True;
			}
			else{
				System.out.println("Line "+pnode.getLineNumber()+", Error: compound type can not be calculated.\n");
	 			//fflush(stdout);
	 			typeError();
	 			// error = True;
			}

		}
		else {
			checkNode(pnode.getChildren().get(0));
			pnode.setRunTimeType((pnode.getChildren().get(0)).getRunTimeType());
		}
	}

	private static void checkExpConst(TreeNode pnode) {
		if(pnode.getExpType() == ExpressionType.BOOL)
			pnode.setRunTimeType(ExpressionType.INT);
		else
			pnode.setRunTimeType(pnode.getExpType());
	}
	
	private void checkExpCase(TreeNode pnode) {
		checkNode(pnode.getChildren().get(0));	
		checkNode(pnode.getChildren().get(1));

		pnode.setRunTimeType(pnode.getChildren().get(0).getRunTimeType());
	}
	private void checkExpFunc(TreeNode pnode) {
		FunctionDefinition judge_var=SymbolTable.lookupFunc((String)pnode.getAttribute());
	 	if(judge_var == null){
	 		System.out.println("Line "+pnode.getRunTimeType()+", Error: Function "+(String)pnode.getAttribute()+" dose not declare.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
	 	}
		TreeNode tmpChild = pnode.getChildren().get(0);
		LinkedList<SimpleType> tmpPara = judge_var.paraList;

		if(tmpChild != null)		//���ܲ����ڲ���
			checkNode(tmpChild);

		int i=0;

		while(tmpChild!=null && i < tmpPara.size()){
			//ֻ�Ǽ򵥵��ж��������Ƿ���ͬ
			if(tmpChild.getRunTimeType() != tmpPara.get(i).type){
				System.out.println("Line "+pnode.getLineNumber()+", Error: parameter type does not match.\n");
	 			//fflush(stdout);
	 			typeError();
	 			// error = True;
			}
			tmpChild = tmpChild.getSibling();
			i++;
		}
		if(tmpChild != null || i < tmpPara.size()){
			System.out.println("Line "+pnode.getLineNumber()+", Error: number of parameters does not match.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}

		//���践��ֵ��ȷ
		pnode.setRunTimeType(judge_var.retType);

		// ��ʱ�޷��ȽϷ���ֵ
		// checkNode(pnode.getChildren().get(1));
		// if(pnode.getChildren().get(1)->RunningType != judge_var->retType){
		// 	printf("Line %d, Error: return data type does not match.\n",pnode.getLineNumber());
	 // 		fflush(stdout);
	 // 		error = True;
		// }

	}

	private void checkStmtAssign(TreeNode pnode) {
		//����0��һ�����ʽ�������ȼ��ñ��ʽ�Ƿ����﷨����
		//Ȼ���ñ��ʽ������
		checkNode(pnode.getChildren().get(1));
		//����1��һ������������ͨ������Ѱ�ұ������������ֻ����һ���ڵ�
		VariableDefinition ssvar=SymbolTable.lookupVar((pnode.getChildren().get(0)).getAttribute().toString());
		if(ssvar == null){
			System.out.println("Line "+pnode.getLineNumber()+", Error: The variable "+(pnode.getChildren().get(0)).getAttribute().toString()+" is not declare.\n");
	 	//	fflush(stdout);
	 		typeError();
		}
		//���ȣ�����ڵ㲻�ܹ�Ϊ����
		if (ssvar.isConst){	
			System.out.println("Line "+pnode.getLineNumber()+", Error: The const variable "+(pnode.getChildren().get(0)).getAttribute().toString()+" can not be assigned.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}
		//�����һ��ExpNode,�ṹֻ�����������id,id[]��id.id
		//Ȼ�����Ǽ�����ExpNode�Ƿ����﷨���󣬲��һ�ȡ���ExpNode������
		checkNode(pnode.getChildren().get(0));

		//���ֵ����������ߵ����Ͳ���ͬ���򱨴�
		if(!nodeTypeEqual(pnode.getChildren().get(0),pnode.getChildren().get(1))){
			System.out.println("Line "+pnode.getLineNumber()+", Error: The type of "+pnode.getChildren().get(0).getAttribute().toString()+" is different from the right hand.");
		//	fflush(stdout);
			typeError();
	 		// error = True;
		}
	}
	private void checkStmtIf(TreeNode pnode) {
		ExpressionType checkType;
		//�﷨�����ᱣ֤if����������

		//panduan
		checkNode(pnode.getChildren().get(0));
		checkType = pnode.getChildren().get(0).getRunTimeType();
		if(checkType != ExpressionType.INT &&
		   checkType != ExpressionType.REAL){
			System.out.println("Line "+pnode.getLineNumber()+", Error: If condition is not illegal.\n");
	 	//	fflush(stdout);
	 		typeError();
	 		// error = True;
		}

		//if-part
		checkNode(pnode.getChildren().get(1));

		if (pnode.getChildren().get(2)!=null)
			checkNode(pnode.getChildren().get(2));
	}
	private void checkStmtFor(TreeNode pnode) {

		//��ʼֵ
		//�﷨������֤for�����Ķ�
		checkNode(pnode.getChildren().get(0));
		checkNode(pnode.getChildren().get(1));
		checkNode(pnode.getChildren().get(2));
		checkNode(pnode.getChildren().get(3));

		if(pnode.getChildren().get(0).getRunTimeType()!= ExpressionType.INT||
		   pnode.getChildren().get(1).getRunTimeType()!= ExpressionType.INT ||
		   pnode.getChildren().get(2).getRunTimeType()!= ExpressionType.INT){
			System.out.println("Line "+pnode.getLineNumber()+", Error: Index of for statement must be int.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}
	}
	private void checkStmtWhile(TreeNode pnode) {
		ExpressionType checkType;

		//�﷨������֤while������������
		checkNode(pnode.getChildren().get(0));
		checkNode(pnode.getChildren().get(1));

		checkType = pnode.getChildren().get(0).getRunTimeType();
		if(checkType != ExpressionType.INT &&
		   checkType != ExpressionType.REAL){
			System.out.println("Line "+pnode.getLineNumber()+" Error: While condition is not illegal.\n");
	 		//fflush(stdout);
	 		typeError();
	 		// error = True;
		}
	}
	private void checkStmtRepeat(TreeNode pnode) {
		ExpressionType checkType;

		checkNode(pnode.getChildren().get(0));
		checkNode(pnode.getChildren().get(1));	

		checkType = pnode.getChildren().get(1).getRunTimeType();
		if(checkType != ExpressionType.INT &&
		   checkType != ExpressionType.REAL){
			System.out.println("Line "+pnode.getLineNumber()+" Error: Util condition is not illegal.\n");
	 		typeError();
	 		// error = True;
		}
	}
	private void checkStmtCase(TreeNode pnode) {
		ExpressionType checkType;
		TreeNode tmp;

		//�﷨������֤2������
		checkNode(pnode.getChildren().get(0));
		checkNode(pnode.getChildren().get(1));

		checkType = pnode.getChildren().get(0).getRunTimeType();
		tmp = pnode.getChildren().get(1);
		while(tmp!=null){
			if(checkType != tmp.getRunTimeType()){
				System.out.println("Line:"+ pnode.getLineNumber()+", Error: data type dose not match case type.\n");
	 			typeError();
	 			// error = True;
			}
			tmp = tmp.getSibling();
		}
	}
	private void checkStmtGoto(TreeNode pnode) {
		int i=0;
	}
	private void checkStmtLabel(TreeNode pnode) {
		checkNode(pnode.getChildren().get(0));
	}
	private void checkStmtProc(TreeNode pnode) {
		if((pnode.getChildren().get(0)) != null)
			checkNode(pnode.getChildren().get(0));
	}

	private void checkNode(TreeNode pnode) {

		if(pnode.getNodeType()==StatementKind.ASSIGN){
			checkStmtAssign(pnode);
		}else if(pnode.getNodeType()==StatementKind.IF){
			checkStmtIf(pnode);
		}else if(pnode.getNodeType()==StatementKind.FOR){
			checkStmtFor(pnode);
		}else if(pnode.getNodeType()==StatementKind.WHILE){
			checkStmtWhile(pnode);
		}else if(pnode.getNodeType()==StatementKind.REPEAT){
			checkStmtRepeat(pnode);
		}else if(pnode.getNodeType()==StatementKind.CASE){
			checkStmtCase(pnode);
		}else if(pnode.getNodeType()==StatementKind.GOTO){
			checkStmtGoto(pnode);
		}else if(pnode.getNodeType()==StatementKind.LABEL){
			checkStmtLabel(pnode);
		}else if(pnode.getNodeType()==StatementKind.PROC_ID){
			checkStmtProc(pnode);
		}
		
		if((pnode.getNodeType()==ExpressionKind.CASE)
		 |(pnode.getNodeType()==ExpressionKind.CONST)
		 |(pnode.getNodeType()==ExpressionKind.FUNC_ID)
		 |(pnode.getNodeType()==ExpressionKind.FUNC_SYS)
		 |(pnode.getNodeType()==ExpressionKind.ID)
		 |(pnode.getNodeType()==ExpressionKind.OP)){
			checkNodeExpression(pnode);
		}
		if(pnode.getNodeType()==DeclarationKind.ROUTINEHEAD){

			SymbolTable.enterNewScope(pnode);
			if (pnode.getChildren().get(3)!=null)
					checkNode(pnode.getChildren().get(3));

		}else if(pnode.getNodeType()==DeclarationKind.FUNCTION){

			(pnode.getChildren().get(1)).setAttribute((pnode.getChildren().get(0)).getAttribute().toString());
			SymbolTable.addProcOrFunc(pnode.getChildren().get(0));
			checkNode(pnode.getChildren().get(1)); //routine_head
			SymbolTable.leaveScope();

		}else if(pnode.getNodeType()==DeclarationKind.PROCEDURE){

			(pnode.getChildren().get(1)).setAttribute((pnode.getChildren().get(0)).getAttribute().toString());
			SymbolTable.addProcOrFunc(pnode.getChildren().get(0));
			checkNode(pnode.getChildren().get(1)); //routine_head
			SymbolTable.leaveScope();
		}
        

		if(pnode.getSibling()!=null){
			checkNode(pnode.getSibling());	
		}
	}
	private void typeError() {
		System.out.println("Exit with error\n");
		System.exit(1);
	}
}
