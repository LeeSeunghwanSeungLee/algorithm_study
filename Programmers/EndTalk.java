import java.util.*;

class Solution {
    private Set<String> usedWord;
    private char lastChar;
    public int[] solution(int n, String[] words) {
        int[] answer = {0, 0};
        
        this.usedWord = new HashSet<>();
        for (int i = 0; i < words.length; i++) {
            int now = (i % n) + 1;
            int turn = (i / n) + 1;
            String nowWord = words[i];
            char lastSpecificChar = nowWord.charAt(nowWord.length() - 1);
            char firstSpecificChar = nowWord.charAt(0);
            if (this.lastChar != firstSpecificChar && i != 0) {
                answer[0] = now;
                answer[1] = turn;
                break;
            }
            this.lastChar = lastSpecificChar;
            
            if (this.usedWord.contains(nowWord)) {
                answer[0] = now;
                answer[1] = turn;
                break;
            }
            this.usedWord.add(nowWord);
        }

        return answer;
    }
}
