import java.util.*;

class Solution {
    public int solution(int []A, int []B) {    
        // given
        Integer[] b = Arrays.stream(B)
                        .boxed()
                        .toArray( Integer[]::new );
        Arrays.sort(A);
        Arrays.sort(b,Collections.reverseOrder());
        
        // when
        int answer = 0;
        for(int i = 0;i<A.length;i++){
            answer+=(A[i] * b[i]);
        }        

        // then
        return answer;
    }
}
