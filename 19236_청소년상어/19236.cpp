// https://www.acmicpc.net/problem/19236
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
struct FISH{
    bool is_fish  = true;
    int row;
    int col;
    int self_points;
    int dir;
};
struct SHARK{
    int row;
    int col;
    int points;
    int dir;
};
FISH GRAPH[4][4][17];
vector<SHARK> CHECK_SHARK;
vector<int> ANS;
int d_r[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int d_c[] = {0, -1, -1, -1, 0, 1, 1, 1};

bool cmp(FISH &a, FISH &b){
    return a.self_points < b.self_points;
}

void swap(int row, int col, int depth, int dir){
    int new_dir = dir;
    int target_row = row + d_r[new_dir];
    int target_col = col + d_c[new_dir];
    
    //만일 벽에 나가거나 상어의 위치와 동일하면 new_dir = (new_dir + 1) % 8 을 적용
    //꾸준히 회전했는대 new_dir == dir 가되면 이동 불가 //  그대로 그래프에 저장하고, return;

    GRAPH[target_row][target_col][depth + 1] = GRAPH[row][col][depth];
    GRAPH[row][col][depth + 1] = GRAPH[target_row][target_col][depth];
}

void DFS(int depth){
    if(depth >= 16){
        sort(ANS.begin(), ANS.end());
        cout << ANS[ANS.size() - 1];
        return;
    }

    vector<FISH> temp_fish;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(GRAPH[i][j][depth].is_fish == true){
                temp_fish.push_back(GRAPH[i][j][depth]);
            }
        }
    }
    sort(temp_fish.begin(), temp_fish.end(), cmp);
    for(int i = 0; i < temp_fish.size(); i++){
        int now_row = temp_fish[i].row, now_col = temp_fish[i].col, now_dir = temp_fish[i].dir;
        swap(now_row, now_col, depth,  now_dir);
    }


    //상어의 방향에 맞춰서 가능한 방향으로 DFS 시킨다.
        //빈칸이거나 밖으로 나가면 컨티뉴
        //상어의 포인트를 더한다
        //현재 상어의 상태를 벡터에 저장한다
        //DFS(depth + 1)
        //벡터에서 현재 상어의 상태를 퇴출시킨다
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int tmp_point, tmp_dir;
            cin >> tmp_point >> tmp_dir;
            GRAPH[i][j][0].row = i, GRAPH[i][j][0].col = j, GRAPH[i][j][0].self_points = tmp_point, GRAPH[i][j][0].dir = tmp_dir;
        }
    }

    //샤크의 현재 위치 (0, 0) 와 점수(0) 을 저장한다

    // DFS 를 진행한다?
}