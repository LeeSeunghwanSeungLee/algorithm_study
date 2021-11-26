import java.util.*;

class Solution {
    private int left;
    private int right;
    private int start;
    private int end;
    
    public int[] solution(String[] gems) {
        Set<String> set = new HashSet<>();
        for (String s : gems) 
            set.add(s);
        
        this.left = this.right = 0;    
        Map<String, Integer> map = new HashMap<>();
        int distance = Integer.MAX_VALUE;
        
        while (true) {
            if (map.size() == set.size()) {
                map.put(gems[this.left], map.get(gems[this.left]) - 1);
                
                if (map.get(gems[this.left]) == 0)
                    map.remove(gems[this.left]);
                
                this.left++;
            } else if (this.right >= gems.length) {
                break;
            } else {
                map.put(gems[this.right], map.getOrDefault(gems[this.right], 0) + 1);
                this.right++;
            }
            
            if (map.size() == set.size()) {
                if (this.right - this.left < distance){
                    distance = this.right - this.left;
                    this.start = this.left + 1;
                    this.end = this.right;
                }    
            }
        }
    
        int[] ans = {this.start, this.end};
        return ans;
    }
}
