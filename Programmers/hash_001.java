import java.util.*;

class Solution {
    public String solution(String[] participant, String[] completion){
        String answer = "";


       Map <String, Integer> hm = new HashMap<String, Integer>();

        for(String p_member : participant){
            if(hm.get(p_member) == null){
                hm.put(p_member, 1);
            }
            else{
                hm.put(p_member, hm.get(p_member) + 1);
            }
        }

        for(String c_mem : completion){
            hm.put(c_mem, hm.get(c_mem) - 1);
        }

        for(String key : hm.keySet()){
            if(hm.get(key) == 1) answer = key;
        }
        return answer;
    }
}

/*
    배운점
    1. HashMap 은 삽입시를 제외하고는 접근에서 o(1) 의 성능을 보여준다.
    2. 제너릭스를 사용하는 이유는 컴파일타임에 런타임 에러를 미리 잡기 위함이다(ex> 참조타입을 미리 설정해놓는다)
*/
