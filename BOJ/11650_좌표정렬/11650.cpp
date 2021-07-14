#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>


using namespace std;

//전역변수
int len;
vector<pair<int,int>> ans;


//bool
bool cmp (pair<int, int> a, pair<int, int> b){ //포인터 사용필요 x 
    if(a.first != b.first){
        return a.first <= b.first;
    }
    else{
        return a.second <= b.second;
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
        cout<<ans[i].first<<' '<<ans[i].second<<'\n';
    }

    return 0;
}