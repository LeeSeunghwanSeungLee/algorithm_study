class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        int targetRow = findSameOrUnderBoundRow(matrix, target);
        return targetRow != -1 ? findBinarySearch(matrix[targetRow], target) : false;
    }
    private int findSameOrUnderBoundRow(int[][] matrix, int target) {
        int left = 0;
        int right = matrix.length - 1;
        int result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[mid][0] < target) {
                result = mid;
                left = mid + 1;
            } else if (matrix[mid][0] > target){
                right = mid - 1;
            } else {
                result = mid;
                break;
            }
        }
        return result;
    }

    private boolean findBinarySearch(int[] matrix, int target) {
        int left = 0;
        int right = matrix.length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (matrix[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return matrix[left] == target;
    }
}
