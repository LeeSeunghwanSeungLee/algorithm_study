/**
 * 내 정답
 */
class MySolution {
    private char[] charList = { 'A', 'E', 'I', 'O', 'U'};
    private int count;
    public int solution(String word) {
        this.count = 0;
        dfs(word, "", 0);
        return this.count;
    }
    
    private boolean dfs(String target, String now, int d) {        
        if (target.equals(now)) {
            return true;
        }
        
        if (d == 5) return false;
        
        for (int i = 0; i < 5; i++) {
            this.count++;
            if (dfs(target, now + this.charList[i], d + 1)) return true;
        }
        return false;
    }
}
/**
 * 추천 정답
 */
class SuperSolution {
    public int solution(String word) {
        int answer = 0, per = 3905;
        for(String s : word.split("")) answer += "AEIOU".indexOf(s) * (per /= 5) + 1;
        return answer;
    }
}
