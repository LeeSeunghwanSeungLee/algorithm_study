import java.util.*;

class Solution {
    private Map<String, Boolean> flag;
    public int solution(String begin, String target, String[] words) {
        this.flag = new HashMap<>();
        
        this.flag.put(begin, true);
        for (int i = 0; i < words.length; i++)
            this.flag.put(words[i], false);
        
        if (!this.flag.containsKey(target)) return 0;
        
        
        
        return BFS(begin, target);
    }
    
    private int BFS(String startWord, String endWord) {
        Queue<Node> q = new LinkedList<>();
        q.add(new Node(startWord, 0));
        while(!q.isEmpty()) {
            Node nowNode = q.poll();
            if (nowNode.getWord().equals(endWord)) return nowNode.getDepth();
            
            StringBuilder nowWord = new StringBuilder(nowNode.getWord());
            int depth = nowNode.getDepth() + 1;
            for (int i = 0; i < 26; i++) {
                char c = (char)(97 + i);
                for (int j = 0; j < startWord.length(); j++) {
                    char tmp = nowWord.charAt(j);
                    
                    nowWord.setCharAt(j, c);
                    String now = nowWord.toString();
                    nowWord.setCharAt(j, tmp);
                    boolean res = this.flag.getOrDefault(now, true);
                    if (res) 
                        continue;
                    
                    this.flag.put(now, true);
                    
                    q.add(new Node(now, depth));
                }
            }
        }
        return 0;
    }
}

class Node {
    String word;
    int depth;
    public Node(String word, int depth) {
        this.word = word;
        this.depth = depth;
    }
    
    public String getWord() {
        return this.word;
    }
    
    public int getDepth() {
        return this.depth;
    }
}
