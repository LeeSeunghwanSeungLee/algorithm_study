import java.util.*;

class Solution {
    Map<String, Node> members;
    List<String> memberNames;
    
    public int[] solution(String[] enroll, String[] referral, String[] seller, int[] amount) {
        this.members = new HashMap<>();
        this.memberNames = new ArrayList<>();
        // center 멤버 이름과 멤버 맵에 추가한다
        this.memberNames.add("center");
        this.members.put("center", new Node("center", "-", 0));
        // 멤버들을 멤버 이름과 멤버 맵에 순회하면서 추가한다
        for (int i = 0; i < enroll.length; i++) {
            String name = enroll[i];
            String parentsName = referral[i].equals("-") ? "center" : referral[i];            
            this.memberNames.add(name);
            this.members.put(name, new Node(name, parentsName, 0));
        }
        // seller와 amount를 순회하면서 계산한다
        for (int i = 0; i < seller.length; i++) {
            String target = seller[i];
            int points = amount[i] * 100;
            calculatePoints(target, points);
        }
        int[] answer = new int[this.memberNames.size() - 1];
        for (int i = 1; i < this.memberNames.size(); i++) {
            String target = this.memberNames.get(i);
            answer[i - 1] = this.members.get(target).getPoints();
        }
        return answer;
    }
    // DFS
    public void calculatePoints(String target, int p) {
        int nextPoint = (int)(p * 0.1);
        int myPoint = p - nextPoint;
                
        Node targetNode = this.members.get(target);
        if (targetNode.getParentsName() == "-") {
            targetNode.addPoints(p);
            return;
        }
        targetNode.addPoints(myPoint);
        if (nextPoint <= 0) return;
        
        calculatePoints(targetNode.getParentsName(), nextPoint);
    }
}

class Node {
    private String name;
    private String parentsName;
    private int points;
    
    public Node(String name, String parents, int points) {
        this.name = name;
        this.parentsName = parents;
        this.points = points;
    }
    public String getParentsName() {
        return this.parentsName;
    }
    public int getPoints() {
        return this.points;
    }
    
    public void addPoints(int p) {
        this.points += p;
    }
}
