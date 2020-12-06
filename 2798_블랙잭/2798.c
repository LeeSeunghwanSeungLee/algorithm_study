#include <stdio.h>

//전역변수
int N, M;
int card[101] = {0,};


void pre_Process(){
    scanf("%d",&N);
    scanf("%d",&M);
    for(int i = 0; i < N ; i++){
        scanf("%d" , card + i);
    }
}

void act_BruteForce(){ // 절댓값 헤더파일 찾기!! in action!!!
    int min_sum = 2147483646;
    int temp_sum;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if ( j == i) continue;
            for(int k = 0; k < N ; k++){
                if( k == i || k == j) continue;
                    temp_sum = card[i] + card[j] + card[k];
                    if (abs(M - temp_sum) < min_sum) min_sum = abs(M - temp_sum);
            }
        }
    }
    printf("%d", min_sum);
}

int main(void){
    pre_Process();
    //act_BruteForce();
}