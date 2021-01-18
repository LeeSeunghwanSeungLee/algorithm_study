#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

char tray[1000][1000];
bool tray_check[1000][1000];
int ans;
queue<pair<int, int>> fire;
queue<pair<int, int>> NOW;

int d_height[] = {-1, 0, 1, 0};
int d_width[] = {0, 1, 0, -1};
int main(void){
    // int test_case;
    // cin >> test_case;

    //test_case 반복분
    //NOW, FIRE 클리어
    int width, height;
    cin >> width >> height;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cin >> tray[i][j];
            if(tray[i][j] == '@'){//사람이면
                NOW.push(make_pair(i, j));
                tray[i][j] = '.';
                tray_check[i][j] = false;

            }
            else if(tray[i][j] == '*'){ // 불이면
                fire.push(make_pair(i, j));
                tray_check[i][j] = true;
            }
            else{//벽이면
                tray_check[i][j] = true;
            }
        }
    }

   
    ans = 0;
    while(!NOW.empty()){
        pair<int, int> now = NOW.front();
        NOW.pop();
        ans++;       
        if(now.first < 0 || now.first >= height || now.second < 0 || now.second >= width){
            break;
        }

        for(int i = 0; i < fire.size(); i++){ 
            pair<int, int> now_fire = fire.front();
            fire.pop();
            for(int i = 0; i < 4; i++){
                if(tray[now_fire.first + d_height[i]][now_fire.second + d_width[i]] == '.'){
                    tray[now_fire.first + d_height[i]][now_fire.second + d_width[i]] = '*';
                    fire.push(make_pair(now_fire.first + d_height[i], now_fire.second + d_width[i]));
                }
            }
        }
        for(int i = 0; i < 4; i++){
            if(tray[now.first + d_height[i]][now.second + d_width[i]] != '#' || tray[now.first + d_height[i]][now.second + d_width[i]] != '*'){
                NOW.push(make_pair(now.first + d_height[i], now.second + d_width[i]));
            }
            if(NOW.empty()){
                ans == -1;
            }
        }
    }
    if(ans == -1) printf("IMPOSSIBLE\n");


    


    
    //test_case 반복문 종료

    return 0;
}