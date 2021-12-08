import java.util.*;

class Solution {
    public int[] solution(int brown, int red) {
        int a = (brown+4)/2;
        int b = brown + red
        int[] answer = {(int)(a+Math.sqrt(a*a-4*b))/2,(int)(a-Math.sqrt(a*a-4*b))/2};
        return answer;
    }
}

class Solution2 {
  public int[] solution(int brown, int yellow) {
        int[] answer = new int[2];
 
        int area = brown + yellow; // 전체 격자 개수
 
        for (int i = 1; i <= area; i++) {
            int row = i;
            int col = area / row;    
 
            if (row > col)
                break;
 
            if ((row - 2) * (col - 2) == yellow) {
                answer[0] = col;
                answer[1] = row;
                return answer;
            }
        }
        return answer;
    }
}
// yellow 는 red와 동일.. 중간에 문제 버전이 수정된 것으로 보임..
