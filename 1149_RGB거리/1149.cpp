#include <iostream>



using namespace std;
//전역변수
int** template_arr;

int main(void){
    int size;
    cin >> size;


    template_arr = new int*[size]; // 동적으로 배열 생성
    for(int i = 0; i < size; i++){
        template_arr[i] = new int[3];
    }

    for(int i = 0; i < size; i++){ // 변수 담기
        for(int j = 0; j < 3; j++){
            cin >> template_arr[i][j];
        }
    }

    //연산
    int dp[size] = {0,}; // 동적 프로그래밍
    







    return 0;
}