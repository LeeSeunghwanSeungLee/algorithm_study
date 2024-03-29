import java.util.Arrays;
import java.util.List;
import java.util.stream.*;

class Solution {

	public String solution(int[] numbers) {

		// 숫자를 문자열로 변환
			List<String> numbersAsString = Arrays.stream(numbers)
                    .boxed()
                    .map(String::valueOf).sorted((a, b) -> (b + a).compareTo(a + b)).collect(Collectors.toList());
			
			if (numbersAsString.get(0).startsWith("0")) {
				return "0";
			}
			
			return numbersAsString.stream()
				.reduce("", (accum, elem) -> accum + elem);
	}
}
