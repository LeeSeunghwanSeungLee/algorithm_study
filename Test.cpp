#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define MAX 987654321

using namespace std;

int TEST_CASE;
int SIZE;
int GRAPH[13][13];
bool CHECK[13][13];
vector<pair<int, int>> PC_LIST;
int PC_NUM(0);
int ANS(MAX);
int tmp_ans(0);
int d_r[4] = {0, 0, 0, 0}; // 0, 자기자신, SIZE -1, 자기자신
int d_c[4] = {0, 0, 0, 0}; // 자기자신, SIZE - 1, 자기자신, 0, 

void DFS(int depth, int pc_number){
    if(depth >= PC_LIST.size()){
        if(pc_number > PC_NUM){
            PC_NUM = pc_number;
            ANS = tmp_ans;
        }
        else if(pc_number == PC_NUM){
            ANS = min(ANS, tmp_ans);
        }
        return;
    }

    int now_row = d_r[1] = d_r[3] = PC_LIST[depth].first;
    int now_col = d_c[0] = d_c[2] = PC_LIST[depth].second;

    for(int dir = 0; dir < 4; dir++){
        int start_p, end_p;
        bool flag = false;
        if(dir % 2 == 0){
            start_p = min(now_row, d_r[dir]);
            end_p = max(now_row, d_r[dir]);
            for(int t = start_p + 1; t <= end_p; t++){
                if(CHECK[t][now_col] == true){
                    flag = true;
                    break;
                }
            }
        }
        else{
            start_p = min(now_col, d_c[dir]);
            end_p = max(now_col, d_c[dir]);
            for(int t = start_p + 1; t <= end_p; t++){
                if(CHECK[now_row][t] == true){
                    flag = true;
                    break;
                }
            }
        }
        if(flag){
            DFS(depth + 1, pc_number);
            continue;
        }
        
        //아래는 가능하다는 의미가된다
        //전부 체크 한다
        if(dir % 2 == 0){
            start_p = min(now_row, d_r[dir]);
            end_p = max(now_row, d_r[dir]);
            for(int t = start_p + 1; t <= end_p; t++) CHECK[t][now_col] = true;
        }
        else{
            start_p = min(now_col, d_c[dir]);
            end_p = max(now_col, d_c[dir]);
            for(int t = start_p + 1; t <= end_p; t++) CHECK[now_row][t] = true;
        }
        //해당 길이만큼 예시 답에 더한다
        tmp_ans += (end_p - start_p);
        DFS(depth + 1, ++pc_number);
        //전부 체크 해제한다
        if(dir % 2 == 0){
            start_p = min(now_row, d_r[dir]);
            end_p = max(now_row, d_r[dir]);
            for(int t = start_p + 1; t <= end_p; t++) CHECK[t][now_col] = false;
        }
        else{
            start_p = min(now_col, d_c[dir]);
            end_p = max(now_col, d_c[dir]);
            for(int t = start_p + 1; t <= end_p; t++) CHECK[now_row][t] = false;
        }
        //해당 길이만큼 예시 답에서 뺸다
        tmp_ans -= (end_p - start_p);
    }
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> TEST_CASE;
    for(int tc = 1; tc <= TEST_CASE; tc++){
        
        cin >> SIZE;
        d_r[2] = SIZE - 1;
        d_c[1] = SIZE - 1;
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                cin >> GRAPH[i][j];
                if(GRAPH[i][j] == 1) {
                    CHECK[i][j] = true;
                    if(i != 0 && i != SIZE - 1 && j != 0 && j!= SIZE - 1) PC_LIST.push_back(make_pair(i, j));
                }
            }
        }
        DFS(0, 0);
        소팅한다
        cout << '#' << tc << ' ' << ANS << '\n';
    }
    return;
}