class Solution {
    public int solution(int n) {
        int total = countNumberOne(Integer.toBinaryString(n));
        
        int answer = n + 1;
        while (!compare(n, answer)) {
            answer++;
        }
        return answer;
    }
    private boolean compare(int a, int b) {
        int s_a = countNumberOne(Integer.toBinaryString(a));
        int s_b = countNumberOne(Integer.toBinaryString(b));
        
        if (s_a == s_b) {
            return true;
        }
        
        return false;
    }
    
    private int countNumberOne(String number) {
        int cnt = 0;
        for (int i = 0; i < number.length(); i++) {
            if (number.charAt(i) == '1')
                cnt++;
        }
        return cnt;
    }
}
