#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<int, int>> test_case;
vector<string> ans;


int main(void){
    bool swit = true;
    while(swit){ // 테스트 케이스를 가져온다
        pair<int, int> temp;
        cin >> temp.first >> temp.second;
        if(temp.first == 0 && temp.second == 0) {
            swit = false;
            continue;
        }
        test_case.push_back(temp);
    }

    for(int i = 0; i < test_case.size(); i++){
        if(test_case[i].second % test_case[i].first == 0 && test_case[i].first < test_case[i].second){
            ans.push_back("factor");
        }
        else if(test_case[i].first % test_case[i].second == 0 && test_case[i].first > test_case[i].second){
            ans.push_back("multiple");
        }
        else ans.push_back("neither");
    }

    for(int i = 0; i < test_case.size(); i++){
        cout << ans[i] << '\n';
    }


    return 0;
}