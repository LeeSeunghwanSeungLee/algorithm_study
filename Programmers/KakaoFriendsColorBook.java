import java.util.Arrays;

class Solution {
    private boolean[][] flag;
    private int maxSizeOfOneArea;
    private int numberOfArea;
    private int depth;
    
    private final int[] row = {-1, 0, 1, 0};
    private final int[] col = {0, 1, 0, -1};
    
    public int[] solution(int m, int n, int[][] picture) {

        flag = new boolean[m][n];

        for(int i = 0; i < m; i++){
            Arrays.fill(this.flag[i], false);
        }
        this.maxSizeOfOneArea = 0;
        this.numberOfArea = 0;
        
        for(int row = 0; row < m; row++){
            for(int col = 0; col < n; col++){
                if(this.flag[row][col] || picture[row][col] == 0) continue;
                
                this.depth = 0;
                this.numberOfArea++;
                DFS(0, row, col, picture);
                this.maxSizeOfOneArea = Math.max(this.maxSizeOfOneArea, this.depth);
            }
        }
        
        int[] answer = new int[2];
        answer[0] = this.numberOfArea;
        answer[1] = this.maxSizeOfOneArea;
        return answer;
    }
    
    public void DFS(int depth, int row, int col, int[][] picture){
        this.depth++;
        
        int color = picture[row][col];
        
        this.flag[row][col] = true;
               
        boolean aTempFlag = false;

        for(int dir = 0; dir < 4; dir++){
            int next_row = row + this.row[dir];
            int next_col = col + this.col[dir];
            if(next_row < 0 || next_row >= picture.length) continue;
            if(next_col < 0 || next_col >= picture[0].length) continue;
            if(this.flag[next_row][next_col] || picture[next_row][next_col] != color) continue;
            
            DFS(depth, next_row, next_col, picture);
        }
  
    }
}
