// 1. self solve
class Solution {
    private int boundary;
    private boolean[] flag;
    private int answer;
    private int fatigue;
    
    public int solution(int k, int[][] dungeons) {
        this.boundary = dungeons.length;
        this.flag = new boolean[dungeons.length];
        this.answer = 0;
        this.fatigue = k;
        
        DFS(0, dungeons);
        return this.answer;
    }
    
    private void DFS(int depth, int[][] dungeons) {
        if (depth >= this.boundary) {
            this.answer = this.boundary;
            return;
        }
        
        for (int i = 0; i < this.boundary; i++) {
            if (this.flag[i]) continue;
            int limitFatig = dungeons[i][0];
            int useFatig = dungeons[i][1];
            if (this.fatigue < limitFatig) continue;
            this.fatigue -= useFatig;
            this.flag[i] = true;
            DFS(depth + 1, dungeons);
            this.fatigue += useFatig;
            this.flag[i] = false;
        }
        
        this.answer = Math.max(this.answer, depth);
    }
}

// 제약조건상에서 세로의 길이는 8 이하인 만큼 완전탐색을 해도 큰 영향은 없을 것으로 보임

// 2. answer


class Answer {
    public static boolean check[];
    public static int ans = 0;

    public int solution(int k, int[][] dungeons) {
        check = new boolean[dungeons.length];

        dfs(k, dungeons, 0);

        return ans;
    }
    public static void dfs(int tired, int[][] dungeons, int cnt){
        for(int i=0; i<dungeons.length; i++){
            if(!check[i] && dungeons[i][0]<=tired){
                check[i] = true;
                dfs(tired-dungeons[i][1], dungeons, cnt+1);
                check[i] = false;
            }
        }
        ans = Math.max(ans, cnt);
    }
}

// 동일한 풀이지만 fatigue(tired)를 매개변수로 전달함
