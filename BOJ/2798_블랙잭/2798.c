#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//printf는??

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

void act_BruteForce(){ 
    int min_sum = 2147483646;
    int temp_sum;
    int distance = 2147483646;
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            if ( j == i) continue;
            for(int k = j; k < N ; k++){
                if( k == i || k == j) continue;
                    temp_sum = card[i] + card[j] + card[k];
                    if(temp_sum > M) continue;
                    if (abs(M - temp_sum) <=  distance){
                        min_sum = temp_sum;
                        distance =  abs(M - temp_sum);                    
                    }
            }
        }
    }
    printf("%d\n", min_sum);
}

int main(void){
    pre_Process();
    act_BruteForce();
}