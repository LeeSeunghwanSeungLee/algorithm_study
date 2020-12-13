#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//전역
int len;
vector<string> ans;

//bool
bool cmp(string a, string b){
    if(a.size() == b.size()){
        return a < b;
    }
    return a.size() < b.size();
}

int main(void){
    cin >> len;
    for(int i = 0; i < len; i++){
        string temp;
        cin >> temp;
        ans.push_back(temp);
    }


    sort(ans.begin(), ans.end(), cmp);

    for(int i = 0; i < len; i++){
        if( ans[i] != ans[i + 1]){
            cout << ans[i] << '\n';
        }
        continue;
    }


    return 0;
}