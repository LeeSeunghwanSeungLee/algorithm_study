import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

class Solution {
    List<String> stack;
    Map<String, String> nickname;
    
    public String[] solution(String[] record) {
        this.stack = new ArrayList<>();
        this.nickname = new HashMap<>();
        
        for(int i = 0; i < record.length; i++){
            orderSet(record[i]);
        }
        
        String[] answer = new String[this.stack.size()];
        for(int i = 0; i < this.stack.size(); i++){
            String[] res = this.stack.get(i).split("-");
            String name = this.nickname.get(res[0]);
            answer[i] = name + res[1];
        }
        return answer;
    }
    
    public void orderSet(String record){
        String[] now = record.split(" ");
        
        if(now[0].equals("Enter")){
            this.nickname.put(now[1], now[2]);
            this.stack.add(now[1] + "-" + "님이 들어왔습니다.");
            
            return;
        } else if(now[0].equals("Change")){
            this.nickname.put(now[1], now[2]);
            
            return;
        } else {
            this.stack.add(now[1] + "-님이 나갔습니다.");
        }
        
    }
}
