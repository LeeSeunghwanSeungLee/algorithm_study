#include <iostream>  
#include <queue>
using namespace std; 
#define N_MAX 100 + 1
 
enum {
    UP, RIGHT, DOWN, LEFT
};
int board[N_MAX][N_MAX] = { 0 };
int dx[4] = { -1, 0 , 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
deque<pair<int, int>> snake; 
int now_direction = RIGHT;
int N, time = 0;
 
void change_direction(char _way){
    switch (_way) {
    case 'L':
        now_direction = (now_direction + 3) % 4;
        break;
    case 'D':
        now_direction = (now_direction + 1) % 4;
        break; 
    }
}
 
bool is_can_move() {
    pair<int, int> before_top = snake.front();
    int now_x = before_top.first + dx[now_direction];
    int now_y = before_top.second + dy[now_direction];
    // 더 이상 못 움직이면 0 리턴 
    if (now_x < 1 || now_x > N || now_y < 1 || now_y > N) return false; 
    if (board[now_x][now_y] == -1) return false;
    
    snake.push_front({ now_x, now_y });
    // 사과 없으면
    if (board[now_x][now_y] != 1) {
        board[snake.back().first][snake.back().second] = 0;
        snake.pop_back();
    }
    board[now_x][now_y] = -1;
    return true;
} 
 
int main(){
    snake.push_back({ 1,1 }); board[1][1] = -1;
    int K; scanf("%d %d", &N, &K);
    for (int K_idx = 0; K_idx < K; K_idx++) {
        int row, col; scanf("%d %d", &row, &col);
        board[row][col] = 1;
    }
    // 이동하는 조건에 맞춰서 이동
    int L; scanf("%d", &L);
    for (int L_idx = 0; L_idx < L; L_idx++) {
        int X, C; scanf("%d %c", &X, &C);
        while (time != X) {
            if (is_can_move() == false) {
                printf("%d", time+1);
                return 0; 
            }
            time++;
        }
        change_direction(C);
    }
    // 이동 조건이 다 끝났으면 현재 방향 상태로 이동 
    while (1) {
        if (is_can_move() == false) {
            printf("%d", time + 1);
            return 0;
        }
        time++;
    }
    return 0;
}
