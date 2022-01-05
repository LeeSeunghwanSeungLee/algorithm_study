import java.util.*;

class MySolution {
    private int time;
    private List<String> cacheList;
    private int cacheSize;
    public int solution(int cacheSize, String[] cities) {
        this.time = 0;
        this.cacheSize = cacheSize;
        this.cacheList = new LinkedList<>();
        
        for (String city : cities) {
            getName(city.toLowerCase());
        }
        return this.time;
    }
    
    private void getName(String target) {
        if (this.cacheSize == 0) {
            this.time += 5;
            return;
        }
        for (int i = 0; i < this.cacheList.size(); i++) {
            String now = this.cacheList.get(i);
            if (now.equals(target)) {
                this.cacheList.remove(i);
                this.cacheList.add(target);
                this.time++;
                return;
            }
        }
        
        if (this.cacheList.size() >= this.cacheSize) this.cacheList.remove(0);
        this.cacheList.add(target);
        this.time += 5;
    }
}
