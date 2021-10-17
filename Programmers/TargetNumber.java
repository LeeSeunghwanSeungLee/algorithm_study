class Solution {
    public int target;
    public int leafDepth;
    public int answer;
    
    public int solution(int[] numbers, int target) {
        this.target = target;
        this.leafDepth = numbers.length;
        this.answer = 0;
        
        dfs(0, 0, 0, numbers);
        dfs(0, 0, 1, numbers);
        
        return this.answer / 2;
    }
    
    private void dfs(int depth, int totalNum, int calculate, int[] numbers){
        if(depth == this.leafDepth){
            if(this.target == totalNum) this.answer++;
            return;
        }
        
        if(calculate == 0)
            totalNum += numbers[depth];
        
        else if(calculate == 1)
            totalNum -= numbers[depth];
        
        for(int i = 0; i < 2; i++){
            dfs(depth + 1, totalNum, i, numbers);
        }
    }
}

// 1. this.leafDepth 필요없음
// 2. flag를 사용하지 않은 관계로 최종 답이 2번 더해짐 (임시로 this.answer / 2 로 선언해서 제출했으나, 탈출 플래그만 세우면 연산 절반 줄일 수 있음)
