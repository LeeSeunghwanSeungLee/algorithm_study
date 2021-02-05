#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

//------전역-------
int N, M, D;
int GRAPH[15][15];
int tmp_graph[15][15];
bool CHECK[15][15];
int ANS;
vector<int> ARCHOR;
vector<pair<int, int>> TARGET;
queue<pair<int, int>> tmp_target;
bool ARCHOR_CHECK[5];
int d_r[] = {0, -1, 0};
int d_c[] = {-1, 0, 1};
//------함수-------
void copy(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            tmp_graph[i][j] = GRAPH[i][j];
        }
    }
}
void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> D;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> GRAPH[i][j];
        }
    }
}
bool check_empty(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(tmp_graph[i][j] == 1) return false;
        }
    }
    return true;
}
int simulate(){
    int tmp_ans(0);
    while(1){
        TARGET.clear();
        for(int archor = 0; archor < 3; archor++){
            memset(CHECK, 0, sizeof(CHECK));
            pair<int, int> start = make_pair(N - 1, ARCHOR[archor]);
            int distance = 1;
            if(tmp_graph[start.first][start.second] == 1) {
                TARGET.push_back(start);
                continue;
            }
            else tmp_target.push(start);
            CHECK[start.first][start.second] = true;
            while(!tmp_target.empty()){
                pair<int, int> now = tmp_target.front();
                tmp_target.pop();
                distance++;
                for(int i = 0; i < 3; i++){
                    //다음위치를 선언한다
                    pair<int, int> next = make_pair(now.first + d_r[i], now.second + d_c[i]);
                    //만일 다음위치가 벽 밖이면 컨티뉴
                    if(next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;
                    //만일 다음위치가 궁수로부터 거리가 D보다 크면 컨티뉴
                    if(distance > D) continue;
                    //이미 방문했던 지점이면 컨티뉴
                    if(CHECK[next.first][next.second] == true) continue;
                    //if 다음지점의 그래프 값이 1이면 TARGET에 저장하고 다음 ARCHOR로 돌아가야함
                    if(tmp_graph[next.first][next.second] == 1){
                        TARGET.push_back(next);
                        int boundary = tmp_target.size();
                        for(int i = 0; i < boundary; i++){
                            tmp_target.pop();
                        }
                        break;
                    }
                    else{
                        tmp_target.push(next);
                        CHECK[next.first][next.second] = true;
                    }
                }
            }
        }
        cout << 's' << '\n';
        for(int kill = 0; kill < TARGET.size(); kill++){
            pair<int, int> now = TARGET[kill];
            if(tmp_graph[now.first][now.second] == 1){
                tmp_graph[now.first][now.second] = 0;
                cout << now.first << ' ' << now.second << ' ' << '\n';
                tmp_ans++;
            }
        }
        if(check_empty()) {
            return tmp_ans;
        }
        for(int row = N - 1; row >= 1; row--){
            for(int col = 0; col < M; col++){
                tmp_graph[row][col] = tmp_graph[row - 1][col];
            }
        }
        for(int col = 0; col < M; col++){
            tmp_graph[0][col] = 0;
        }
    }
}
void archor_dfs(int depth){
    if(ARCHOR.size() >= 3){
        copy();
        cout << '\n';
        ANS = max(simulate(), ANS);
        return;
    }

    if(ARCHOR.size() < 3 && depth >= 3){
        ARCHOR.clear();
        return;
    }
    int start_number;
    if(ARCHOR.size() == 0) start_number = 0;
    else start_number = ARCHOR[ARCHOR.size() - 1];
    for(int i = start_number; i < 5; i++){
        if(ARCHOR_CHECK[i] == true) continue;
        ARCHOR_CHECK[i] = true;
        ARCHOR.push_back(i);
        archor_dfs(depth + 1);
        ARCHOR_CHECK[i] = false;
        ARCHOR.pop_back();        
    }
}
//------메인-------
int main(void){
    init();
    archor_dfs(0);
    cout << ANS;
    return 0;
}