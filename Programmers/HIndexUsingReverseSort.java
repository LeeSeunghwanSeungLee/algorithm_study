import java.util.*;

class Solution {
    public int solution(int[] citations) {
        Integer[] arr = Arrays.stream(citations).boxed().toArray(Integer[]::new);
        Arrays.sort(arr, (a, b) -> b - a); // reverse order

        if(arr[0] == 0) return 0;

        int h = citations.length;
        for(int i = 0; i < citations.length; i++){
            if(arr[i] >= i + 1) h = i + 1;
        }

        return h;
    }
}
