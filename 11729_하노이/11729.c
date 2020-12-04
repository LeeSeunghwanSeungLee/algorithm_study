#include <stdio.h>
#include <math.h>
//전역변수
int num_tray;
int cnt = 0;
int A = 1; // 하노이의 탑 번호..
int B = 2;
int C = 3;
//함수
void pre_Process(){
    scanf("%d",&num_tray);
    printf("%d\n", pow(2,num_tray)-1);
}

//점화식은 a(n) = 2*a(n - 1) + 1 인것 알겠음
//print하는방법은 뭘까..

void act_Hanoi(int from, int middle, int to, int height){
    cnt++;
    if (height == 1) {
        printf("%d %d\n", from, to); 
        return;
    }
    act_Hanoi(from, to, middle,height - 1);
    act_Hanoi(from, middle, to, 1);
    act_Hanoi(middle, from, to, height - 1);
}  


int main(void){
    pre_Process();// 입력
    act_Hanoi(1,2,3,num_tray);

    return 0;
}