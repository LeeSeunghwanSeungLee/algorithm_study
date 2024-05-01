class Solution {
    public int solution(int [][]board) {
        int answer = 0;
        
        int row = board.length;
        int col = board[0].length;
        
        // 1이 연속해서 이어진 가장 큰 정사각형의 한 변의 길이를 저장하는 배열
        int[][] dp = new int[row][col];
        
        // 첫 번째 열은 그대로 복사
        for(int i=0; i<row; i++) {
            dp[i][0] = board[i][0];
            answer = Math.max(answer, dp[i][0]);
        }
        
        // 첫 번째 행은 그대로 복사
        for(int j=0; j<col; j++) {
            dp[0][j] = board[0][j];
            answer = Math.max(answer, dp[0][j]);
        }
        
        // 나머지 칸에 대해서 DP 수행
        for(int i=1; i<row; i++) {
            for(int j=1; j<col; j++) {
                // 현재 칸이 1인 경우
                if(board[i][j] == 1) {
                    // 좌측, 상단, 좌상단의 칸들을 확인하여 가장 작은 값에 1을 더함
                    int min = Math.min(dp[i-1][j], Math.min(dp[i][j-1], dp[i-1][j-1]));
                    dp[i][j] = min + 1;
                    answer = Math.max(answer, dp[i][j]);
                }
            }
        }
        
        // 가장 큰 정사각형의 넓이 반환
        return answer * answer;
    }
}
