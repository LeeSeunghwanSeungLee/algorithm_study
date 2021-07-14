#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//전역변수
vector<pair<long long, long long>> dp;
vector<long long> stair;

//함수

long long find_max(long long a, long long b) {
    if (a > b) return a;
    return b;
}
long long find_max(long long a, long long b, long long c) {
    long long ans;
    if (a > b) {
        if (a > c) return a;
        else return c;
    }
    else { // a <= b
        if (b < c) return c;
        else return b;
    }
}

int main(void) {
    int layer;
    cin >> layer;
    for (int i = 0; i < layer; i++) { // 계단 점수를 쌓는다
        long long temp;
        cin >> temp;
        stair.push_back(temp);
    }
    //첫번째 계단
    pair<long long, long long> temp_p;
    temp_p.first = 0;
    temp_p.second = stair[0];
    dp.push_back(temp_p);
    //두번째 계단
    if (layer > 1) {
        temp_p.first = stair[1] + find_max(dp[0].second, dp[0].first);
        temp_p.second = stair[1]; // + find_max(dp[-1].first, dp[-1].second)
        dp.push_back(temp_p);
    }
    if (layer > 2) {
        for (int i = 2; i < layer; i++) {
            temp_p.first = stair[i] + dp[i - 1].second;
            temp_p.second = stair[i] + find_max(dp[i - 2].first, dp[i - 2].second);
            dp.push_back(temp_p);
        }
    }
    
    cout << find_max(dp[layer - 1].first, dp[layer - 1].second);

   
    return 0;
}