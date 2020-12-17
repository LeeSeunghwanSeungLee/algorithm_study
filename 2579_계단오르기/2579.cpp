#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//전역변수
vector<pair<pair<long long,long long>, long long>> dp;
vector<long long> stair;

//함수
long long find_max(long long a, long long b, long long c){
    long long ans;
    if (a > b){
        if(a > c) return a;
        else return c;
    }
    else{ // a <= b
        if(b < c) return c;
        else return b;
    }
}

int main(void){
    int layer;
    cin >> layer;
    for(int i = 0; i < layer; i++){ // 계단 점수를 쌓는다
        long long temp;
        cin >> temp;
        stair.push_back(temp);
    }

    //첫번째경우의수 layer = 0
    pair<long long, long long> temp;
    pair<pair<long long, long long>,long long> temp_two;
    temp.first = 0;
    temp.second = stair[0];
    temp_two.first= temp;
    temp_two.second = 0;
    dp.push_back(temp_two);
    if(layer > 1){
        //두번째 경우의수  layer = 1
        temp.first = stair[1] + dp[0].first.second;
        temp.second = 0;
        temp_two.first = temp;
        temp_two.second = stair[1]; //+max ( dp[-1].first.first, dp[-1].first.second, dp[-1].second);
        dp.push_back(temp_two);
    }
    if(layer > 2){
        for(int i = 2; i < layer; i++){
            temp.first = stair[i] + dp[i - 1].first.second;
            temp.second = stair[i] + dp[i - 1].second;
            temp_two.first = temp;
            temp_two.second = stair[i] + find_max( dp[i - 2].first.first, dp[i - 2].first.second, dp[i - 2].second);
            dp.push_back(temp_two);
        }
    }
    
    cout << find_max(dp[layer - 1].first.first, dp[layer - 1].first.second, dp[layer - 1].second) << '\n';
    
    return 0;
}