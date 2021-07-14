#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// 전역변수
vector<int> ans;
vector<pair<int, int>> lists; // 순열 좌표 3개 찾기
vector<bool> check;
int _map[9][9];
int _tray[9][9]; // 매번 확인차 복사 붙여넣기 할 공간
int N, M;
queue<pair<int, int>> virus;

vector<int> temp;
int d_row[] = {-1, 0, 1, 0};
int d_col[] = {0, 1, 0, -1};

void BFS(){
    int temp_ans = 0;
    for(int i = 0; i < N; i++){ // 전부 담는다
        for(int j = 0; j < M; j++){
            if(_tray[i][j] == 2){
                virus.push(make_pair(i, j));
            }
        }
    }

    while(!virus.empty()){
        pair<int, int> now = virus.front();
        virus.pop();
        for(int i = 0; i < 4; i++){
            int new_row = now.first + d_row[i];
            int new_col = now.second + d_col[i];
            if(new_row >= 0 && new_row < N  && new_col >= 0 && new_col < M){
                if(_tray[new_row][new_col] == 0){
                    _tray[new_row][new_col] = 2;
                    virus.push(make_pair(new_row, new_col));
                }
            }
        }
    }

    //확인
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(_tray[i][j] == 0){
                temp_ans++;
            }
        }
    }
    ans.push_back(temp_ans);
}

void DFS(int depth, int initial_number){
    if(depth >= 3){//BFS계산하기
        // BFS();
        copy(&_map[0][0], &_map[0][0] + 9 * 9, &_tray[0][0]);
        for(int i = 0; i < temp.size(); i++){
            _tray[lists[temp[i]].first][lists[temp[i]].second] = 1;
        }
        BFS();
        return;
    }

    
    for(int i = initial_number; i < lists.size(); i++){
        if(depth == 0){
            for(int i = 0; i < check.size(); i++){
                check[i] = false;
            }
         }
        if(check[i] != true){
            check[i] = true;
            temp.push_back(i);
            DFS(depth + 1, i);
            check[i] = false;
            temp.pop_back();
        }
    }
}

int main(void){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> _map[i][j];
            _tray[i][j] = _map[i][j];
            if(_tray[i][j] == 0){
                lists.push_back(make_pair(i, j));
                check.push_back(false);
            }
        }
    }
    // 3개좌표를... 조합(DFS활용) 으로 좌표 계산..
    //BFS();
    DFS(0, 0);
    sort(ans.begin(), ans.end());
    cout << ans[ans.size() - 1];
    return 0;
}