class Solution {
    public static int MOD = 1234567;
    
    public long solution(int n) {
        long pre_answer = 1;
        long answer = 2;
        for (int i = 3; i <= n; i++) {
            long tmp = answer;
            answer = getModular(answer + pre_answer);
            pre_answer = tmp;
        }
        return n == 1 ? 1 : answer;
    }
    
    private long getModular(long n) {
        return n % MOD;
    }
}
