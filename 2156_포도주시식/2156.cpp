#include <iostream>
#include <vector>


using namespace std;

//전역변수
long long dp[10001];
long long wine[10001];


int main(void){
    int num;
    cin >> num;

    for(int i = 0; i < num; i++){ // 와인잔을 채운다
        cin >> wine[i];
    }

    //첫번째 잔
    dp[0] = wine[0];

    //두번째 잔
    dp[1] = wine[0] + wine[1];

    //세번째 잔
    dp[2] = max(max(wine[2] + wine[1] + 0, wine[2] + wine[0] + 0), 0 + wine[1] + wine[0]);

    //네번째 잔
    dp[3] = max(max(wine[3] + wine[2] + dp[0], wine[3] + dp[1]), wine[2] + wine[1]);

    for(int i = 4; i < num; i++){
        dp[i] = max( max(wine[i] + wine[i-1] + dp[i -3], wine[i] + dp[i - 2]), wine[i - 1] + wine[i - 2] + dp[i - 4]);
    }

    cout << dp[num - 1];


    return 0;
}