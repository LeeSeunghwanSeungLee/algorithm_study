import java.util.Set;
import java.util.HashSet;

class Solution {
    private Set<Integer> numberCheck;
    private int zeroCnt;
    private int rightCnt;
    
    public int[] solution(int[] lottos, int[] win_nums) {
        
        // 0. 초기화 작업진행 
        this.numberCheck = new HashSet<>();
        this.zeroCnt = 0;
        this.rightCnt = 0;
        
        // 1. 현재 일치하는 숫자의 갯수를 확정한다.
        for(int i = 0; i < win_nums.length; i++)
            this.numberCheck.add(win_nums[i]);
        
        // 2. 공백체크, 맞춘녀석 체크
        for(int i = 0; i < lottos.length; i++){
            if(lottos[i] == 0){
                this.zeroCnt++;
            }
            
            else if(this.numberCheck.contains(lottos[i])){
                this.rightCnt++;
            }
        }
            

        int[] answer = new int[2];
        answer[0] = Math.min(6, 7 - (this.rightCnt + this.zeroCnt));
        answer[1] = Math.min(6, 7 - this.rightCnt);
        return answer;
    }    
}
