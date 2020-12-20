#include <iostream>
#include <vector>


using namespace std;

//전역변수
long long dp[10001][4];
vector<long long> gls_q;


//비교 함수
long long comp(long long a, long long b, long long c){
    if(a>b){
        if(a > c) return a;
        else return c;
    }
    else{ // a <= b
        if(c > b) return c;
        else return b;
    }
}
int main(void){
    int gls;
    cin >> gls;

    for(int i = 0; i < gls; i++){ // 포도주의 양을 받아온다
        long long temp;
        cin >> temp;
        gls_q.push_back(temp);
    }
    //첫잔의경우
    dp[0][0] = 0; // 안마시는경우
    dp[0][1] = gls_q[0]; // 한잔 여유있게 마심
    dp[0][2] = gls_q[0]; // 2잔을 마셔서 다음번에는 마실 수 없다
     
    //두잔의경우
    dp[1][0] = dp[0][2]; // 안 마시는 경우
    dp[1][1] = dp[0][0] + gls_q[1]; // 지난번에 안 마셔서 한잔 마시는 경우
    dp[1][2] = dp[0][1] + gls_q[1]; // 지난 번에 한잔 마셧고, 이번에 다 마시는 경우 다음번에 못 마심


    if(gls > 2){
        for(int i = 2; i < gls; i++){
            dp[i][0] = dp[i - 1][2];
            dp[i][1] = dp[i - 1][0] + gls_q[i];
            dp[i][2] = dp[i - 1][1] + gls_q[i];
        }
    }

    cout << comp(dp[gls - 1][0],dp[gls - 1][1], dp[gls - 1][2]); 
    return 0;
}


//반례 1 : 2번건너뛰는경우가 있을수도있네.. fuck that!!