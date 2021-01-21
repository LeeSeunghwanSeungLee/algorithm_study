#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
#include <queue>

#define MAX 20
using namespace std;

struct SHARK{
    int row;
    int col;
    int cnt;
    int size;
};
int GRAPH[MAX][MAX];
int VISITED[MAX][MAX];
SHARK BABY;
int SIZE;
vector<tuple<int, int, int>> EAT_LIST;
int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};
int ANS(0);
void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> SIZE;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            cin >> GRAPH[i][j];
            if(GRAPH[i][j] == 9){ 
                GRAPH[i][j] = 0;
                BABY.row = i; BABY.col = j; BABY.cnt = 0; BABY.size = 2;
            }
        }
    }
}

void BFS(){
    int init_row = BABY.row;
    int init_col = BABY.col;
    int init_size = BABY.size;
    queue<pair<int, int>> q;
    q.push(make_pair(init_row, init_col));
    VISITED[init_row][init_col] = 1;
    while(!q.empty()){
        int now_row = q.front().first;
        int now_col = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int next_row = now_row + d_r[i]; int next_col = now_col + d_c[i];
            if(next_row < 0 || next_row >= SIZE || next_col < 0 || next_col >= SIZE) continue;
            if(GRAPH[next_row][next_col] > init_size) continue;
            if(VISITED[next_row][next_col] != 0) continue;
            q.push(make_pair(next_row, next_col));
            VISITED[next_row][next_col] = VISITED[now_row][now_col] + 1;
            if(GRAPH[next_row][next_col] != 0 && GRAPH[next_row][next_col] != init_size){
                EAT_LIST.push_back(make_tuple(VISITED[next_row][next_col], next_row, next_col));
            }
        }
    }
}


int main(void){
    init();


    while(1){
        EAT_LIST.clear();
        memset(VISITED, 0, sizeof(VISITED));
        BFS();
        if(EAT_LIST.size() == 0){
            cout << ANS;
            break;
        }
        else{
            sort(EAT_LIST.begin(), EAT_LIST.end());
            BABY.row = get<1>(EAT_LIST[0]); BABY.col = get<2>(EAT_LIST[0]);
            ANS += get<0>(EAT_LIST[0]) - 1;
            GRAPH[BABY.row][BABY.col] = 0;
            BABY.cnt++;
            if(BABY.cnt == BABY.size){
                BABY.size++;
                BABY.cnt = 0;
            }
        }
    }
    return 0;
}