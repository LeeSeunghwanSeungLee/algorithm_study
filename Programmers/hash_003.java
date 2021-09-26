import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;


class Solution {
    public int solution(String[][] clothes) {
        int answer = 1;
        HashMap<String,Integer> clothesMap = new HashMap<String, Integer>();
        
        for(int i = 0; i < clothes.length; i++){
            int x = 1;
            if (clothesMap.containsKey(clothes[i][1])) {
                x = clothesMap.get(clothes[i][1])+1;
            }
            clothesMap.put(clothes[i][1], x);
        }
        
        Set<String> keySet = clothesMap.keySet(); 
        
        for(String key : keySet) {
        	answer *= clothesMap.get(key)+1; 
        }
        return answer-1; 
    }
}