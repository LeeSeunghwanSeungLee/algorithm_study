#include <iostream>
#include <queue>

using namespace std;

struct node
{
    int row;
    int col;
    int cnt;
};

int H, W;
int GRAPH[51][51];
bool VISITED[51][51];
queue<node> Q;
int ans;
int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};

bool move(int &row, int &col, int num, int dir){
    //dir 방향으로 num만큼이동한다.
    row += num * d_r[dir];
    col += num * d_c[dir];
    if(row < 0 || row >= H || col < 0 || col >= W) return true;
    else if(GRAPH[row][col] == -1) return true;
    return false;  
} 


void BFS(){
    //최초 큐를 담는다
    node f;
    f.row = 0; f.col = 0; f.cnt = 0;
    Q.push(f);
    
    while(!Q.empty()){
    
        node now = Q.front();
        Q.pop();
        VISITED[now.row][now.col] = true;
        for(int i = 0; i < 4; i++){ 
            int t_r = now.row; int t_c = now.col; int cnt = now.cnt + 1;
            if(move(t_r, t_c, GRAPH[t_r][t_c], i)){
                if(ans < cnt) ans = cnt;
                continue;
            }
            if(VISITED[t_r][t_c] == true){
                cout << -1;
                return;
            }
            node new_node;
            new_node.row = t_r; new_node.col = t_c; new_node.cnt = cnt;
            Q.push(new_node);
        }
    }
    cout << ans;
    return;
}

void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> H >> W;

    for(int i = 0; i < H; i++){
        char temp[50];
        for(int j = 0; j < W; j++){
            cin >> temp[j];
            if(temp[j] == 'H') GRAPH[i][j] = -1;
            else GRAPH[i][j] = temp[j] - '0';
        }
    }
}
int main(void){
    init(); // 기본값
    BFS();
    return 0;
}