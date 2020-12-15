#include <iostream>
#include <vector>


using namespace std;
//전역변수
//long long dp[41] = {0, 1,};
vector<int> test_list;
pair<int, int> dp_list[41];
// int len = 1;
//함수


// pair<int, int> fibo_check(int num){
//     if(num == 0){
//         //0 일때 증가
//         return dp_list[0];
//     }
//     if(num == 1){

//         return dp_list[1];
//     }
//     if(num <= len){
//         return dp_list[num];
//     }
//     dp_list[num] = make_pair(fibo_check(num - 2).first + fibo_check(num - 1).first, fibo_check(num - 2).second + fibo_check(num - 1).second);

//     return dp_list[num];
// }


int main(void){
    int T;
    cin >> T;
    for(int i = 0; i < T; i++){
        int temp;
        cin >> temp;
        test_list.push_back(temp);
    }

    for(int i = 0; i < 41; i++){
        if(i == 0){
            dp_list[i] = make_pair(1, 0);
            continue;
        }
        else if(i == 1){
            dp_list[i] = make_pair(0, 1);
            continue;
        }
        dp_list[i] = make_pair(dp_list[i - 2].first + dp_list[i - 1].first, dp_list[i - 2].second + dp_list[i - 1].second);
    }

    for(int i = 0; i < test_list.size(); i++){
 
        cout << dp_list[test_list[i]].first << ' ' << dp_list[test_list[i]].second << '\n';
    }
    return 0;
}