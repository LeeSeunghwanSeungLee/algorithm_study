class Solution {
    private int[] d_r = {-1, 0, 1, 0};
    private int[] d_c = {0, 1, 0, -1};
    private int numberOfArea;
    private int maxSizeOfOneArea;
    private boolean[][] checkBoard;
    
    public int[] solution(int m, int n, int[][] picture) {
        numberOfArea = 0;
        maxSizeOfOneArea = 0;
        checkBoard = new boolean[picture.length][picture[0].length];
        
        for (int i = 0; i < picture.length; i++) {
            for (int j = 0; j < picture[0].length; j++) {
                if (picture[i][j] == 0) continue;
                dfs(i, j, 0, picture);
            }
        }
            

        int[] answer = new int[2];
        answer[0] = numberOfArea;
        answer[1] = maxSizeOfOneArea;
        return answer;
    }
    
    private int dfs(int row, int col, int depth, int[][] picture) {
        if (checkBoard[row][col]) return 0;
        checkBoard[row][col] = true;
        if (depth == 0) numberOfArea++;
        
        
        int result = 1;
        for (int dir = 0; dir < 4; dir++) {
            int n_row = row + d_r[dir];
            int n_col = col + d_c[dir];
            if (n_row >= picture.length || n_row < 0) continue;
            if (n_col >= picture[0].length || n_col < 0) continue;
            if (picture[row][col] != picture[n_row][n_col]) continue;
            result += dfs(n_row, n_col, depth + 1, picture);
        }
        
        maxSizeOfOneArea = Math.max(maxSizeOfOneArea, result);
        return result;
    }
}
