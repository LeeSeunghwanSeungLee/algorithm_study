#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 987654321
using namespace std;

int N, M;
int GRAPH[10][10];
bool CHECK[10][10];
int CONTINENT_DIST[11][11];
int ANS(MAX);
int tmp_ans(0);
int FLAG(1);
int d_r[] = { -1, 0, 1, 0 };
int d_c[] = { 0, 1, 0, -1 };
vector<pair<pair<int, int>, int>> DFS_LIST;
vector<bool> DFS_LIST_CHECK;
vector<int> PARENTS;

bool final_check(){
    for(int i = 1; i <= FLAG; i++){
        if(PARENTS[i] != 1) return false;
    }
    return true;
}
void BFS(int row, int col, int num) {
    CHECK[row][col] = true;
    queue<pair<int, int>> tmp;
    tmp.push(make_pair(row, col));
    while (!tmp.empty()) {
        int now_row = tmp.front().first;
        int now_col = tmp.front().second;
        GRAPH[now_row][now_col] = num;
        tmp.pop();
        for (int i = 0; i < 4; i++) {
            int next_row = now_row + d_r[i];
            int next_col = now_col + d_c[i];
            if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= M) continue;
            if (CHECK[next_row][next_col] == true) continue;
            if (GRAPH[next_row][next_col] != 1) continue;
            tmp.push(make_pair(next_row, next_col));
            CHECK[next_row][next_col] = true;
        }
    }
}

void DFS(int depth) {

    if(depth >= FLAG - 1){
        if(final_check()){
            ANS = min(ANS, tmp_ans);
            return;
        }
    }
    for(int i = 0; i < DFS_LIST.size(); i++){
        if(DFS_LIST_CHECK[i] == false){
            DFS_LIST_CHECK[i] = true;
            tmp_ans += DFS_LIST[i].second;
            int minimum = min(DFS_LIST[i].first.first, DFS_LIST[i].first.second);
            int rear_1 = PARENTS[DFS_LIST[i].first.first];
            int rear_2 = PARENTS[DFS_LIST[i].first.second]; 
            PARENTS[DFS_LIST[i].first.first] = min(minimum, PARENTS[DFS_LIST[i].first.first]);
            PARENTS[DFS_LIST[i].first.second] = min(minimum, PARENTS[DFS_LIST[i].first.second]);
            DFS(depth + 1);
            DFS_LIST_CHECK[i] = false;
            tmp_ans -= DFS_LIST[i].second;
            PARENTS[DFS_LIST[i].first.first] = rear_1;
            PARENTS[DFS_LIST[i].first.second] = rear_2;
        }
    }
}

void init() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    int area(0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> GRAPH[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (GRAPH[i][j] == 1 && CHECK[i][j] == false) {
                BFS(i, j, FLAG);
                FLAG++;
            }
        }
    }
    FLAG--;
    for (int i = 0; i <= FLAG; i++) {
        PARENTS.push_back(MAX);
    }
    memset(CONTINENT_DIST, -1, sizeof(CONTINENT_DIST));
}

void calc_bridge() {
    for (int row = 0; row < N; row++) { //가로
        vector<pair<int, int>> tmp_li;
        for (int col = 0; col < M; col++) {
            if (GRAPH[row][col] != 0) {
                tmp_li.push_back(make_pair(GRAPH[row][col], col));
            }
        }
        if (tmp_li.size() <= 1) continue;
        for (int i = 0; i < tmp_li.size() - 1; i++) {
            if (tmp_li[i].first != tmp_li[i + 1].first && tmp_li[1 + i].second - tmp_li[i].second - 1 > 1) {
                if (CONTINENT_DIST[GRAPH[row][tmp_li[i].second]][GRAPH[row][tmp_li[i + 1].second]] == -1) {
                    CONTINENT_DIST[GRAPH[row][tmp_li[i].second]][GRAPH[row][tmp_li[i + 1].second]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                    CONTINENT_DIST[GRAPH[row][tmp_li[i + 1].second]][GRAPH[row][tmp_li[i].second]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                }
                else {
                    if (CONTINENT_DIST[GRAPH[row][tmp_li[i].second]][GRAPH[row][tmp_li[i + 1].second]] > tmp_li[1 + i].second - tmp_li[i].second - 1) {
                        CONTINENT_DIST[GRAPH[row][tmp_li[i].second]][GRAPH[row][tmp_li[i + 1].second]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                        CONTINENT_DIST[GRAPH[row][tmp_li[i + 1].second]][GRAPH[row][tmp_li[i].second]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                    }
                }

            }
        }
    }

    for (int col = 0; col < M; col++) { // 세로
        vector<pair<int, int>> tmp_li;
        for (int row = 0; row < N; row++) {
            if (GRAPH[row][col] != 0) {
                tmp_li.push_back(make_pair(GRAPH[row][col], row));
            }
        }

        if (tmp_li.size() <= 1) continue;
        for (int i = 0; i < tmp_li.size() - 1; i++) {
            if (tmp_li[i].first != tmp_li[i + 1].first && tmp_li[1 + i].second - tmp_li[i].second - 1 > 1) {
                if (CONTINENT_DIST[GRAPH[tmp_li[i].second][col]][GRAPH[tmp_li[i + 1].second][col]] == -1) {
                    CONTINENT_DIST[GRAPH[tmp_li[i].second][col]][GRAPH[tmp_li[i + 1].second][col]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                    CONTINENT_DIST[GRAPH[tmp_li[i + 1].second][col]][GRAPH[tmp_li[i].second][col]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                }
                else {
                    if (CONTINENT_DIST[GRAPH[tmp_li[i].second][col]][GRAPH[tmp_li[i + 1].second][col]] > tmp_li[1 + i].second - tmp_li[i].second - 1) {
                        CONTINENT_DIST[GRAPH[tmp_li[i].second][col]][GRAPH[tmp_li[i + 1].second][col]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                        CONTINENT_DIST[GRAPH[tmp_li[i + 1].second][col]][GRAPH[tmp_li[i].second][col]] = tmp_li[1 + i].second - tmp_li[i].second - 1;
                    }
                }

            }
        }
    }

    for(int row = 1; row <= FLAG; row++){
        for(int col = row + 1; col <= FLAG; col++){
            if(CONTINENT_DIST[row][col] == -1) continue;
            DFS_LIST.push_back(make_pair(make_pair(row, col), CONTINENT_DIST[row][col]));
            DFS_LIST_CHECK.push_back(false);
        }
    }
}
int main(void) {
    init();
    calc_bridge();
    DFS(0);
    if(ANS == MAX){
        cout << -1;
        return 0;
    }
    cout << ANS;

    return 0;
}