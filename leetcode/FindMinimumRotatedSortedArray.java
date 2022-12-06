class Solution {
    public int findMin(int[] nums) {
        int result = nums[0];
        int left = 0;
        int right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= result) {
                left = mid + 1;
            } else {
                result = nums[mid];
                right = mid - 1;
            }
        }

        return result;
    }
}
