import java.util.*;
import java.util.stream.*;

class Solution {
    public int solution(int[][] routes) {
         Arrays.sort(routes, (a, b) -> Integer.compare(a[1], b[1])); // 차량의 진출 지점을 기준으로 오름차순 정렬
        
        int answer = 1; // 첫 번째 차량이 진출 지점에 카메라가 설치되어 있으므로 최소 카메라 대수는 1부터 시작
        
        int cameraPos = routes[0][1]; // 카메라가 설치된 위치는 첫 번째 차량의 진출 지점으로 초기화
        
        for (int i = 1; i < routes.length; i++) {
            if (cameraPos < routes[i][0]) { // 다음 차량의 진입 지점이 현재 카메라 위치보다 크다면
                answer++; // 새로운 카메라를 설치하고
                cameraPos = routes[i][1]; // 해당 차량의 진출 지점을 카메라 위치로 갱신
            }
        }
        
        return answer;
    }
}
