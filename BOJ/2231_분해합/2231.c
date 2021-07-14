#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//전역변수
int N;
int ans;
int boundary;
int values[8] = {0,};

void pre_Process(){
    scanf("%d", &N);
}

void get_Digit(){
}

int cal_Process(int num){
    int len = -1;
    int ans = num;
    for(int i = 0; i < 8; i++){
        if(num <= 0) break;
        len = i;
        values[i] = num % 10;
        num = num / 10;
    }
    boundary = len + 1;
    for(int i = 0; i <= len; i++ ){
        ans += values[i];
    }
    return ans;
}

void main_Process(){
    int temp;
    for(int i = N - 29; i < N; i++){
        if(i <=0){
            continue;
        }
        temp = cal_Process(i);
        if(temp == N) {
            printf("%d\n", i);
            return;
        }
    }
    printf("%d\n", 0);
    return;
}
int main(void){
    pre_Process();
    main_Process();
    return 0;
}