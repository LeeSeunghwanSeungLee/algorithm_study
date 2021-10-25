class Solution {
    private final int width = 5;
    private final int height = 5;
    private final int[] d_r = {-1, 0, 1, 0};
    private final int[] d_c = {0, 1, 0, -1};
    
    private boolean[][] flag = new boolean[5][5];
    
    public int[] solution(String[][] places) {
        int[] answer = new int[places.length];
        
        for(int i = 0; i < places.length; i++){
            if(solve(places[i])) {
                answer[i] = 0;
                continue;
            }
            answer[i] = 1;
        }
        return answer;
    }
    
    private void initializeFlag(){
        for(int i = 0; i < this.height; i++){
            for(int j = 0; j < this.width; j++){
                this.flag[i][j] = false;
            }
        }
    }
    
    private boolean solve(String[] waitingRoom){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(waitingRoom[i].charAt(j) == 'P') {
                    initializeFlag();
                    this.flag[i][j] = true;
                    if(dfs(i, j, 0, waitingRoom)) return true;
                }
            }
        }
        
        return false;
    }
    
    private boolean dfs(int row, int col, int depth,String[] waitingRoom){
        if(depth > 2) return false;
        
        if(waitingRoom[row].charAt(col) == 'P' && depth != 0) return true;
        
        if(waitingRoom[row].charAt(col) == 'X') return false;
        
        
        
        for(int dir = 0; dir < 4; dir++){
            int n_r = row + d_r[dir];
            int n_c = col + d_c[dir];
            
            if(n_r < 0 || n_r >= this.height) continue;
            
            if(n_c < 0 || n_c >= this.width) continue;
            
            if(this.flag[n_r][n_c]) continue;
            
            this.flag[n_r][n_c] = true;
            if(dfs(n_r, n_c, depth + 1, waitingRoom)) return true;
            this.flag[n_r][n_c] = false;
        }
        
        return false;
    }
}
