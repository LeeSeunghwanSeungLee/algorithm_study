#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
//전역변수
vector<pair<int, int>> counsel;
int DAY;
vector<int> ans;
int temp_ans(0);

void pre_action(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> DAY;
    for(int i = 0; i <= DAY; i++){ // 초기화
        counsel.push_back(make_pair(0, 0));
    }
    for(int i = 1; i <= DAY; i++){ // 입력
        cin >> counsel[i].first >> counsel[i].second;
    }
}

void DFS(int day){
    int next_day = day + counsel[day].first;
    if(next_day > DAY + 1){
        ans.push_back(temp_ans);
        return;
    }
    //해당일 상담
    temp_ans += counsel[day].second;
    if(next_day == DAY + 1){
        ans.push_back(temp_ans);
        temp_ans -= counsel[day].second;
        return;
    }
    for(int i = next_day; i <= DAY; i++){
        DFS(i);
    }
    temp_ans -= counsel[day].second;
}

int main(void){
    pre_action();
    for(int i = 1; i <= DAY; i++){
        temp_ans = 0;//초기화
        DFS(i);
    }
    sort(ans.begin(), ans.end());
    cout << ans[ans.size() - 1];
    return 0;
}