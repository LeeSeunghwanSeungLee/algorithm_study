class Solution {
    public int[] runningSum(int[] nums) {
        int[] result = new int[nums.length];
        int cumulateNumber = 0;
        for (int i = 0; i < nums.length; i++) {
            cumulateNumber += nums[i];
            result[i] = cumulateNumber;
        }
        return result;
    }
}
