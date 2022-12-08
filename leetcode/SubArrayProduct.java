class Solution {
    public int numSubarrayProductLessThanK(int[] nums, int k) {
        if (k == 0) return 0;
        
        int count = 0;
        int product = 1;
        int left = 0, right = 0;
        
        for (; right < nums.length; right++){
            product *= nums[right];
            while (product >= k && left < nums.length) {
                product /= nums[left++];
            }
            if (right >= left) count += right - left + 1;
        }
        
        return count;
    }
}
