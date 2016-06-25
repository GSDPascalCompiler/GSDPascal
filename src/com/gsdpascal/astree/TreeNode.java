package com.gsdpascal.astree;
/**
 * Created by Xiecihui on 16/6/22.
 */
import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

public class TreeNode {
    /*�﷨���Ķ�����ӽڵ㣬�����������*/
    private List<TreeNode> childNode = new ArrayList<>();
    /*�﷨���ֵܽڵ�*/
    private TreeNode siblingNode = null;
    /*�﷨���ڵ������*/
    private Object nodeType = null;
    /*�﷨���ڵ������*/
    private Object attribute = null;
    /*�﷨���ڵ��ڵı��ʽ����Type*/
    private ExpressionType ExpressionType = null;
    /*�﷨���ڵ�������ʱ������*/
    private ExpressionType runtimeType = null;
    /*�﷨���ڵ��к�*/
    private int lineNumber = 0;
    /*�﷨���ڵ��к�*/
    private int columnNumber = 0;
    private BitSet bitSet = new BitSet();

    /*Ĭ�Ϲ��캯��*/
    public TreeNode() {

    }
    /*�����ս���Ĺ��캯��*/
    public TreeNode(Object nodeType, int lineNumber) {
        this.nodeType = nodeType;
        this.lineNumber = lineNumber;
        if (nodeType instanceof ExpressionKind) {
            this.ExpressionType = ExpressionType.VOID;
        }
    }
    /*���ڷ��ս���Ĺ��캯��*/
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

    public void printTree(TreeNode root, int level){
        if(level == 0)
            if(root == null) return;
        for(int i = 0; i < level; ++i){
            if(bitSet.get(i) == false){
                System.out.print("|");
            }
            else{
                System.out.print(" ");
            }
            System.out.print("    ");
        }
        System.out.print("|-");
        //System.out.print(root.getKind());
        System.out.print(" " +  root.getNodeType());
        System.out.print(" " +  root.getExpType());
        System.out.print(" " +  root.getAttribute());
        System.out.println("");
        if(root.getSibling() == null){
            bitSet.set(level);
        }
        else{
            bitSet.clear(level);
        }
        int cnt = 0;
        for(int i=0;i<root.getChildren().size();i++){
            if(root.getChildren().get(i) != null) cnt++;
        }
        int cnt2 = 0;
        for(int i=0;i<root.getChildren().size();i++){
            if(root.getChildren().get(i) != null){
                cnt2++;
                for(int j = 0; j < level + 1; ++j){
                    if(bitSet.get(j) == false){
                        System.out.print("|");
                    }
                    else{
                        System.out.print(" ");
                    }
                    System.out.print("    ");
                }
                if(cnt2 == cnt)
                    bitSet.set(level + 1);
                else
                    bitSet.clear(level + 1);
                System.out.println("|-" + root.getChildren().get(i).getNodeType());
                printTree(root.getChildren().get(i), level + 2);
            }
        }
        TreeNode t = root.getSibling();
        if(t != null){
            if(t.getSibling() == null){
                bitSet.set(level);
            }
            else{
                bitSet.clear(level);
            }
            printTree(t, level);
        }

    }
}
