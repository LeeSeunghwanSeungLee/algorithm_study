import java.util.*;

class Solution {
    private PriorityQueue<Node> pqMin;
    private PriorityQueue<Node> pqMax;
    
    public int[] solution(String[] operations) {
        // init
        this.pqMin = new PriorityQueue<>((a, b) -> {
            return a.getNumber() - b.getNumber();
        });
        this.pqMax = new PriorityQueue<>((a, b) -> {
            return b.getNumber() - a.getNumber();
        });
        
        
        for (int i = 0; i < operations.length; i++) {
            String[] order = operations[i].split(" ");
            int num = Integer.parseInt(order[1]);
            if (order[0].equals("I")) { // insert
                Node newNode = new Node(num);
                this.pqMin.add(newNode);
                this.pqMax.add(newNode);
            } else if (num < 0){ // pop min
                while(true) {
                    if (this.pqMin.isEmpty()) break;
                    Node peek = this.pqMin.poll();
                    if (!peek.isDelete()) {
                        peek.setDelete();
                        break;
                    }
                }
            } else { // pop max
                while(true) {
                    if (this.pqMax.isEmpty()) break;
                    Node peek = this.pqMax.poll();
                    if (!peek.isDelete()) {
                        peek.setDelete();
                        break;
                    }
                }
            }
        }
        int[] answer = new int[2];
        answer[0] = getMax();
        answer[1] = getMin();
        return answer;
    }
    
    private int getMin() {
        int res = 0;
        while(true) {
            if (this.pqMin.isEmpty()) break;
            Node peek = this.pqMin.poll();
            if (!peek.isDelete()) {
                res = peek.getNumber();
                break;
            }
        }
        return res;
    }
    
    private int getMax() {
        int res = 0;
        
        while(true) {
            if (this.pqMax.isEmpty()) break;
            Node peek = this.pqMax.poll();
            if (!peek.isDelete()) {
                res = peek.getNumber();
                break;
            }
        }
        return res;
    }
}

class Node {
    private int num;
    private boolean delete;
    
    public Node(int n) {
        this.num = n;
        this.delete = false;
    }
    
    public void setDelete() {
        this.delete = true;
    }
    
    public boolean isDelete() {
        return this.delete;
    }
    
    public int getNumber() {
        return this.num;
    }
}
