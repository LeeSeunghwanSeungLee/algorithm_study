#include <stdio.h>



int get_Factorial(int num){
    //재귀함수로 factorial 구현한다
    if(num == 0) return 1;
    if(num == 1) {
        return num;
    }
  
    return num * get_Factorial(num - 1);
}


int main(void){
    //변수 선언
    int goal;
    int answer;
    //숫자를 받는다
    scanf("%d",&goal);

    //함수 실행
    answer = get_Factorial(goal);
    printf("%d",answer);
    return 0;
}