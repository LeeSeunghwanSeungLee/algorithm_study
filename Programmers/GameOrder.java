class Solution {
    public int solution (int n, int[][] results) {
        boolean[][] game = new boolean[n][n];
        int answer = 0;
        
        for (int i = 0; i < results.length; i++) {
            int row = results[i][0] - 1;
            int col = results[i][1] - 1;
            game[row][col] = true;
        }
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (game[i][k] && game[k][j]) game[i][j] = true;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            int result = 0;
            for (int j = 0; j < n; j++) {
                if (game[i][j] || game[j][i]) result++;
            }
            if (result == n - 1) answer++;
        }
        
        return answer;
    }
}
