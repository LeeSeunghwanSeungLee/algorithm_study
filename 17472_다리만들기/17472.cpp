#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
int GRAPH[10][10];
bool CHECK[10][10];
int CONTINENT_DIST[7][7];
int ANS(0);
int FLAG(1);
int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};
vector<bool> FLAG_CHECK;
vector<int> CALC_LIST;

void BFS(int row, int col, int num){
    CHECK[row][col] = true;
    queue<pair<int, int>> tmp;
    tmp.push(make_pair(row, col));
    while(!tmp.empty()){
        int now_row = tmp.front().first;
        int now_col = tmp.front().second;
        GRAPH[now_row][now_col] = num;
        tmp.pop();
        for(int i = 0; i < 4; i++){
            int next_row = now_row + d_r[i];
            int next_col = now_col + d_c[i];
            if(next_row < 0 || next_row >= N || next_col < 0 || next_col >= M) continue;
            if(CHECK[next_row][next_col] == true) continue;
            if(GRAPH[next_row][next_col] != 1) continue;
            tmp.push(make_pair(next_row, next_col));
            CHECK[next_row][next_col] = true;
        }
    }
}

void DFS(int depth){
    if(depth >= FLAG - 1){
        int final;
        for(int i = 1; i <= FLAG; i++){
            if(FLAG_CHECK[i] == false) final = i;
        }
        for(int j = 1; j <= FLAG; j++){
            int final_2 = j;
        }
        //여기서부터 연산
        return;
    }
    for(int i = 1; i <= FLAG; i++){
        if(FLAG_CHECK[i] == false){
            FLAG_CHECK[i] = true;
            CALC_LIST.push_back(i);
            DFS(depth + 1);
            FLAG_CHECK[i] = false;
            CALC_LIST.pop_back();
        }
    }
}

void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    int area(0);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> GRAPH[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(GRAPH[i][j] == 1 && CHECK[i][j] == false){
                BFS(i, j, FLAG);
                FLAG++;
            }
        }
    }
    FLAG--;
    for(int i = 0; i <= FLAG; i++){
        FLAG_CHECK.push_back(false);
    }
    memset(CONTINENT_DIST, -1, sizeof(CONTINENT_DIST));
}
int main(void){
    init();
   
    for(int row = 0; row < N; row++){ // 가로에서 확인
        int from(-1), to(-1);
        for(int col = 0; col < M; col++){
            if(GRAPH[row][col] != 0){
                //if 둘다 -1 이면 from 에 저장 컨티뉴
                //else if from만 -1 이 아니면 to 에 저장후 거리를 계산한다
                    //if 거리가 2이상이면
                        //CONTINENT[from][to] 값이 -1 이면 그대로 저장하고
                        //아니면 더 작을때만 저장한다
                if(from == -1 && to == -1){
                    from = GRAPH[row][col];
                    continue;
                }
                else if (from != -1){
                    to = GRAPH[row][col];
                    if(to - from - 1 <= 1){
                        from = -1, to = -1;
                        continue;
                    }
                    else{
                        if(CONTINENT_DIST[row][col] == -1){
                            CONTINENT_DIST[from][to] = to - from - 1;
                            CONTINENT_DIST[to][from] = to - from - 1;
                        }
                        else{
                            if(CONTINUE_DIST[from][to] <= to - from - 1) continue;
                            CONTINENT_DIST[from][to] = to - from - 1;
                            CONTINENT_DIST[to][from] = to - from - 1;
                        }
                    }
                }
            }
        }
    }

    for(int col = 0; col < M; col++){ // 세로에서 확인
        int from(-1), to(-1);
        for(int row = 0; row < N; row++){
            if(GRAPH[row][col] != 0){
                //if 둘다 -1 이면 from 에 저장 컨티뉴
                //else if from만 -1 이 아니면 to 에 저장후 거리를 계산한다
                    //if 거리가 2이상이면
                        //CONTINENT[from][to] 값이 -1 이면 그대로 저장하고
                        //아니면 더 작을때만 저장한다
            }
        }
    }

    //DFS로 최단거리를 찾는다 1 ~ FLAG 에 다가 1개만 더추가
    

    return 0;
}