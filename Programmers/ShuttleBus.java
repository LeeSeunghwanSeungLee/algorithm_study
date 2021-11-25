import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
class Solution {
    public String solution(int n, int t, int m, String[] timetable) {
       	int answer = 0;
        //크루들 도착시간 오름차순 정렬하여 빼서 쓰기위해
		PriorityQueue<Integer> q = new PriorityQueue<>();
        //셔틀버스 시작시간인 09:00시
		int departT = 9*60;
		List<Integer>[] list = new List[n];
        
        //크루들 도착시간을 숫자로 변환하여 큐에 저장
		for (int i = 0; i < timetable.length; i++) {
			int hh = Integer.parseInt(timetable[i].split(":")[0]);
			int mm = Integer.parseInt(timetable[i].split(":")[1]);
			int time = hh*60 + mm;
			
			q.add(time);
			
		}
		
        //09:00시부터 시작하여 시간간격 t만큼 셔틀버스 배치
        //총 몇대 운행하는지로 반복문 사용
		for (int i = 0; i < n; i++) {
			list[i] = new ArrayList<>();
            
            //기다리고 있는 크루들이 있을경우
			while(!q.isEmpty()) {
				int arrivedT = q.poll();
                //현재 도착해있는 셔틀버스보다 일찍 도착하고, 셔틀버스 정원이 차지 않았을 경우
				if(arrivedT <= departT && list[i].size() < m) {
                	//셔틀버스에 크루를 태움 -> 셔틀버스 정원 확인하기 위해
					list[i].add(arrivedT);
				}
                //현재 도착해있는 크루가 없을 경우 이미 뺀 크루의 시간을 다시 넣어줌
				else {
					q.add(arrivedT);
					break;
				}
                //마지막 크루보다 1분 일찍 와야되므로 계속 갱신해줌
				answer = arrivedT-1;
			}
            //다음 셔틀버스 도착시간 갱신
			departT += t;
			

		}
        //마지막 버스가 비었을 경우 마지막 버스 도착시간에 맞춰서 오는게 정답
		if(list[n-1].size() < m) {
			answer = departT - t;
		}
		String hh = String.format("%02d",answer/60);
		String mm = String.format("%02d",answer%60);
        return hh+":"+mm;
    }
}
