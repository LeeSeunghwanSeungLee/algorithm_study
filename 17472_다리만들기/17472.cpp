#include <iostream>
#include <vector>

using namespace std;

int N, M;
int GRAPH[10][10];
bool CONTINENT[7][7]; // 대륙간 연결성을 확인하기 위한 장표
int CONTINENT_DIST[7][7];
int ANS(0);

void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    int area(0);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> GRAPH[i][j];
            if(GRAPH[i][j] == 1){
                //상하 좌우의 영역을 체크한다
                //if 0이아닌 녀석이 있으면 그 값을 GRAPH[i][j] 에 넣는다
                //else GRAPH[i][j] = ++area; 
            }
        }
    }
}
int main(void){
    init();
    for(int row = 0; row < N; row++){ // 가로에서 확인
        //from to 선언 (-1)
        //이거를 queue에 pair로 담는다
        for(int col = 0; col < M; col++){
            //만일 0 이 아닌 녀석이 나오면 from To 순서대로 저장
        }
        //while(!.queue.empty())
            //만일 거리가 1이하면 컨티뉴
            //아니면 
                //CONTINENT[from][to] 가 false 면 true 로 변경 후 기존의 true엿던 녀석들을통해 전부 다리를 놓아준다
                //true면 CONTINENT_DIST에서 더 짧은 녀석으로 교체한다
                //이후 ANS를 수정한다
    }

    for(int col = 0; col < M; col++){ // 세로에서 확인

    }


    return 0;
}