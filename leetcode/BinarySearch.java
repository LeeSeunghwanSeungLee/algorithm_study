class Solution {
    public int search(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;
        while (left <= right) {
            int nowIndex = (left + right) / 2;
            int indexNumber = nums[nowIndex];
            if (indexNumber == target) {
                return nowIndex;
            } else if (indexNumber < target) {
                left = nowIndex + 1;
            } else {
                right = nowIndex - 1;
            }
        }
        return -1;
    }
}
