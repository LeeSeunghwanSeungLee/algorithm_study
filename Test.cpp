#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define MAX 987654321

using namespace std;

int TEST_CASE;
int SIZE;
int GRAPH[13][13];
bool CHECK[13][13];
vector<pair<int, int>> PROCESSOR_LIST;
int ANS(MAX);

int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};
void DFS(int depth, int core, int temp_ans){
    //만일 최종지점에 도달했으면 vector.pushback 이후 리턴한다
    for(int i = 0; i < 4; i++){
        //현재 위치 표현
        //i 에 해당하는 방향으로 가장자리까지 true 가 없는 지 확인.. 있다면 DFS(depth + 1, core, temp_ans);
        //전부 체크하고 길이를 측정(len)
        //DFS(depth + 1, core + 1, temp_ans + len);
        //전부 체크 해제한다
    } 
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> TEST_CASE;
    for(int tc = 1; tc <= TEST_CASE; tc++){
        
        cin >> SIZE;

        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                cin >> GRAPH[i][j];
                if(GRAPH[i][j] == 1) {
                    CHECK[i][j] = true;
                    if(i != 0 && i != SIZE -1 && j != 0 && j != SIZE - 1) PROCESSOR_LIST.push_back(make_pair(i, j));                    
                }
            }
        }
        DFS(0, 0, 0);
        //소팅한다
        cout << '#' << tc << ' ' << ANS << '\n';
    }

    return 0;
}