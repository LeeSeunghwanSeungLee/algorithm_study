class Solution {
    public int search(int[] nums, int target) {
        return binarySearch(nums, 0, nums.length-1, target);
    }
    public int binarySearch(int[] nums, int start, int end, int target) {
        if(start >= end) {
            return (nums[start] == target) ? start : -1;
        }
        int result = -1;
        int mid = start + (end - start) / 2;
        if(nums[mid] == target){
            return mid;
        } 

        result = binarySearch(nums, start, mid - 1, target);

        if(result < 0) {
            result = binarySearch(nums,  mid + 1, end, target);
        }

        return result;
    } 
}
