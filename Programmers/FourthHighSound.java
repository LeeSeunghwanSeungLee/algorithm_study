class Solution {
    public int solution(int n) {
        int answer = 0;
        answer = getCases(n, 0);
        return answer;
    }
    
    private int getCases(int n, int plus) {
        int res = 0;
        
        if (n == 3 && plus == 2) return 1;
        else if (n == 2) return 0;
        else if (n == 1) return 0;
        
        if (Math.pow(3, plus / 2) > n) return 0;
        
        if (n % 3 == 0)
            if (plus >= 2) res += getCases(n / 3, plus - 2);
        res += getCases(n - 1, plus + 1);
        return res;
    }
}
