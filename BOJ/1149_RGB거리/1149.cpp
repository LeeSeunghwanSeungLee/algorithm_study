#include <iostream>
#include <algorithm>


using namespace std;
//전역변수
int** template_arr;
long long** dp_arr;
int main(void){
    int size;
    cin >> size;
    
    
    template_arr = new int*[size]; // 동적으로 배열 생성
    dp_arr = new long long*[size];
    for(int i = 0; i < size; i++){
        template_arr[i] = new int[3];
        dp_arr[i] = new long long[3];
    }

    for(int i = 0; i < size; i++){ // 변수 담기
        for(int j = 0; j < 3; j++){
            cin >> template_arr[i][j];
        }
    }

    for(int i = 0; i < 3; i++){
        dp_arr[0][i] = (long long)template_arr[0][i]; // 형변환
    }

    //연산
    for(int i = 1; i < size; i++){
        for(int j = 0; j < 3; j++){
            long long min = 9223372036854775807;
            for(int k = 0; k < 3; k++){
                if(k == j) continue;
                if(dp_arr[i-1][k] < min) min = dp_arr[i-1][k];
            }
            dp_arr[i][j] = template_arr[i][j] + min;
        }
    }
    
    long long ans = min(min(dp_arr[size-1][0], dp_arr[size-1][1]), dp_arr[size - 1][2]);
    cout << ans;
    





    delete[] template_arr; // 질문 더블포인터는 동적 메모리 해제 어떻게 하는지 확인하기!
    delete[] dp_arr;
    return 0;
}