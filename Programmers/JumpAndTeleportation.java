public class Solution {
    public int solution(int n) {
        return dfs(n);
    }
    private int dfs(int depth) {
        if (depth == 1 || depth == 2) return 1;
        int res = 0;
        if (depth % 2 == 0) {
            res += dfs(depth / 2);
            return res;
        }
        res += (dfs(depth - 1) + 1);
        return res;
    }
}
