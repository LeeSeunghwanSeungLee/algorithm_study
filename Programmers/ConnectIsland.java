import java.util.*;

class Solution {
    private int[] parent;
    public int solution(int n, int[][] costs) {
        parent = new int[n];
        for(int i=0; i<n; i++)
            parent[i] = i;

        Arrays.sort(costs, Comparator.comparingInt(o -> o[2]));

        int answer = 0;
        for (int[] cost : costs) {
            if (getParent(cost[0]) != getParent(cost[1])) {
                answer += cost[2];
                merge(cost[0], cost[1]);
            }
        }

        return answer;
    }

    public int getParent(int node){
        if(parent[node] == node)
            return node;
        else
            return getParent(parent[node]);
    }

    public void merge(int startNode, int endNode){
        int startParent = getParent(startNode);
        int endParent = getParent(endNode);

        if(startParent > endParent)
            parent[startParent] = endParent;
        else
            parent[endParent] = startParent;
    }
}
