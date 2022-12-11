class Solution {
    private int[] r_d = {-1, 0, 1, 0};
    private int[] r_c = {0, 1, 0, -1};
    public int numIslands(char[][] grid) {
        int result = 0;
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[0].length; c++) {
                if (dfs(r, c, grid)) {
                    result++;
                }
            }
        }
        return result;
    }

    private boolean dfs(int row, int col, char[][] grid) {
        if (grid[row][col] == '0') {
            return false;
        }

        grid[row][col] = '0';
        for (int dir = 0; dir < 4; dir++) {
            int n_row = row + r_d[dir];
            if (n_row < 0 || n_row >= grid.length) {
                continue;
            }

            int n_col = col + r_c[dir];
            if (n_col < 0 || n_col >= grid[0].length) {
                continue;
            }
            dfs(n_row, n_col, grid);
        }
        return true;
    }
}
