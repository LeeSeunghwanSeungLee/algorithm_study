#include <iostream>

using namespace std;


//전역변수
long long dp[1000001] = {0, 1, 2,};

int main(void){
    int len;
    cin >> len;
    if(len <= 2){
        cout << dp[len] << endl;
    }
    else{
        for(int i = 3; i <= len; i++){
            dp[i] = (dp[i-1] + dp[i-2]) % 15746;
        }
        cout << dp[len] << endl;
    }
    
    return 0;
}