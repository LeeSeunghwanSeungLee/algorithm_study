#include <iostream>
#include <queue>
#include <string>
#include <math.h>
using namespace std;

int GEAR[5][8] = {0,};
int ans(0);
queue<pair<int, int>> rotate_list;
int K;


void rotate_gear(int dir, int num){
    if(dir == 1){ // 시계방향
        int temp = GEAR[num][7];
        for(int i = 6; i >=0; i--){
            GEAR[num][i + 1] = GEAR[num][i];
        }
        GEAR[num][0] = temp;
        return;
    }
    else if(dir == -1){ // 반시계방향
        int temp = GEAR[num][0];
        for(int i = 1; i <= 7; i++){
            GEAR[num][i - 1] = GEAR[num][i];
        }
        GEAR[num][7] = temp;
        return;
    }
    else return;
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for(int i = 1; i <= 4; i++){
        char temp[8];
        for (int j = 0; j < 8; j++){
            cin >> temp[j];
            GEAR[i][j] = temp[j] - '0';
        }
    }

    cin >> K;
    for(int i = 0; i < K; i++){
        int temp_1, temp_2;
        cin >> temp_1 >> temp_2;
        rotate_list.push(make_pair(temp_1, temp_2));
    }

    while(!rotate_list.empty()){
        pair<int, int> now_turn = rotate_list.front();
        rotate_list.pop();
        queue<pair<int, int>> check;
        check.push(make_pair(now_turn.second, now_turn.first));

        for(int i = now_turn.first; i < 4; i++){ // 오른쪽 확인
            if(GEAR[i][2] == GEAR[i + 1][6]){
                break;
            }

            if((now_turn.first + i + 1) % 2 == 0){
                check.push(make_pair(now_turn.second, i + 1));
            }
            else{
                check.push(make_pair(-now_turn.second, i + 1));
            }
        }

        for(int i = now_turn.first; i > 1; i--){
            if(GEAR[i][6] == GEAR[i - 1][2]){
                break;
            }

            if((now_turn.first + i - 1) % 2 == 0){
                check.push(make_pair(now_turn.second, i - 1));
            }
            else{
                check.push(make_pair(-now_turn.second, i - 1));
            }
        }
        while(!check.empty()){
            pair<int, int> action = check.front();
            check.pop();
            rotate_gear(action.first, action.second);
        }
    }

    
    for(int i = 1; i <= 4; i++){
        if(GEAR[i][0] == 0) continue;

        ans += pow(2, i - 1);
    }
    cout << ans;


   
    return 0;
}