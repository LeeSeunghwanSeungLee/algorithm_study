/**
 * 내가 작성한 답
 * Brute Force (DFS)
 */
class Solution {
    private boolean[][] graph;
    private int answer;
    public int solution(int n, int[][] wires) {
        this.graph = new boolean[n + 1][n + 1];
        this.answer = Integer.MAX_VALUE;
        
        for (int[] wire : wires) {
            int v_1 = wire[0];
            int v_2 = wire[1];
            this.graph[v_1][v_2] = true;
            this.graph[v_2][v_1] = true;
        }
        
        for (int[] wire : wires) {
            int v_1 = wire[0];
            int v_2 = wire[1];
            
            this.graph[v_1][v_2] = false;
            this.graph[v_2][v_1] = false;
            
            this.answer = Math.min(this.answer, Math.abs(dfs(v_1) - dfs(v_2)));
                                   
            this.graph[v_1][v_2] = true;
            this.graph[v_2][v_1] = true;
        }
        
        return this.answer;
    }
    
    private int dfs(int v) {
        int res = 1;
        for (int i = 1; i < this.graph.length; i++) {
            if (!this.graph[v][i]) continue;
            
            this.graph[v][i] = false;
            this.graph[i][v] = false;
            res += dfs(i);
            this.graph[v][i] = true;
            this.graph[i][v] = true;
        }
        return res;
    }
}
/**
 * 추천 답안
 * O(N)
 */
import java.util.*;

class Solution {
    private boolean[][] graph;
    private int answer;
    private int nodeNumber;
    public int solution(int n, int[][] wires) {
        this.graph = new boolean[n + 1][n + 1];
        this.answer = Integer.MAX_VALUE;
        this.nodeNumber = n;
        for (int[] wire : wires) {
            int v_1 = wire[0];
            int v_2 = wire[1];
            this.graph[v_1][v_2] = true;
            this.graph[v_2][v_1] = true;
        }
        
        dfs(1);
        
        return this.answer;
    }
    
    private int dfs(int v) {
        int res = 1;
        for (int i = 1; i < this.graph.length; i++) {
            if (!this.graph[v][i]) continue;
            
            this.graph[v][i] = false;
            this.graph[i][v] = false;
            res += dfs(i);
            this.graph[v][i] = true;
            this.graph[i][v] = true;
        }
        this.answer = Math.min(this.answer, Math.abs(this.nodeNumber - 2 * res));
        return res;
    }
}
