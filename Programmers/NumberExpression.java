class Solution {
    public int solution(int n) {
        int answer = 0;
        for (int size = 1; size <= 10000; size++) {
            int target = size * (size - 1) / 2;
            if (target + size > n) break;
            if ((n - target) % size == 0)
                answer++;
        }
        return answer;
    }
}
