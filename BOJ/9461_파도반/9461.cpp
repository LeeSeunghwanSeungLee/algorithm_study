#include <iostream>
#include <vector>

using namespace std;
vector<int> test_case;

long long dp[101] = {0,1,1,1,2,2,3,4,5,7,9,12,16,};

void answer(int num){


}


int main(void){
    int case_cnt;
    int max = 0;
    cin >> case_cnt;
    for(int i = 0; i < case_cnt; i++){
        int temp;
        cin >> temp;
        if(temp > max) max = temp;
        test_case.push_back(temp);
    }

    if(max > 12){
        for(int i = 13; i <= max; i++){
                dp[i] = dp[i-1] + dp[i-5]; 
        }
    }

    for(int i = 0; i < case_cnt; i++){
        cout << dp[test_case[i]]<<'\n';
    }


    return 0;
}