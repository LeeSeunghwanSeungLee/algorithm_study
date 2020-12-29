#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

//전역
int T, N, M, worm_n;
vector<vector<int>> graph;
vector<vector<bool>> check;
int ans(0);
vector<int> ans_arr;
queue<pair<int, int>> coord_pocket;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

//함수
void pre_process() {
	ios::sync_with_stdio(false); // 버퍼 줄이기
	cin.tie(NULL);
	cout.tie(NULL);
}

void init() {
	graph.clear(); // initialize
	check.clear();
	ans = 0;

	for (int i = 0; i < N; i++) { // draw graph & check table 
		vector<int> temp_graph;
		vector<bool> temp_check;
		for (int j = 0; j < M; j++) {
			temp_graph.push_back(0);
			temp_check.push_back(true);
		}
		graph.push_back(temp_graph);
		check.push_back(temp_check);
	}
	for (int i = 0; i < worm_n; i++) {
		int temp_row, temp_col;
		cin >> temp_row >> temp_col;
		graph[temp_row][temp_col] = 1;
		check[temp_row][temp_col] = false;
	}
}

void BFS(int start_row, int start_col){
	ans++;
	check[start_row][start_col] = true;
	coord_pocket.push(make_pair(start_row, start_col));

	while (!coord_pocket.empty()) {
		pair<int, int> now_coord = coord_pocket.front();
		coord_pocket.pop();
		for (int i = 0; i < 4; i++) {
			int now_x = now_coord.second + dx[i];
			int now_y = now_coord.first + dy[i];
			if ( now_x >= 0 && now_x <  M&& now_y >= 0 && now_y < N) {
				if (graph[now_y][now_x] == 1 && check[now_y][now_x] == false) {
					check[now_y][now_x] = true;
					coord_pocket.push(make_pair(now_y, now_x));
				}
			}
		}
	}
}

int main(void) {
	pre_process();
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N >> M >> worm_n; // test_case, row_size, col_size, worm number
		init();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (graph[i][j] == 1 && check[i][j] == false) BFS(i, j);
			}
		}
		ans_arr.push_back(ans);
	}
	for (int i = 0; i < ans_arr.size(); i++) {
		cout << ans_arr[i] << '\n';
	}
	return 0;
}