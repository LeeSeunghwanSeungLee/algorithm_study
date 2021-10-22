import java.util.*;

class Solution {
    int position;
    
    public String solution(String p){
        if(p.isEmpty()) return p;
        
        boolean correction = isCorrect(p);
        
        String u = p.substring(0, this.position);
        String v = p.substring(this.position, p.length());
        
        if(correction){
            return u + solution(v);
        }
        
        String answer = "(" + solution(v) + ")";
        
        for(int i = 1; i < u.length() - 1; i++){
            if(u.charAt(i) == '('){
                answer +=")";
            } else {
                answer += "(";
            }
        }
        
        return answer;
    }
    
    private boolean isCorrect(String str){
        boolean ret = true;
        int left = 0, right = 0;
        
        Stack<Character> mystack = new Stack<>();
        
        for(int i = 0; i < str.length(); i++){
            if(str.charAt(i) == '('){
                left++;
                mystack.push('(');
            } else {
                right++;
                if(mystack.isEmpty()){
                    ret = false;
                } else {
                    mystack.pop();
                }
            }
            
            if(left == right) {
                this.position = i + 1;
                return ret;
            }
        }
        return true;
    }
}
