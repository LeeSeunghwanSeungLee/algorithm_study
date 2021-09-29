public class ExpressByN{
    public static void main(String[] args) {

    }
}

class Solution {
    private int n;
    private int target;
    private int answer = Integer.MAX_VALUE;

    public int solution(int N, int number){

        // constructor
        this.n = N;
        this.target = number;

        // logic
        dfs(0, 0);
        return this.answer == Integer.MAX_VALUE ? -1 : answer;
    }

    private void dfs(int count, int prev){

        if(count > 8){ 
            this.answer = -1;
            return;
        }

        if(prev == this.target){
            answer = Math.min(answer, count);
            return;
        }

        int aTempNumber = this.n;
        for (int i = 0; i < 8 - count; i++){
            int newCount = count + i + 1;
            dfs(newCount, prev + aTempNumber);
            dfs(newCount, prev - aTempNumber);
            dfs(newCount, prev / aTempNumber);
            dfs(newCount, prev * aTempNumber);

            aTempNumber = aTempNumber * 10 + this.n;
        }
    }
}