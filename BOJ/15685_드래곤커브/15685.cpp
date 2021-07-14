#include <iostream>
#include <vector>
#include <math.h>
using namespace std;



int N;
bool H_EDGE[100][100] = {0,};
bool V_EDGE[100][100] = {0,};
vector<vector<int>> GEN;
int d_c[] = { 1, 0, -1, 0};
int d_r[] = { 0, -1, 0, 1};
int ans(0);
void check_edge(int row_1, int col_1, int row_2, int col_2){
    if(row_1 < 0 || row_1 >= N || col_1 < 0 || col_1 >= N) return;
    if(row_2 < 0 || row_2 >= N || col_2 < 0 || col_2 >= N) return;
    if(col_1 == col_2){
        int start_row = min(row_1, row_2);
        V_EDGE[start_row][col_1] = true;
        return;
    }
    else if(row_1 == row_2){ 
        int start_col = min(col_1, col_2);
        H_EDGE[row_1][start_col] = true;
        return;
    }

    return;
}
void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    for(int i = 0; i <= 10; i++){
        if( i == 0 || i == 1) {
            vector<int> temp;
            temp.push_back(0);
            GEN.push_back(temp);
        }
        else{
            vector<int> temp;
            for(int j = 0; j < GEN[i - 1].size(); j++){
                temp.push_back(GEN[i - 1][j]);
            }
            for(int j = GEN[i - 1].size() - 1; j >= 0; j--){
                temp.push_back((GEN[i - 1][j] + 1) % 4);
            }
            GEN.push_back(temp);
        }
    }

    cin >> N;
    for(int time = 0; time < N; time++){
        int start_col, start_row, start_dir, start_gen;
        cin >> start_col >> start_row >> start_dir >> start_gen;
        int now_col = start_col, now_row = start_row;
        for(int i = 0; i < GEN[start_gen].size(); i++){
            int next_row = now_row + d_r[(start_dir + GEN[start_gen][i]) % 4];
            int next_col = now_col + d_c[(start_dir + GEN[start_gen][i]) % 4];
            check_edge(now_row, now_col, next_row, next_col);
            now_row = next_row, now_col = next_col;
        }
    }
}

int main(void){
    init();
    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - 1; j++){
            cout << H_EDGE[i][j] << ' ';
            // if(H_EDGE[i][j] == false || H_EDGE[i + 1][j] == false) continue;
            // if(V_EDGE[i][j] == false || V_EDGE[i][j + 1] == false) continue;
            // ans++;
        }
        cout << '\n';
    }

    // cout << ans;
    return 0;
}