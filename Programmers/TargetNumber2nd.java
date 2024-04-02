class Solution {

		int[] signs = new int[]{-1, 1};
		int answer = 0;

		public int solution(int[] numbers, int target) {
			calc(target, 0, numbers, 0);


			return answer;
		}

		public void calc(int target, int accum, int[] elems, int depth) {
			if (depth >= elems.length) {
				if (target == accum) answer++;
				return;
			}

			for (int i = 0; i < 2; i++) {
				int now = accum + elems[depth] * signs[i];
				calc(target, now, elems, depth + 1);
			}
		}
	}
