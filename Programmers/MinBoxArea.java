class Solution {
    public int solution(int[][] sizes) {
			int min = -1;
			int max = -1;

			for (int[] wallet : sizes) {
				int[] sortedWallet = sortInArr(wallet);
				min = Math.max(min, sortedWallet[0]);
				max = Math.max(max, sortedWallet[1]);
			}
			
			return min * max;
		}
		
		public int[] sortInArr(int[] arr) {
			int a = arr[0];
			int b = arr[1];
			return a < b ? new int[]{a, b} : new int[]{b , a};
		}
}
