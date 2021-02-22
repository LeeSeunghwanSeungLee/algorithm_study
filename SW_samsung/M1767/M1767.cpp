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
vector<pair<int, int>> PROCESSOR_LIST;
int ANS(MAX);
int tmp_ans(0);

int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};
void DFS(int depth){
    if(depth >= PROCESSOR_LIST.size()){
        ANS = min(ANS, tmp_ans);
        return;
    }

    if(CHECK[PROCESSOR_LIST[depth].first][PROCESSOR_LIST[depth].second] == true) return;
    if(PROCESSOR_LIST[depth].first == 0 || PROCESSOR_LIST[depth].first == SIZE - 1 || PROCESSOR_LIST[depth].second == 0 || PROCESSOR_LIST[depth].second == SIZE - 1) {
        CHECK[PROCESSOR_LIST[depth].first][PROCESSOR_LIST[depth].second] = true;
        DFS(depth + 1);
        CHECK[PROCESSOR_LIST[depth].first][PROCESSOR_LIST[depth].second] = false;
        return;
    }
    for(int i = 0; i < 4; i++){
        int start_row = PROCESSOR_LIST[depth].first;
        int start_col = PROCESSOR_LIST[depth].second;
        int next_row(start_row);
        int next_col(start_col);
        bool flag = false;

        while(next_row != 0 || next_row != SIZE - 1 || next_col != 0 || next_col != SIZE - 1){
            next_row += d_r[i], next_col += d_c[i];
            if(CHECK[next_row][next_col] == true) {
                flag = true;
                break;
            }
        }
        if(flag) continue;
        int len(-1);
        next_row = start_row;
        next_col = start_col;
        while(next_row >= 0 && next_row <= SIZE - 1 && next_col >= 0 && next_col <= SIZE - 1){
            CHECK[next_row][next_col] = true;
            next_row += d_r[i], next_col += d_c[i];
            len++;
        }
        tmp_ans += len;
        DFS(depth + 1);
        tmp_ans -= len;
        next_row = start_row;
        next_col = start_col;
        while(next_row >= 0 && next_row <= SIZE - 1 && next_col >= 0 && next_col <= SIZE - 1){
            CHECK[next_row][next_col] = false;
            next_row += d_r[i], next_col += d_c[i];
        }
    }   
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> TEST_CASE;
    for(int tc = 1; tc <= TEST_CASE; tc++){
        
        cin >> SIZE;

        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                cin >> GRAPH[i][j];
                if(GRAPH[i][j] == 1) PROCESSOR_LIST.push_back(make_pair(i, j));
            }
        }
        DFS(0);
        cout << '#' << tc << ' ' << ANS << '\n';
    }

    return 0;
}