class Solution {
	
    public int solution(String name) {
        int answer = 0;
        int len = name.length();

        int min_move = len - 1;

        for(int i = 0; i < len; i++) {
            answer += Math.min(name.charAt(i)-'A', 'Z'-name.charAt(i)+1);

            int next = i + 1;// 현재 다음 위치부터

            while(next<len && name.charAt(next) == 'A')
                next++;

            min_move = Math.min(min_move, i + len - next + Math.min(i, len - next));
        }

        answer += min_move;
        return answer;
    }
}
