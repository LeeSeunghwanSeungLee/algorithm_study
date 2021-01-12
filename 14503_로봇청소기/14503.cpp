#include <iostream>
#include <queue>
#include <tuple>
#include <utility>

using namespace std;

int N, M;
int map[51][51];
int ans(0);
queue<tuple<int, int, int>> tray;// r, c, direction 순서대로 대입한다

int d_c[] = {0, 1, 0, -1};
int d_r[] = {-1, 0, 1, 0};

int turn_left(int dir){
    if(dir == 0) return 3;
    return (dir - 1);
}
void pre_process(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M ;
    
    int r, c, dir;
    cin >> r >> c >> dir;
    tray.push(make_tuple(r, c, dir));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
}

bool check_AllAround(int row, int col){
    for(int i = 0; i < 4; i++){
        if(map[row + d_r[i]][col + d_c[i]] == 0) return true;
    }
    return false;
}

void main_process(){

    while(!tray.empty()){
        tuple<int, int, int> temp = tray.front();
        tray.pop();
        //1단계
        if(map[get<0>(temp)][get<1>(temp)] == 0){
            map[get<0>(temp)][get<1>(temp)] = -1;
            ans++;
        }
        //2단계
        

        // 4방향가능
        if(check_AllAround(get<0>(temp), get<1>(temp))){
            int now_dir = turn_left(get<2>(temp));
            int now_r = get<0>(temp) + d_r[now_dir];
            int now_c = get<1>(temp) + d_c[now_dir];
            if(map[now_r][now_c] == 0){
                tray.push(make_tuple(now_r, now_c, now_dir));
                continue;
             }
        
            else{
                tray.push(make_tuple(get<0>(temp), get<1>(temp), now_dir));
                continue;
            }
        }
        else{
            int now_dir = get<2>(temp);
            int now_r = get<0>(temp) - d_r[now_dir];
            int now_c = get<1>(temp) - d_c[now_dir];
            if(map[now_r][now_c] == 1){
                cout << ans;
                return;
            }
            tray.push(make_tuple(now_r, now_c, now_dir));
            continue;        
         }

    }
}

int main(void){
    pre_process();
    main_process();
    return 0;
}