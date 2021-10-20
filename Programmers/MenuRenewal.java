import java.util.*;

class Solution {
    static HashMap<String, Integer> hm;
    public String[] solution(String[] orders, int[] course) {
        hm = new HashMap<>();
        
        for(String o: orders) {
            char[] order = o.toCharArray();
            Arrays.sort(order);
            for(int i=0; i< course.length; i++) {
                combination(0, 0, course[i], order, "");
            }
        }
        
        int[] maxCntOfCourse = new int[course[course.length -1] +1]; // course가 2,3,4인 경우 0~4까지
        for(String key: hm.keySet()) {
            // 최소 2명 이상의 손님으로부터
            if(hm.get(key) >= 2) {
                maxCntOfCourse[key.length()] = Math.max(hm.get(key), maxCntOfCourse[key.length()]);
            }
        }
        
        // maxCntOfCourse에 각 코스별 가장 많이 주문된 횟수가 채워진 상태
        List<String> answerTemp = new ArrayList<>();
        for(String key: hm.keySet()) {
            for(int i=0; i< maxCntOfCourse.length; i++) {
                if(maxCntOfCourse[i] == 0) continue;
                if(key.length() == i && hm.get(key) == maxCntOfCourse[i]) {
                    answerTemp.add(key);
                }
            }
        }
        
        Collections.sort(answerTemp);
        String[] answer = new String[answerTemp.size()];
        int i=0;
        for(String str: answerTemp) {
            answer[i++] = str;
        }
        
        return answer;
    }
    
    private static void combination(int cnt, int start, int limit, char[] order, String result) {
        if(cnt == limit) {
            hm.put(result, hm.getOrDefault(result, 0)+1);
            return;
        }
        
        for(int i=start; i< order.length;i++) {
            combination(cnt+1, i+1, limit, order, result+order[i]);
        }
    }
}
