class Solution {
    private int CONST = 1000000007;
    
    public int solution(int n) {
        if (n == 1) return 1;
        else if (n == 2) return 2;
        int prev = 1;
        int next = 2;
        for (int i = 3; i <= n; i++) {
            int tmp = (prev + next) % this.CONST;
            prev = next;
            next = tmp;
        }
        
        return next;
    }
}
