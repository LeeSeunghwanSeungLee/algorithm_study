#include <iostream>
#include <vector>
using namespace std;

int GRAPH[4][4][16];
int GRAPH_DIR[4][4][16];

struct SHARK{
    int row;
    int col;
    int points;
};
SHARK NOW;

bool CHECK[4][4]; 

int d_r[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int d_c[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
vector<int> ANS;

void reset(int depth){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            GRAPH[i][j][depth] = 0;
            GRAPH_DIR[i][j][depth] = 0;
        }
    }
}
void DFS(int depth){
    //만일 depth가 15회 이상이면 ANS를 소팅하고, 가장 큰 값을 출력한다

    //현재 depth 에서 reset함수를 실행한다
    //물고기를 회전시킨다

    //for(int i = 0; i < 4; i++)반복문 실행
        //int now_row, now_col, next_row, next_col을 설정한다
        //만일 상어의 위치가 틀을 벗어나면 반복문을 그냥 중지시켜버린다
        //만일 CHECK에서 이미 지나갓던 장소라면 continue시켜버린다
        //NOW를 업데이트한다
        //CHECK를 true로 변경한다
        //DFS(depth + 1)
        //NOW를 기존 형태로 바꾼다
        //CHECK를 false 로 변경한다
    //
}
int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> GRAPH[i][j][0] >> GRAPH_DIR[i][j][0];
        }
    }

    //가장 처음 0, 0 을 샤크가 먹는다 -> 0회차

    //DFS(1) 을 실행한다
    return 0;
}