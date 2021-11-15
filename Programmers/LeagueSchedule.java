// 1. xor 
class Solution1
{
    public int solution(int n, int a, int b)
    {
        return Integer.toBinaryString((a-1)^(b-1)).length();
    }
}

// 2. idea

class Solution2
{
    public int solution(int n, int a, int b)
    {
        a = a - 1;
        b = b - 1;
        
        int answer = 1;
        while (true) {
            if(Math.abs(a - b) == 1 && Math.min(a, b) % 2 == 0) break;
            a = a / 2;
            b = b / 2;
            answer++;
        }
        
        return answer;
    }
}
