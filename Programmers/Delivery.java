class Solution {
    private int[][] graph;
    private int HASH = 10003;
    public int solution(int N, int[][] road, int K) {
        this.graph = new int[N][N];
        for (int i = 0 ; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) this.graph[i][j] = 0;
                else this.graph[i][j] = 500001;
            }    
        }
            
        for (int[] now : road) {
            int row = now[0] - 1;
            int col = now[1] - 1;
            int dist = Math.min(this.graph[row][col], now[2]);
            this.graph[row][col] = dist;
            this.graph[col][row] = dist;
        }
        
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int min = Math.min(this.graph[i][j], this.graph[i][k] + this.graph[k][j]);
                    this.graph[i][j] = min;
                    this.graph[j][i] = min;
                }
            }
        }
        
        
        int answer = 0;
        for (int i = 0; i < N; i++) {
            if (this.graph[0][i] <= K) answer++;
        }
        return answer;
    }
}
