import java.util.*;

class Solution {
    private Integer min;
    private Integer max;
    
    public String solution(String s) {
        // 0. init
        this.min = null;
        this.max = null;
        // 1. split
        String[] numList = s.split(" ");
        // 2. stream을 이용한 min max 찾기
        for (String num : numList) {
            int val = Integer.valueOf(num);
            if (this.min == null && this.max == null) {
                this.min = this.max = val;
            } else if (this.min > val) {
                this.min = val;
            } else if (this.max < val) {
                this.max = val;
            }
        }
        
        return this.min + " " + this.max;
    }
}
