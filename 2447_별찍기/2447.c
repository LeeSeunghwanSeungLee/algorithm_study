#include <stdio.h>
#include <stdlib.h>

void draw_Star(int size);
void draw_Star_2(int size);


//동적 2차원 배열
char **m;


int main(void){//함수 완료
    int W_H;
    scanf("%d",&W_H);
    m  = malloc(sizeof(int *) * (W_H + 1);
    
    for(int i = 0; i<W_H; i++){
        m[i] = malloc(sizeof(int) * (W_H + 1);
    }

    for(int i=1; i<=W_H; i++){
        for(int j=1; j<=W_H; j++){
            m[i][j] = '*';
        }
    }

    
    //draw_Star(W_H);
    return 0;
}


void draw_Star(int size){//반복문

}

void draw_Star_2(int size){//재귀함수
    if(size/3 == 0) return; //마지막은 종료
    
    for(int i = size/3+1 ; i <= size*2/3; i++){
        for(int j = size/3+1 ; j <= size*2/3; j++){
            m[i][j] = ' ';
        }
    }
}