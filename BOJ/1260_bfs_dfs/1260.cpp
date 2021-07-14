#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//전역변수
vector<vector<int>> node;
vector<bool> check;
int N, M, start_p;
queue<int> bfs_check;

void dfs(int node_point){
    
    check[node_point] = true;
    cout << node_point <<' ';

    for(int i = 1; i <= N; i++){
        if(node[node_point][i] == 1 && check[i] == false){//간선이 존재한다면
            dfs(i);
        }
    }
}

void bfs(int node_point){
 

    check[node_point] = true;
    bfs_check.push(node_point);
    while(!bfs_check.empty()){
        int temp = bfs_check.front();
        bfs_check.pop();

        cout << temp << ' ';
        for(int i = 1; i <= N; i++){
            if(node[temp][i] == 1 && check[i] == false){
                bfs_check.push(i);
                check[i] = true;
            }
        }
    }
}

int main(void){
    cin >> N >> M >> start_p;
    for(int i = 0; i <= N; i++){ // pre_process
        vector<int> temp;
        temp.push_back(i); // 본인 주소 
        for(int j = 0; j < N; j++){
            temp.push_back(0); // 초기화 주소
        }
        node.push_back(temp);
        check.push_back(false); // 체크 초기화
    } 

    //노드 입력
    for(int i = 0; i < M; i++){ // 노드 추가
        int a,b;
        cin >> a >> b;
        node[a][b] = 1;
        node[b][a] = 1;
    }

    dfs(start_p);
    cout << '\n';
    for(int i = 0; i <=N; i++) check[i] = false;
    bfs(start_p);



    return 0;
}
