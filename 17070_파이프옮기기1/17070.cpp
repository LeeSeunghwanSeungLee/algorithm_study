#include <iostream>
using namespace std;
int SIZE;
int GRAPH[17][17];
bool DP[17][17][2]; // 추후DP를 위함임
int d_r[] = {0, 1, 1};
int d_c[] = {1, 1, 0};
int ANS(0);
void DFS(int row, int col, int dir){
    if(row == SIZE && col == SIZE){
        ANS++;
        return;
    }

    if(dir == 0){
        for(int i = 0; i < 2; i++){
            int next_row = row + d_r[i];
            int next_col = col + d_c[i];
            if(next_row < 1 || next_row > SIZE || next_col < 1 || next_col > SIZE) continue;
            if(GRAPH[next_row][next_col] == 1) continue;
            if(i == 1){
                if(GRAPH[next_row - 1][next_col] == 1 || GRAPH[next_row][next_col - 1] == 1) continue;
            }
            DFS(next_row, next_col, i);
        }
    }
    else if(dir == 1){
        for(int i = 0; i < 3; i++){
            int next_row = row + d_r[i];
            int next_col = col + d_c[i];
            if(next_row < 1 || next_row > SIZE || next_col < 0 || next_col > SIZE) continue;
            if(GRAPH[next_row][next_col] == 1) continue;
            if(i == 1){
                if(GRAPH[next_row - 1][next_col] == 1 || GRAPH[next_row][next_col - 1] == 1) continue;
            }
            DFS(next_row, next_col, i);
        }
    }
    else{
        for(int i = 2; i > 0; i--){
            int next_row = row + d_r[i];
            int next_col = col + d_c[i];
            if(next_row < 1 || next_row > SIZE || next_col < 1 || next_col > SIZE) continue;
            if(GRAPH[next_row][next_col] == 1) continue;
            if(i == 1){
                if(GRAPH[next_row - 1][next_col] == 1 || GRAPH[next_row][next_col - 1] == 1) continue;
            }
            DFS(next_row, next_col, i);
        }
    }
}
int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> SIZE;
    for(int i = 1; i <= SIZE; i++){
        for(int j = 1; j <= SIZE; j++){
            cin >> GRAPH[i][j];
        }
    }

    DFS(1, 2, 0);
    cout << ANS;
}