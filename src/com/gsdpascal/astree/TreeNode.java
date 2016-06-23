package com.gsdpascal.astree;
/**
 * Created by Xiecihui on 16/6/22.
 */
import java.util.ArrayList;
import java.util.List;

public class TreeNode {
    /*语法树的多个儿子节点，避免层数过深*/
    private List<TreeNode> childNode = new ArrayList<>();
    /*语法树兄弟节点*/
    private TreeNode siblingNode = null;
    /*语法树节点的类型*/
    private Object nodeType = null;
    /*语法树节点的属性*/
    private Object attribute = null;
    /*语法树节点在的表达式类型Type*/
    private ExpressionType ExpressionType = null;
    /*语法树节点在运行时的类型*/
    private ExpressionType runtimeType = null;
    /*语法树节点行号*/
    private int lineNumber = 0;
    /*语法树节点列号*/
    private int columnNumber = 0;

    /*默认构造函数*/
    public TreeNode() {

    }
    /*用于终结符的构造函数*/
    public TreeNode(Object nodeType, int lineNumber) {
        this.nodeType = nodeType;
        this.lineNumber = lineNumber;
        if (nodeType instanceof ExpressionKind) {
            this.ExpressionType = ExpressionType.VOID;
        }
    }
    /*用于非终结符的构造函数*/
    public TreeNode(TreeNode first, TreeNode second, OperationKind op, int lineNumber) {
        this.nodeType = ExpressionKind.OP;
        this.attribute = op;
        this.lineNumber = lineNumber;
        this.addChild(first);
        this.addChild(second);
    }

    public TreeNode(OperationKind op, TreeNode child, int lineNumber) {
        this.nodeType = ExpressionKind.FUNC_SYS;
        this.addChild(child);
        this.attribute = op;
        this.lineNumber = lineNumber;
    }

    public List<TreeNode> getChildren() {
        return childNode;
    }

    public void addChild(TreeNode node) {
        childNode.add(node);
    }

    public TreeNode getSibling() {
        return siblingNode;
    }

    public void setSibling(TreeNode siblingNode) {
        this.siblingNode = siblingNode;
    }

    public int getLineNumber() {
        return lineNumber;
    }

    public void setLineNumber(int lineNumber) {
        this.lineNumber = lineNumber;
    }

    public Object getNodeType() {
        return nodeType;
    }

    public void setNodeType(Object nodeType) {
        this.nodeType = nodeType;
    }

    public Object getAttribute() {
        return attribute;
    }

    public void setAttribute(Object attribute) {
        this.attribute = attribute;
    }

    public ExpressionType getExpType() {
        return ExpressionType;
    }

    public void setExpType(ExpressionType ExpressionType) {
        this.ExpressionType = ExpressionType;
    }

    public ExpressionType getRunTimeType() {
        return runtimeType;
    }

    public void setRunTimeType(ExpressionType runtimeType) {
        this.runtimeType = runtimeType;
    }

    public void printTree(TreeNode tree){
        int i;
        while(tree!=null){
           System.out.println("line number "+" nodeType       "+
        "  attribute "+" ExpressionType "+" runtimeType ");
           System.out.print("     "+tree.getLineNumber());
           System.out.print("       "+tree.getNodeType());
           System.out.print("  "+tree.getAttribute());
           System.out.print("       "+tree.getExpType());
           System.out.print("     "+tree.getRunTimeType()+"\n");

            for(i=0;i<tree.getChildren().size();i++){
              if(tree.getChildren().get(i)==null){
            	  System.out.println("childNode:"+i+" is null ");
              }else{
            	  System.out.println("childNode:"+i);
                  printTree(tree.getChildren().get(i));
              }
            }
            tree=tree.getSibling();
        }
    }
}
