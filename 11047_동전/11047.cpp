#include <iostream>

using namespace std;

//전역변수
int coin[11];


int main(void){
    int num, target;
    int ans(0);
    cin >>num >> target;

    for(int i = 0; i < num; i++){ // 동전을 받는다
        cin >> coin[i];
    }

    for(int i = num - 1; i > -1; i--){ // 가장 큰 값부터 계산해본다
        if(coin[i] <= target){ // 작으면
            ans += target / coin[i];
            target %= coin[i];
            if(target <= 0) break;
        }
    }
    cout << ans;


    return 0;
}