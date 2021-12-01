import java.util.*;

class Solution {
    private int answer;
    private Stack<Character> st;
    
    public int solution(String s) {
        this.answer = 0;
        this.st = new Stack<>();
        String curve = s;
        
        for (int i = 0; i < s.length(); i++) {
            if (!checkRightCurve(curve)) {
                curve = rotateString(curve, i + 1);
                continue;
            }
            break;
        }
        

        return this.answer;
    }
    
    private boolean checkRightCurve(String s) {
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '}') {
                if (this.st.isEmpty() || this.st.pop() != '{') {
                    this.answer = 0;
                    this.st = new Stack<>();
                    return false;
                } 
                if (this.st.isEmpty()) this.answer++;
            } else if (s.charAt(i) == ')') {
                if (this.st.isEmpty() || this.st.pop() != '(') {
                    this.answer = 0;
                    this.st = new Stack<>();
                    return false;
                }  
                if (this.st.isEmpty()) this.answer++;
            } else if (s.charAt(i) == ']') {
                if (this.st.isEmpty() || this.st.pop() != '[') {
                    this.answer = 0;
                    this.st = new Stack<>();
                    return false;
                } 
                if (this.st.isEmpty()) this.answer++;
            } else {
                this.st.push(s.charAt(i));
            }
        }
        return true;
    }
    
    private String rotateString(String s, int idx) {
        String a = s.substring(0, idx);
        String b = s.substring(idx, s.length());
        return b + a;
    }
}
