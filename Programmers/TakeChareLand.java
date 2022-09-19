class Solution {
    private static int COL_SIZE = 4;
    int solution(int[][] land) {
        // initialize
        int[][] dp = new int[land.length][COL_SIZE];
        for (int col = 0; col < COL_SIZE; col++) {
            dp[0][col] = land[0][col];
        }
        // dp
        for (int i = 1; i < land.length; i++) {
            for (int j = 0; j < COL_SIZE; j++) {
                dp[i][j] = land[i][j] + getMaxInRowExceptColumn(i - 1, j, dp);
            }
        }
        
        return Math.max(Math.max(dp[land.length - 1][0], dp[land.length - 1][1]), Math.max(dp[land.length - 1][2], dp[land.length - 1][3]));
    }
    
    private int getMaxInRowExceptColumn(int row, int col, int[][] land) {
        if (col == 0) {
            return Math.max(Math.max(land[row][1], land[row][2]), land[row][3]);
        } else if (col == 1) {
            return Math.max(Math.max(land[row][0], land[row][2]), land[row][3]);
        } else if (col == 2) {
            return Math.max(Math.max(land[row][1], land[row][0]), land[row][3]);
        }
        
        return Math.max(Math.max(land[row][1], land[row][2]), land[row][0]);
    }
}
