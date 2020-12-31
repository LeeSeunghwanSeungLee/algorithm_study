#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;


int N;
int arr[20][20] = {0};
vector<int> ans;
int temp_arr[20][20] = {0};

void draw_temp_arr(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            temp_arr[i][j] = arr[i][j];           
        }
    }
}

void swap_temp_arr(int row_1, int col_1, int row_2, int col_2){
    int temp = temp_arr[row_1][col_1];
    temp_arr[row_1][col_1] = temp_arr[row_2][col_2];
    temp_arr[row_2][col_2] = temp;
}

void plus_temp_arr(int row_1, int col_1, int row_2, int col_2){
    temp_arr[row_1][col_1] += temp_arr[row_2][col_2];
    temp_arr[row_2][col_2] = 0;
}

void move_temp(int dir){ 
    switch (dir)
    {
    case 0://상
        for(int i = N - 1; i > 0; i--){
            for(int j = 0; j < N; j++){
                if(temp_arr[i - 1][j] == 0 && temp_arr[i][j] != 0) swap_temp_arr(i - 1, j, i, j);
                else if(temp_arr[i - 1][j] == temp_arr[i][j] && temp_arr[i][j] != 0) plus_temp_arr(i - 1, j, i, j);
            }
        }
        break;
    case 1://하
        for(int i = 0; i < N - 1; i++){
            for(int j = 0; j < N; j++){
                if(temp_arr[i + 1][j] == 0 && temp_arr[i][j] != 0) swap_temp_arr(i + 1, j, i, j);
                else if(temp_arr[i + 1][j] == temp_arr[i][j] && temp_arr[i][j] != 0) plus_temp_arr(i + 1, j, i, j);
            }
        }
        break;
    case 2://좌
        for(int j = N - 1; j > 0; j--){
            for(int i = 0; i < N; i++){
                if(temp_arr[i][j - 1] == 0 && temp_arr[i][j] != 0) swap_temp_arr(i, j - 1, i, j);
                else if(temp_arr[i][j - 1] == temp_arr[i][j] && temp_arr[i][j] != 0) plus_temp_arr(i, j - 1, i, j);
            }
        }
        break;
    case 3://우
        for(int j = 0; j < N - 1; j++){
            for(int i = 0; i < N; i++){
                if(temp_arr[i][j + 1] == 0 && temp_arr[i][j] != 0) swap_temp_arr(i, j + 1, i, j);
                else if(temp_arr[i][j + 1] == temp_arr[i][j] && temp_arr[i][j] != 0) plus_temp_arr(i, j + 1, i, j);
            }
        }
        break;
    
    default:
        break;
    }
}

int find_max(){
    int max = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(max < temp_arr[i][j]) max = temp_arr[i][j];
        }
    }
    return max;
}

void DFS(int depth, int pre_dir){
    if(depth > 4) {
        int temp_ans = find_max();
        ans.push_back(temp_ans);
        return;
    }
    


    for(int i = 0; i < 4; i++){
        //액션을 취해서 temp 를 변형시킨다
        if(depth == 0) draw_temp_arr();
        if(i == pre_dir) continue; // 이전과 같은 방향으로는 될 수 없다
        move_temp(i);
        DFS(depth + 1, i);
        
    }
    
}

int main(void){
    cin >> N;
    for(int i = 0; i < N; i++){ // 그래프 그리기
        for(int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
    DFS(0, -1);
    sort(ans.begin(), ans.end());
    cout << ans[ans.size() - 1];

    
    return 0;
}


//수정사항

// 순서가 잘못된거같음
// 상의경우
// 1 행 부터 위로 쭉
// 2행부터 위로쭊
// 3행부터 위로 쭊 형태로 변경해야한다