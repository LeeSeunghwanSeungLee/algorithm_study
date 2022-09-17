class Solution {
    public int[] solution(int n, long left, long right) {
        int[] answer = new int[(int)(right - left) + 1];
        for (long i = left; i <= right; i++) {
            long row = getConvertedRow(n, i);
            long col = getConvertedCol(n, i);
            answer[(int)(i - left)] = getMapNumber(row, col);
        }
        return answer;
    }
    
    private int getMapNumber(long row, long col) {
        return (int)Math.max(row + 1, col + 1);
    }
    
    private long getConvertedIndex(int size, int row, int col) {
        return size * row + col;
    }
    
    private long getConvertedCol(int size, long num) {
        return num % size;
    }
  
    private long getConvertedRow(int size, long num) {
        return (num - getConvertedCol(size, num)) / size;
    }
}
