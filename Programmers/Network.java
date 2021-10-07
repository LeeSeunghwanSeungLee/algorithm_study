import java.util.Arrays;

class Solution {
    
    private boolean[] check;
    private int answer;

    public int solution(int n, int[][] computers){
        this.check = new boolean[n];
        Arrays.fill(this.check, Boolean.FALSE);

        this.answer = 0;

        for(int i = 0; i < n; i++){
            if(check[i]) continue;

            check[i] = true;
            dfs(i, n, computers);
            this.answer++;
        }

        return this.answer;
    }

    public void dfs(int node, int n, int[][] computers){
        for(int i = 0; i < n; i++){
            if(this.check[i] == true) continue;
            if(computers[node][i] != 1) continue;
            // 체크 표시
            this.check[i] = true;
            dfs(i, n, computers);
        }
    }
}