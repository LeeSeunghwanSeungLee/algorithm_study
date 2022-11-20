class Solution {
    public void rotate(int[] nums, int k) {
        if (k == 0) {
            return;
        }

        int gdc = getGdc(nums.length, k);
        for (int i = 0; i < gdc; i++) {
            rotateValue(nums, k, i);
        }
    }
    private void rotateValue(int[] nums, int k, int startIndex) {
        int nowIndex = startIndex;
        int nowNumber = nums[nowIndex];
        while (true) {
            int nextIndex = (nowIndex + k) % nums.length;
            int temp = nums[nextIndex];
            nums[nextIndex] = nowNumber;
            nowNumber = temp;
            nowIndex = nextIndex;

            if (nowIndex == startIndex) {
                break;
            }
        }
    }

    private int getGdc(int a, int b) {
        if(a<b) // 유클리드 호제법 조건
		{
			int temp = a;
			a = b;
			b = temp;
		}
		while(b!=0) { // 유클리드 호제법
			int r=a%b;
			a=b;
			b=r;
		}
		return a;
    }
}
