class Solution {
    private int answer;
    public int solution(int[] stones, int k) {
        int left = 0;
        int right = 200000000;
        while(left <= right) {
            int mid = (left + right) / 2;
            if (check(stones, mid, k)) {
                right = mid - 1;
                this.answer = mid;
            } else {
                left = mid + 1;
            }
        }
        return this.answer;
    }
    
    private boolean check(int[] stones, int num, int k) {
        int skip = 0;
        for (int stone : stones) {
            if (stone <= num) skip++;
            else skip = 0;
            if (skip == k) return true;
        }
        return false;
    }
}
