class Solution {
    private int size;
    private boolean[][] check;
    private int[][] board;
    private int[][] dp;
    private int answer = Integer.MAX_VALUE;
    private int[] d_r = {-1, 0, 1, 0};
    private int[] d_c = {0, 1, 0, -1};
    public int solution(int[][] board) {
        this.size = board.length;
        this.check = new boolean[this.size][this.size];
        this.board = board;
        this.dp = new int[this.size][this.size];
        intializeDp();
        
        if (this.board[0][1] == 0) {
            this.check[0][1] = true;
            DFS(0, 1, 100, 1);
            this.check[0][1] = false;
        }
        
        if (this.board[1][0] == 0) {
            this.check[1][0] = true;
            DFS(1, 0, 100, 2);
            this.check[1][0] = false;
        }
        return this.dp[this.size - 1][this.size - 1];
    }
    private void DFS(int row, int col, int cost, int pre_dir) {
        if (cost > this.dp[row][col]) return; // base_1
        else this.dp[row][col] = cost;
        
        if (row == this.size - 1 && col == this.size - 1) return; // base_2
        
        
        for (int dir = 0; dir < 4; dir++) {
            int n_row = row + d_r[dir];
            int n_col = col + d_c[dir];
            // Exception Case
            if (n_row >= this.size || n_row < 0) continue; 
            else if (n_col >= this.size || n_col < 0) continue;
            else if (this.check[n_row][n_col]) continue;
            else if (this.board[n_row][n_col] == 1) continue;
            
            int n_cost = (pre_dir == dir) ? cost + 100 : cost + 600;
            this.check[n_row][n_col] = true;
            DFS(n_row, n_col, n_cost, dir);
            this.check[n_row][n_col] = false;
        }
    }
    private void intializeDp() {
        for (int i = 0; i < this.size; i++)
            for (int j = 0; j < this.size; j++)
                this.dp[i][j] = Integer.MAX_VALUE;
    }
}
