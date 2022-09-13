import java.util.*;

class Solution {
    boolean solution(String s) {
        // given
        Integer flag = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ')') {
                if (flag <= 0) {
                    return false;
                }
                flag--;
            } else {
                flag++;
            }
        }
        return flag.equals(0);
    }
}
