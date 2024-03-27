import java.util.*;
import java.util.stream.Collectors;

class Solution {
    public int[] solution(int[] array, int[][] commands) {
			int[] result = new int[commands.length];
			
			for (int i = 0; i < commands.length; i++) {
				int[] now = commands[i];
				List<Integer> concatArr = concatArr(array, now[0] - 1, now[1]);
                concatArr.sort((a, b) -> a - b);
				result[i] = concatArr.get(now[2] - 1);
			}
			return result;
		}

		public List<Integer> concatArr(int[] arr, int s, int e) {
			List<Integer> arrList = Arrays.stream(arr)
				.boxed()
				.collect(Collectors.toList());

			return arrList.subList(s, e);
		}
}
