#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//전역변수
int len;
vector<pair<int,int>> ans;

//bool
bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.second != b.second){
        return a.second < b.second;
    }
    else{
        return a.first < b.first;
    }
}

int main(void){
    cin >> len;
    for(int i = 0; i < len; i++){
        int temp_x, temp_y;
        pair<int, int> temp_p;
        cin >> temp_x >> temp_y;
        temp_p.first = temp_x;
        temp_p.second = temp_y;
        ans.push_back(temp_p);
    }

    sort(ans.begin(), ans.end(), cmp);
    
    for(int i = 0; i < len; i++){
        cout << ans[i].first << ' ' << ans[i].second<<'\n';
    }

    return 0;
}