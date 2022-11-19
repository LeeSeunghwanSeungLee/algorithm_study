class Solution {
    public int searchInsert(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;
        int result = -1;
        while (left <= right) {
            System.out.println(left + " : " + right);
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
                result = mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
                result = mid + 1;
            } else {
                result = mid;
                break;
            }
        }
        return result;
    }
}
