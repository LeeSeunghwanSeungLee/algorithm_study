public class Triangle {
    
}

/* Use Brute Force */
class Solution {
    public int solution(int[][] triangle) {
        return relation(0, 0, triangle);
    }
    public int relation(int depth, int index, int[][] triangle){
        if(depth >= triangle.length) return 0;

        return triangle[depth][index] + Math.max(dp(depth + 1, index, triangle), dp(depth + 1, index + 1, triangle));
    }
}


/* Use Dynamic Programming */
class Solution2 {
    public int solution(int[][] triangle) {
        // 1. 기본값 초기화  //
      int[][] dp = new int[triangle.length][triangle.length];
        dp[0][0] = triangle[0][0];
        for(int i = 1; i < triangle.length; i++) {
           dp[i][0] = dp[i - 1][0] + triangle[i][0]; 
           dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        }
         
        // 2. 동적계획법 //
        for(int i = 2; i < triangle.length; i++) 
           for(int j = 1; j < i; j++) 
              dp[i][j] = Math.max(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
         
        // 3. 최대값 반환 //
        int max = 0;
        for(int i = 0; i < dp.length; i++) 
           max = Math.max(max, dp[dp.length - 1][i]);
       
      return max;
    }
}