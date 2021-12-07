import java.util.*;

class Solution {
    public int solution(int[] citations) {
        int length = citations.length;
        int start = 0;
        int mid;
        int end = length;

        Arrays.sort(citations);
        /* H-Index 최대값 이분 탐색 */
        while (start < end) {
            mid = (start + end + 1) / 2;
            if (citations[length - mid] >= mid) {
                start = mid;
            } else {
                end = mid - 1;
            }
        }
        return start;
    }
}
