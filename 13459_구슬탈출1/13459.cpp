#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>

//DFS를 이용한다
using namespace std;
char GRAPH[10][10];
bool CHECK[10][10][2];
pair<int, int> RED;
pair<int, int> BLUE;
int d_r[] = {-1, 0, 1, 0};
int d_c[] = {0, 1, 0, -1};

bool move(int dir){
    if(dir == 0){ // 북

    }
    else if(dir == 1){ // 동

    }
    else if(dir == 2){ // 남

    }
    else{ // 서

    }
}
int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int width, height;
    cin >> height >> width;
    for(int i = 0; i < height; i++){
        char temp[11];
        for(int j = 0; j < width; j++){
            cin >> temp[j];
            if(temp[j] == 'R') {
                RED = make_pair(i, j);
                GRAPH[i][j] = '.';
            }
            else if(temp[j] == 'B') {
                BLUE = make_pair(i, j);
                GRAPH[i][j] = '.';
            }
            else if(temp[j] == '#') {
                CHECK[i][j][0] = true;
                CHECK[i][j][0] = true;
                GRAPH[i][j] = '#';
            }
            else GRAPH[i][j] = temp[j];;
        }
    }

    //BFS


    
    return 0;
}