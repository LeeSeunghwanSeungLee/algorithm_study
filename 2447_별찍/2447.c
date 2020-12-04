#include <stdio.h>

//전역변수
char star[7000][7000];

//함수
void act_PreProcess(int boundary){
    for (int i = 0; i < boundary; i++){
        for (int j = 0; j < boundary; j++){
            star[i][j] = '*';
        }
    }
    return;
}

void test(int boundary){
    for (int i = 0; i < boundary; i++){
        for (int j = 0; j < boundary; j++){
            printf("%c",star[i][j]);
        }
        printf("\n");
    }
    return;
}

void delete_Star(int start_row, int start_col, int size){
    if(size == 1) return;

    int new_size = size / 3;
    for (int i = start_row + new_size; i < start_row + new_size*2; i++){// delete action
        for (int j = start_col + new_size; j < start_col + new_size * 2; j++){
            star[i][j] = ' ';
        }
    }

    int cnt = 0;
    //recursion
    for (int i = start_row; i <= start_row + new_size * 2 ; i+=new_size){
        for (int j = start_col; j <= start_col + new_size * 2; j+=new_size){
            cnt++;
            if(cnt !=5){
                delete_Star(i, j, new_size);
            }   
        }

    }

}

//메인
int main(void){
    int boundary =0;
    scanf("%d", &boundary);
    act_PreProcess(boundary);
    delete_Star(0, 0, boundary);
    test(boundary);
    return 0;
}