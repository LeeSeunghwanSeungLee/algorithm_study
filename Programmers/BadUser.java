import java.util.*;
 
class Solution {
    
    HashSet<String> set;
    String[] regex;
    String[] user;
    boolean[] visited;
    
    public int solution(String[] user_id, String[] banned_id) {
        set = new HashSet<>();
        user = user_id;
        
        regex = new String[banned_id.length];
        for(int i = 0; i < banned_id.length; i++) {
            regex[i] = banned_id[i].replace("*", ".");
        }
        
        visited = new boolean[user.length];
        DFS(0, "");
        return set.size();
    }
    
    public void DFS(int idx, String result) {
        if(idx == regex.length) {
            String[] str = result.split(" ");
            Arrays.sort(str);
            
            String newstr = "";
            for(int i = 0; i < str.length; i++) {
                newstr += str[i];
            }
            set.add(newstr);
            return;
        }
        
        for(int i = 0; i < user.length; i++) {
            if(visited[i] == false && user[i].matches(regex[idx])) {
                visited[i] = true;
                DFS(idx + 1, result + " " + user[i]);
                visited[i] = false;
            }
        }
    }
}
