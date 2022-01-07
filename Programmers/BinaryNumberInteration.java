class Solution {
    public int[] solution(String s) {        
        int count = 0;
        int count_zero = 0;
        
        while(!s.equals("1")) {
            int count_one = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s.charAt(i) == '1') count_one++;
                else count_zero++;
            }
            
            s = Integer.toBinaryString(count_one);
            count++;
        }
        
        int[] answer = { count, count_zero };
        return answer;
    }
}
