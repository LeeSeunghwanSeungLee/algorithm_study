class Solution {
    public String solution(String p) {
        return recursionCheck(p);
    }
    
    private String recursionCheck(String targetString) {
        if (targetString.equals("")) return "";
        
        int idx = getBalancedIndex(targetString);
        String u;
        String v;
        if (idx == targetString.length() - 1) {
            u = targetString;
            v = "";
        } else {
            u = targetString.substring(0, idx + 1);
            v = targetString.substring(idx + 1);
        }
        
        // 만일 u가 올바른 분자열이라면 return u + resursionCheck(v);
        if (isRight(u))
            return u + recursionCheck(v);
        
        // return "(" + recursionCheck(v) + ")" + 첫번째마지막제거하고,뒤집기(u);
        return "(" + recursionCheck(v) + ")" + reverseDirectionAllCharacter(trimSide(u));
    }
    
    private int getBalancedIndex(String targetString) {
        if (targetString.equals("")) return 0;
        
        int rightCurve = 0;
        int leftCurve = 0;
        
        for (int i = 0; i < targetString.length(); i++) {
            if (targetString.charAt(i) == '(')
                leftCurve++;
            else 
                rightCurve++;
            
            if (leftCurve == rightCurve) return i;
        }
        return 0;
    }
    
    private boolean isRight(String targetString) {
        if (targetString.length() == 0) return true;
        
        int res = 0;
        
        for (int i = 0; i < targetString.length(); i++) {
            if (targetString.charAt(i) == '(')
                res++;
            else
                res--;
            
            if (res < 0)
                return false;
        }
        
        return true;
    }
    
    private String trimSide(String targetString) {
        if (targetString.equals("")) return "";
        return targetString.substring(1, targetString.length() - 1);
    }
    
    private String reverseDirectionAllCharacter(String targetString) {
        if (targetString.equals("")) return "";
        String res = "";
        
        for (int i = 0; i < targetString.length(); i++) {
            if (targetString.charAt(i) == '(')
                res += ')';
            else
                res += '(';
        }
        return res;
    }
}
