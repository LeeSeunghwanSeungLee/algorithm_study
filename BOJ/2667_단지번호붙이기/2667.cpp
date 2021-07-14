#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int size_; // graph 사이즈
queue<pair<int, int>> pocket;
vector<vector<int>> graph;
vector<int> ans; // ans.size(). ans[0]... 와같은 형식으로 출력예정
vector<vector<bool>> check; // graph check 
int now(-1);
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
void init(){
    ios::sync_with_stdio(false); // stdio 동기화
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> size_;   //그래프 사이즈 입력
    for(int i = 0; i < size_; i++){ // 그래프 그리기
        string temp;
        vector<int> temp_graph;
        vector<bool> temp_check;
        cin >> temp;
        for(int j = 0; j < temp.size(); j++){
            if(temp[j] == '0') {
                temp_graph.push_back(0);
                temp_check.push_back(true);
            }
            else{
                temp_graph.push_back(1);
                temp_check.push_back(false);
            }
        }
        graph.push_back(temp_graph);
        check.push_back(temp_check);
        temp_graph.clear();
        temp_check.clear();
    }
}

void test_print(){
    for(int i = 0; i < size_; i++){
        for(int j = 0; j < size_; j++){
            cout << check[i][j] << ' ';
        }
        cout << '\n';
    }
}

void BFS(int start_row, int start_col){
    now++;
    pocket.push(make_pair(start_row, start_col));
    check[start_row][start_col] = true;
    ans.push_back(0);
    while(!pocket.empty()){
        pair<int, int> present_coordinate = pocket.front();
        pocket.pop();
        ans[now]++;
        // cout << now << ' ' << present_coordinate.first << ' ' << present_coordinate.second << '\n';
        for(int i = 0; i < 4; i++){
            if(dx[i] + present_coordinate.second < 0 || dx[i] + present_coordinate.second >= size_) continue;
            if(dy[i] + present_coordinate.first < 0 || dy[i] + present_coordinate.first >= size_) continue;
            if(check[dy[i] + present_coordinate.first][dx[i] + present_coordinate.second] == true) continue;
            if(graph[dy[i] + present_coordinate.first][dx[i] + present_coordinate.second] == 1) {
                pocket.push(make_pair(dy[i] + present_coordinate.first, dx[i] + present_coordinate.second));
                check[dy[i] + present_coordinate.first][dx[i] + present_coordinate.second] = true;
            }
        }
    }
}

void main_Process(){
    for(int i = 0; i < size_; i++){
        for(int j = 0; j < size_; j++){
            if(check[i][j] != true) BFS(i, j);
        }
    }
}

int main(void){

    init();
    main_Process();
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << '\n';
    }
    return 0;
}