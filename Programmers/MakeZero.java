import java.util.*;

class Solution {
    private Node[] tree;
    private boolean[][] board;
    private int answer;
    public long solution(int[] a, int[][] edges) {
        this.tree = new Node[a.length];
        for (int i = 0; i < a.length; i++)
            this.tree[i] = new Node(a[i]);
        this.board = new boolean[a.length][a.length];
        this.answer = 0;
        
        
        for (int[] p : edges) {
            this.board[p[0]][p[1]] = true;
            this.board[p[1]][p[0]] = true;
        }
        
        connectDFS(0);
                
        dfs(this.tree[0]);
        
        return (this.tree[0].getCount() == 0) ? this.answer : -1;
    }
    
    private void connectDFS(int row) {
        for (int i = 0; i < this.board.length; i++) {
            if (this.board[row][i]) {
                connect(this.tree[row], this.tree[i]);
                this.board[row][i] = false;
                this.board[i][row] = false;
                connectDFS(i);
            }
        }
    }
    
    private void connect(Node p, Node c) {
        p.setChildren(c);
        c.setParent(p);
    }
    
    private void dfs(Node nowNode) {
        // base case
        if (nowNode.getchildrenNum() > 0) {
            for (int i = 0; i < nowNode.getchildrenNum(); i++)
                dfs(nowNode.getChildren(i));
        }
        
        if (nowNode.getParent() == null) return;
                        
        this.answer += Math.abs(nowNode.getCount());
        
        nowNode.getParent().changeCount(nowNode.getCount());
        
        nowNode.changeCount(nowNode.getCount() * -1);
    }
}

class Node {
    private int count;
    private Node parentNode;
    private int childrenNum;
    private List<Node> childrenNode;
    
    public Node(int count) {
        this.count = count;
        this.childrenNode = new LinkedList<>();
        this.childrenNum = 0;
    }

    
    public int getCount() {
        return this.count;
    }
    
    public void setCount(int cnt) {
        this.count = cnt;
    }
    
    public void changeCount(int num) {
        this.count += num;
    }
    
    public Node getParent() {
        return this.parentNode;
    }
    
    public void setParent(Node p) {
        this.parentNode = p;
    }
    
    public int getchildrenNum() {
        return this.childrenNum;
    }
    
    public Node getChildren(int idx) {
        return this.childrenNode.get(idx);
    }
    
    public void setChildren(Node c) {
        this.childrenNum++;
        this.childrenNode.add(c);
    }
}
