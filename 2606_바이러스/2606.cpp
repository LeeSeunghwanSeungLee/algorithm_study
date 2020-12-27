#include <iostream>
#include <queue>

using namespace std;

//전역
int N, M;
int ** graph_check;
queue<int> temp;
bool* check;
int ans(0);

void init(){
    //N, M 입력받는다
    cin >> N >> M;
    //동적할당으로 graph 작성한다
    graph_check = new int* [N + 1];
    check = new bool[N+1];
    for(int i = 0; i <=N; i++){
        graph_check[i] = new int [N+1];
        check[i] = false;
    }

    for(int i = 0; i <= N; i++){ // 그래프 초기화
        for(int j = 0; j <= N; j++){
            graph_check[i][j] = 0;
        }
    }
}

void draw_graph(){
    int row, col;
    for(int i = 0; i < M; i++){
        cin >> row >> col;
        graph_check[row][col] = 1;
        graph_check[col][row] = 1;
    }

}

void bfs(int start_p){
    temp.push(start_p);
    check[start_p] = true;
    
    while(!temp.empty()){//비어있지 않다면..
        int v = temp.front();
        check[v] = true;
        temp.pop();
        for(int i = 1; i<=N; i++){
            if(graph_check[v][i] == 1 && check[i] == false) {
                temp.push(i);
                check[i] = true;
                ans++;
            }
        }

    }
}

int main(void){
    init();
    draw_graph();
    bfs(1);

    cout << ans;
    return 0;
}