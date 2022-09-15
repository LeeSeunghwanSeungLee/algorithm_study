class Solution {
    public int solution(int n) {
        int pre_answer = 0;
        int answer = 1;
        for (int i = 2; i <= n; i++) {
            int tmp = answer;
            answer = modular(answer + pre_answer);
            pre_answer = tmp;
        }
        return answer;
    }
    
    private int modular(int num) {
        return num % 1234567;
    }
}
