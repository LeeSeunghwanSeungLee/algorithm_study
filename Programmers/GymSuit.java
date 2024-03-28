import java.util.*;

class Solution {
    public int solution(int n, int[] lost, int[] reserve) {
        int answer = n - lost.length; // 일단 체육복을 잃어버린 학생 수만큼 뺀다.
        Arrays.sort(lost); // 도난당한 학생들 번호를 오름차순으로 정렬
        Arrays.sort(reserve); // 여벌의 체육복을 가져온 학생들 번호를 오름차순으로 정렬
        
        // 여벌의 체육복을 가져온 학생이 도난당한 경우를 처리
        for (int i = 0; i < lost.length; i++) {
            for (int j = 0; j < reserve.length; j++) {
                if (lost[i] == reserve[j]) {
                    lost[i] = -1; // 해당 학생은 체육복을 빌릴 필요 없으므로 -1로 표시
                    reserve[j] = -1; // 해당 학생은 체육복을 빌려주었으므로 -1로 표시
                    answer++; // 체육복을 빌린 학생 수 증가
                    break;
                }
            }
        }
        
        // 여벌의 체육복을 가져온 학생이 체육복을 빌려주는 경우를 처리
        for (int i = 0; i < lost.length; i++) {
            for (int j = 0; j < reserve.length; j++) {
                if (lost[i] == reserve[j] - 1 || lost[i] == reserve[j] + 1) {
                    reserve[j] = -1; // 체육복을 빌려준 학생은 다시 빌려줄 수 없으므로 -1로 표시
                    answer++; // 체육복을 빌린 학생 수 증가
                    break;
                }
            }
        }
        
        return answer;
    }
}
