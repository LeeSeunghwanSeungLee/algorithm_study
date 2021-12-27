/**
 * Recommand Solution
 * Same algorithm compared with my solution but simpler..
 */

import java.util.Arrays;

class RecommandSolution {
    public int solution(int n, int s, int a, int b, int[][] fares) {
        int[][] map = new int[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(map[i], 100_000_000);
            map[i][i] = 0;
        }
        for (int[] fare : fares)
            map[fare[0]][fare[1]] = map[fare[1]][fare[0]] = fare[2];

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (map[i][j] > map[i][k] + map[k][j])
                        map[i][j] = map[i][k] + map[k][j];

        int answer = map[s][a] + map[s][b];

        for (int i = 1; i <= n; i++) 
            answer = Math.min(answer, map[s][i] + map[i][a] + map[i][b]);


        return answer;
    }
}

/**
 * Self Solution
 * Dijkstra algorithm 
 */
class SelfSolution {
    private int[][] graph;
    private final int BOUNDARY = 2000001;

    public int solution(int n, int s, int a, int b, int[][] fares) {

        this.graph = new int[n + 1][n + 1];
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) this.graph[i][j] = 0;
                else this.graph[i][j] = BOUNDARY;
            }
        }
            
        
        for (int i = 0; i < fares.length; i++) {
            int j = fares[i][0];
            int k = fares[i][1];
            int edge = fares[i][2];
            
            this.graph[j][k] = edge;
            this.graph[k][j] = edge;
        }
        
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {                    
                    int tmp = Math.min(this.graph[i][j], this.graph[i][k] + this.graph[k][j]);
                    this.graph[i][j] = tmp;
                    this.graph[j][i] = tmp;
                }
            }
        }
        
        int answer = BOUNDARY;
        for (int i = 1; i <= n; i++) {
            int tmp = Math.min(this.graph[s][i] + this.graph[i][a] + this.graph[i][b], this.graph[s][i] + this.graph[i][a] + this.graph[a][b]);
            tmp = Math.min(tmp, this.graph[s][i] + this.graph[i][b] + this.graph[b][a]);
            answer = Math.min(tmp, answer);
        }
        return answer;
    }
}
