import java.util.*;

class ThanskGivingTraffic {
	public int solution(String[] lines) {
		int answer = 0;
		int[] startTimes = new int[lines.length];
		int[] endTimes = new int[lines.length];
		
		getTimes(lines, startTimes, endTimes);
		
		for(int i = 0 ; i < lines.length ; ++i) {
			int cnt = 0;
			int startOfSection = startTimes[i];
			int endOfSection = startOfSection + 1000;
			
			for(int j = 0 ; j < lines.length ; ++j) {
				if(startTimes[j] >= startOfSection && startTimes[j] < endOfSection) {
					cnt++;
				} else if(endTimes[j] >= startOfSection && endTimes[j] < endOfSection) {
					cnt++;
				} else if(startTimes[j] <= startOfSection && endTimes[j] >= endOfSection) {
					cnt++;
				}
			}

			answer = cnt > answer ? cnt : answer;
		}
		
		for(int i = 0 ; i < lines.length ; ++i) {
			int cnt = 0;
			int startOfSection = endTimes[i];
			int endOfSection = startOfSection + 1000;
			
			for(int j = 0 ; j < lines.length ; ++j) {
				if(startTimes[j] >= startOfSection && startTimes[j] < endOfSection) {
					cnt++;
				} else if(endTimes[j] >= startOfSection && endTimes[j] < endOfSection) {
					cnt++;
				} else if(startTimes[j] <= startOfSection && endTimes[j] >= endOfSection) {
					cnt++;
				}
			}

			answer = cnt > answer ? cnt : answer;
		}
		
		return answer;
	}

	private void getTimes(String[] lines, int[] startTimes, int[] endTimes) {
		for(int i = 0 ; i < lines.length ; ++i) {
			String[] log = lines[i].split(" ");
			String[] responseTime = log[1].split(":");
			int processingTime = (int)(Double.parseDouble(log[2].substring(0, log[2].length() - 1)) * 1000);
			int startTime = 0;
			int endTime = 0;
			
			endTime += Integer.parseInt(responseTime[0]) * 60 * 60 * 1000;
			endTime += Integer.parseInt(responseTime[1]) * 60 * 1000;
			endTime += (int)(Double.parseDouble(responseTime[2]) * 1000);
			startTime = endTime - processingTime + 1;
			
			startTimes[i] = startTime;
			endTimes[i] = endTime;
		}
    }
}

// 배운점

// 1. partseInt & parseFloat 등은 Wrapper Class 에 포함되어 있음
// 2. sliding 기법의 경우 startOfSection & endOfSection 2가지 가능성을 고려해야하며 각 영역별 포함관계는 3가지 케이스가 존재(좌로 겹침, 포함 겹침, 우로겹침)
// 3. O(n) 이면 나름 준수한 퍼포먼스임