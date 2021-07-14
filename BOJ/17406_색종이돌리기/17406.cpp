#include <iostream>
#include <vector>
#define MAX 987654321
using namespace std;


int N, M, K;
int GRAPH[51][51];
int TMP_GRAPH[51][51];
vector<pair<pair<int, int>, int>> CHANGE_LIST;
vector<int> ORDER;
bool CHECK[6];
int ANS(MAX);

void duplicate(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            TMP_GRAPH[i][j] = GRAPH[i][j];
        }
    }
}
int check_ans(){
    int ans(MAX);
    for(int i = 1; i <= N; i++){
        int tmp_ans(0);
        for(int j = 1; j <= M; j++){
            tmp_ans += TMP_GRAPH[i][j];
        }
        ans = min(tmp_ans, ans);
    }
    return ans;
}

void rotate(pair<pair<int, int>, int> now){
    int row = now.first.first, col = now.first.second, size = now.second;
    for(int peer = 1; peer <= size; peer++){
        int left_row = row - peer;
        int left_col = col - peer;
        int right_row = row + peer;
        int right_col = col + peer;

        int temp = TMP_GRAPH[left_row][left_col];
        for(int i = left_row; i < right_row; i++){
            TMP_GRAPH[i][left_col] = TMP_GRAPH[i + 1][left_col];
        }

        for(int i = left_col; i < right_col; i++){
            TMP_GRAPH[right_row][i] = TMP_GRAPH[right_row][i + 1];
        }

        for(int i = right_row; i > left_row; i--){
            TMP_GRAPH[i][right_col] = TMP_GRAPH[i - 1][right_col];
        }

        for(int i = right_col; i > left_col + 1; i--){
            TMP_GRAPH[left_row][i] = TMP_GRAPH[left_row][i - 1];
        }

        TMP_GRAPH[left_row][left_col + 1] = temp;
    }
}



void DFS(int depth){
    if(depth >= CHANGE_LIST.size()){
        // for(int i = 0; i < CHANGE_LIST.size(); i++){
        //     cout << ORDER[i] << ' ';
        // }
        // cout << '\n';
        duplicate();
        for(int i = 0; i < CHANGE_LIST.size(); i++){
            rotate(CHANGE_LIST[ORDER[i]]);
        }
        ANS = min(ANS, check_ans());
    }

    for(int i = 0; i < CHANGE_LIST.size(); i++){
        if(CHECK[i] == false){
            CHECK[i] = true;
            ORDER.push_back(i);
            DFS(depth + 1);
            CHECK[i] = false;
            ORDER.pop_back();
        }
    }
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            cin >> GRAPH[i][j];
        }
    }

    for(int i = 0; i < K; i++){
        int temp_1, temp_2, temp_3;
        cin >> temp_1 >> temp_2 >> temp_3;
        CHANGE_LIST.push_back(make_pair(make_pair(temp_1, temp_2), temp_3));
    }

    
    DFS(0);
    cout << ANS;
    return 0;
}