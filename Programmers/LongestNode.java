import java.util.*;

public class LongestNode {
    
}


class Solution {
    public int solution(int n, int[][] edge) {
        boolean[] check = new boolean[n];
        boolean[][] connected = new boolean[n][n];

        Queue<Integer> q = new LinkedList<>();
        for(int i = 0; i < n; i++){
            connected[edge[i][0] - 1][edge[i][1] - 1] = true;
            connected[edge[i][1] - 1][edge[i][0] - 1] = true;
        }

        check[0] = true;
        q.add(0);
        
        int answer = 0;
        while(!q.isEmpty()){
            int qSize = q.size();
            for(int i = 0; i < qSize; i++){
                int node = q.poll();
                for(int j = 0; j < n; j++){
                    if(connected[node][j] && !check[j]){
                        q.add(j);
                        check[j] = true;
                    }
                }
            }
            answer = qSize;
        }
        return answer;
    }
}