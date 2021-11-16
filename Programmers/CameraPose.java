import java.util.*;

class Solution {
    char[] member = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};
    Map<Character, Integer> friends;
    String[] condition;
    int answer = 0;
    public int solution(int n, String[] data) {
        duplicateCondition(data);
        addFriends();
        DFS(1);
        return this.answer;
    }
    
    
    private void DFS(int depth) {
        if (depth > this.friends.size()) {
            checkCondition();
            return;
        }
        
        for (int i = 0; i < this.friends.size(); i++) {
            char now = this.member[i];
            if (this.friends.get(now) != -1) continue;
            
            this.friends.put(now, depth);
            DFS(depth + 1);
            this.friends.put(now, -1);
        }
    }
    
    private void checkCondition() {
        for (int i = 0; i < this.condition.length; i++) {
            // 두개의 알파벳을 분리한다.
            char f_1 = this.condition[i].charAt(0);
            char f_2 = this.condition[i].charAt(2);
            char sign = this.condition[i].charAt(3);
            int distance = this.condition[i].charAt(4) - '0' + 1;
            // 범위를 지정한다
            if (sign == '=') {
                if (Math.abs(this.friends.get(f_1) - this.friends.get(f_2)) != distance) return;
            } else if(sign == '<') {
                if (Math.abs(this.friends.get(f_1) - this.friends.get(f_2)) >= distance) return;
            } else if(sign == '>') {
                if (Math.abs(this.friends.get(f_1) - this.friends.get(f_2)) <= distance) return;
            }
        }
                         
        this.answer++;
    }
    
    private void duplicateCondition(String[] c) {
        this.condition = new String[c.length];
        
        for (int i = 0; i < c.length; i++)
            this.condition[i] = c[i];
    }
    private void addFriends() {
        this.friends = new HashMap<Character, Integer>();
        
        for (int i = 0; i < this.member.length; i++) 
            this.friends.put(this.member[i], -1);
    }
}
