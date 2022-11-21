class Solution {
    public void moveZeroes(int[] nums) {
        int zeroIndex = findFirstZeroIndex(0, nums);
        if (zeroIndex == -1) {
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            if (isNotZero(nums, i)) {
                if (zeroIndex > i) continue;
                // 꺼내서 zeroIndex와 위치를 스왑한다
                swap(i, zeroIndex, nums);
                zeroIndex = findFirstZeroIndex(zeroIndex, nums);
                // zeroIndex를 i로 바꾼다
                if (zeroIndex == -1) {
                    return;
                }
            }
        }
    }
    private int findFirstZeroIndex(int startIndex, int[] nums) {
        for (int i = startIndex; i < nums.length; i++) {
            if (nums[i] == 0) {
                return i;
            }
        }
        return -1;
    }

    private boolean isNotZero(int[] nums, int index) {
        return nums[index] != 0;
    }

    private void swap(int index_a, int index_b, int[] nums) {
        int temp = nums[index_a];
        nums[index_a] = nums[index_b];
        nums[index_b] = temp;
    }
}
