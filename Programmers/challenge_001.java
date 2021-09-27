import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;


public class challenge_001 {
	public static void main(String[] args) {
		int[] numbers = {5,0,2,7};
		Solution s = new Solution();
		int[] rtnArr = s.solution(numbers);

		for (int i = 0; i < rtnArr.length; i++) {
			System.out.println("값 : " + rtnArr[i]);
		}
	}


}

class Solution {
    public int[] solution(int[] numbers) {
        int[] answer = {};
        Map<Integer, Integer> map = new TreeMap<Integer, Integer>();
        for (int i = 0; i < numbers.length; i++) {
			for (int j = i+1; j < numbers.length; j++) {
				map.put(numbers[i] + numbers[j], numbers[i] + numbers[j]);
			}
		}

        Iterator<Integer> keys = map.keySet().iterator();
        int cnt = 0;
        answer = new int[map.size()];
        while(keys.hasNext()) {
        	int key = keys.next();
        	answer[cnt++] = map.get(key);
        }

        return answer;
    }
}
