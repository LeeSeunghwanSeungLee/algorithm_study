import java.util.*;

class Solution {
    private int INF = 1000000000;
    public int solution(int n, int m, int[][] edge_list, int k, int[] gps_log) {
        int[][] road = new int[n + 1][n + 1];
        
        for (int i = 0; i < m; i++) {
            int s = edge_list[i][0];
            int e = edge_list[i][1];
            road[s][e] = 1;
            road[e][s] = 1;
        }
        
        int[][] dp = new int[k][n + 1];
        
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n + 1; j++) {
                dp[i][j] = INF;
            }
        }
        
        dp[0][gps_log[0]] = 0;
        
        for (int i = 1; i < k; i++) {
            for (int j = 1; j < n + 1; j++) {
                dp[i][j] = Math.min(dp[i][j], dp[i - 1][j]);
                
                for (int node = 1; node < n + 1; node++) {
                    if (road[node][j] == 1) {
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][node]);
                    }
                }
                
                if (j != gps_log[i]) dp[i][j]++;
            }
        }
        
        if (dp[k - 1][gps_log[k - 1]] < INF) return dp[k - 1][gps_log[k - 1]];
        return -1;
        
    }
}
