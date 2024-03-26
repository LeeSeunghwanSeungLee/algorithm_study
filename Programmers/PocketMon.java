import java.util.*;

class Solution {
    public int solution(int[] nums) {
        Set numSet = new HashSet<>();
		for (int num : nums) {
			numSet.add(num);
		}

		if (nums.length / 2 < numSet.size()) {
			return nums.length / 2;
		}

		return numSet.size();
    }
}
