class Solution {
    private int answer;
    private boolean[][][] checked;
    private int[] d_row = {-1, 0, 1, 0};
    private int[] d_col = {0, 1, 0, -1};
    public int solution(String dirs) {
        this.answer = 0;
        this.checked = new boolean[11][11][4];
        int row = 5;
        int col = 5;
        for (int i = 0; i < dirs.length(); i++) {
            int dir = getDirection(dirs.charAt(i));
            if (!isRightPosition(row, col, dir)) {
                continue;
            }
            
            if(checkUsedRoad(row, col, dir)) {
                answer++;
            }
            row += d_row[dir];
            col += d_col[dir];
            System.out.println((col - 5) + " " + (5 - row));
            
        }
        return answer;
    }
    
    private int getDirection(char dir) {
        if (dir == 'U') {
            return 0;
        } else if (dir == 'R') {
            return 1;
        } else if (dir == 'D') {
            return 2;
        }
        return 3;
    }
    
    private boolean checkUsedRoad(int row, int col, int dir) {
        if (this.checked[row][col][dir]) {
            return false;
        }
    
        this.checked[row][col][dir] = true;
        int n_row = row + d_row[dir];
        int n_col = col + d_col[dir];
        int n_dir = (dir + 2) % 4;
        this.checked[n_row][n_col][n_dir] = true;
        return true;
    }
    
    private boolean isRightPosition(int row, int col, int dir) {
        row += d_row[dir];
        col +=  d_col[dir];
        
        if (row < 0 || row > 10) {
            return false;
        }
        
        if (col < 0 || col > 10) {
            return false;
        }
        
        return true;
    }
    
    private boolean isUsedRoad(int row, int col, int dir) {
        return this.checked[row][col][dir] == true;
    } 
}
