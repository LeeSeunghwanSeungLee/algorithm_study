#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

//전역변수
int N, M, ans;
vector<string> graph;
queue<pair<pair<int, int>, pair<int, int>>> ans_list; // red 위치, blue 위치
pair<int, int> red, blue, target;
//함수
void pre_Process(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
}

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        string temp;
        cin >> temp;
        graph.push_back(temp);  
    }

    for(int i = 0; i < N; i++){ // 맨 처음 위치 결정
        for(int j = 0; j < M; j++){
            if(graph[i][j] == 'R') red = make_pair(i, j);
            else if(graph[i][j] == 'B') blue = make_pair(i, j);
            else if(graph[i][j] = 'O') target = make_pair(i, j);
            else continue;
        }
    }
}

void test(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << graph[i][j] << ' ';
        }
        cout << '\n';
    }
}

pair<int, int> move(int dir, int start_row, int start_col){

    int now_row = start_row;
    int now_col = start_col;
    int ans_row = -1;
    int ans_col = -1;

    switch(dir){
        case 0:
            //left
            for(int i = 0; i < M; i++){
                if(graph[start_row][start_col - 1] == '.') now_col = start_col - 1;
                else if(graph[start_row][start_col - 1] == 'O') ans_col = start_col - 1;
                else break;
            }
            break;
        case 1:
            //right
            for(int i = 0; i < M; i++){
                if(graph[start_row][start_col + 1] == '.') now_col = start_col + 1;
                else if(graph[start_row][start_col + 1] == 'O') ans_col = start_col + 1;
                else break;
            }
            break;
        case 2:
            //up
            for(int i = 0; i < M; i++){
                if(graph[start_row - 1][start_col] == '.') now_row = start_row - 1;
                else if(graph[start_row - 1][start_col == 'O') ans_row = start_row - 1;
                else break;
            }
            break;
        case 3:
            //down
            for(int i = 0; i < M; i++){
                if(graph[start_row + 1][start_col] == '.') now_row = start_row + 1;
                else if(graph[start_row + 1][start_col == 'O') ans_row = start_row + 1;
                else break;
            }
            break;
        default:
            break;
    }
    if(ans_row != -1) return make_pair(ans_row, start_col);
    else if(ans_col != -1) return make_pair(start_row, ans_col);

    return make_pair(now_row, now_col);
}

void check(){
    //
}

void BFS(int first_direction){
    //첫번째 방향 이동해서 좌표를 따온다 - function : move
    //통과 여부 확인 - function : check
        //첫 이동 좌표를 큐에 담는다

    while(!ans_list.empty()){//비어있지 않으면
        pair<pair<int, int>, pair<int, int>> now_position = ans_list.front();
        ans_list.pop();
        for(int i = 0; i < 4; i++){//4가지 방향
            //방향이동하고 판단한다 - function : move
            //통과여부 확인? - function : check
                //큐에 담는다
        }
    } 
}

int main(void){
    pre_Process();
    init();
    // act
    for(int i = 0; i < 4; i++){//4가지 방향에 따라서

    }
    


    //end act
    return 0;
}
