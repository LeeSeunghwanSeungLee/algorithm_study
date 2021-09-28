import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class TernaryFlip {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);

        SolutionTenaryFlip s = new SolutionTenaryFlip();
        int res = s.solution(input.nextInt());

        System.out.println("res : " + res);
        input.close();
    }
}

class SolutionTenaryFlip {
    public  int solution(int num){
        List<Integer> list = new ArrayList<Integer>();

        while(num > 0){
            list.add(num % 3);
            num /= 3;
        }

        int answer = 0;
        int j = 0;
        for(int i = list.size() - 1; i >= 0; i--) answer += list.get(i) * Math.pow(3, j++);

        return answer;
    }
}

// 배운점 
// 1. 중복디렉토리(패키지) 에 같은 클래스 이름이 존재하면 NoSuchMethodError가 발생한다