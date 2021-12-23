class Solution {
    private int[][] triArr;
    public int[] solution(int n) {
        // 삼각형 구현
        this.triArr = new int[n][];
        for (int i = 0; i < n; i++)
            this.triArr[i] = new int[i + 1];
        
        makeTri(0, 0, 1, n, 0);
        int[] answer = new int[n * (n + 1) / 2];
        int k = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                answer[k++] = this.triArr[i][j];
   
        return answer;
    }
    
    private void makeTri(int startRow, int startCol, int startNum, int size, int depth) {
        if (size < 1)
            return;
     
        for (int r = startRow; r < startRow + size; r++) {
            this.triArr[r][startCol] = startNum++;
        }
        
        for (int c = startCol + 1; c < startCol + size; c++) {
            this.triArr[startRow + size - 1][c] = startNum++;
        }
        
        for (int r = startRow + size - 2; r > startRow; r--) {
            this.triArr[r][r - depth] = startNum++;
        }
        
        makeTri(startRow + 2, startCol + 1, startNum, size - 3, ++depth);
    }
}
