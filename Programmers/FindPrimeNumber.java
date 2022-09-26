import java.util.*;

class Solution {
    public int solution(String numbers) {
        int answer = 0;
        Set<Integer> set = getPossibleNumber(numbers);
        for (Integer target : set) {
            if (isPrimeNumber(target)) {
                 answer++;
            }
        }
        return answer;
    }
    
    private Set<Integer> getPossibleNumber(String numbers) {
        Set<Integer> s = new HashSet<>();
        boolean[] check = new boolean[numbers.length()];
        StringBuffer sb = new StringBuffer();
        bfs(0, sb, numbers, check, s);
        return s;
    }
    
    private void bfs(int depth, StringBuffer sb, String numbers, boolean[] check, Set<Integer> set) {
        if (depth >= numbers.length()) {
            set.add(Integer.parseInt(sb.toString()));
            return;
        }
        
        if (depth != 0) {
            set.add(Integer.parseInt(sb.toString()));
        }
        
        for (int i = 0; i < numbers.length(); i++) {
            if (check[i]) {
                continue;
            }
            
            check[i] = true;
            bfs(depth + 1, sb.append(numbers.charAt(i)), numbers, check, set);
            check[i] = false;
            sb.setLength(sb.length() - 1);
        }
    }
    
    private boolean isPrimeNumber(int number) {
        if (number <= 1) {
            return false;
        }
        
        for (int i = 2; i < number; i++) {
            if (number % i == 0) {
                return false;
            }
        }
        
        return true;
    }
}
