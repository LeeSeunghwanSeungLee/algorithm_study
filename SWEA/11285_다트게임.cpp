//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AXZuaLsqz9wDFAST&categoryId=AXZuaLsqz9wDFAST&categoryType=CODE
//-------------------------------문제 링크------------------------------

#include <iostream>
#include <math.h>

using namespace std;

int get_Points(int x, int y){
    float ans = sqrt(pow(x, 2) + pow(y, 2));
    if(ans <= 20.0){
        return 10;
    }
    else if(ans <= 40.0){
        return 9;
    }
    else if(ans <= 60.0){
        return 8;
    }
    else if(ans <= 80.0){
        return 7;
    }
    else if(ans <= 100.0){
        return 6;
    }
    else if(ans <= 120.0){
        return 5;
    }
    else if(ans <= 140.0){
        return 4;
    }
    else if(ans <= 160.0){
        return 3;
    }
    else if(ans <= 180.0){
        return 2;
    }
    else if(ans <= 200.0){
        return 1;
    }
    else return 0;
}
int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int test_case;
    cin >> test_case;
    for(int i = 1; i <= test_case; i++){ // i는 테스트케이스
        int number_of_arrow;
        int temp_ans(0);
        cin >> number_of_arrow;
        for(int j = 0; j < number_of_arrow; j++){
            int x, y;
            cin >> x >> y;
            //원점에서부터 거리 계산
            temp_ans += get_Points(x, y);
        }
        printf("#%d %d\n", i, temp_ans);
    }
  
    return 0;
}