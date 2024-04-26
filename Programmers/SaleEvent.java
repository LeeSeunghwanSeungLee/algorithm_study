import java.util.*;
import java.util.stream.Collectors;


class Solution { 
    public int solution(String[] want, int[] number, String[] discount) {
        int answer = 0;
        
        WannabeList list = new WannabeList(want, number);
        
        for (int day = 0; day < discount.length; day++) {
           list.remove(discount[day]);
            if (day >= 10) {
                list.add(discount[day - 10]);
            } 
            
            if (list.isDone()) answer++;
        }
        
        return answer;
    }
    
    static class WannabeList {
        Map<String, Integer> map = new HashMap<>();
        
        WannabeList(String[] want, int[] number) {
            for (int i = 0; i < want.length; i++) {
                map.put(want[i], number[i]);
            }
        }
        
        public void add(String item) {
            if (!map.containsKey(item)) return;
            map.put(item, map.getOrDefault(item, 0) + 1);
        }
        
        public void remove(String item) {
            if (!map.containsKey(item)) return;
            map.put(item, map.get(item) - 1);
        }
        
        public boolean isDone() {
            return map.values().stream()
					.filter(val -> val > 0)
					.collect(Collectors.toList()).size() <= 0;
        }
    }
}
