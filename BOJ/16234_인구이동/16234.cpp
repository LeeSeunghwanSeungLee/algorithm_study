#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
using namespace std;

int N, L, R;
int GRAPH[50][50];
int ans(0);
bool VISITED[50][50]; 
vector<pair<int, int>> SUM_LIST;
int d_r[] = { -1, 0, 1, 0 };
int d_c[] = { 0, 1, 0 ,-1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> GRAPH[i][j];
		}
	}
}
void BFS(int init_row, int init_col) {
	VISITED[init_row][init_col] = true;
	queue<pair<int, int>> q;
	q.push(make_pair(init_row, init_col));
	SUM_LIST.push_back(make_pair(init_row, init_col));
	while (!q.empty()) {
		int now_row = q.front().first;
		int now_col = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = now_row + d_r[i];
			int next_col = now_col + d_c[i];
			if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
			if (VISITED[next_row][next_col]) continue;
			if (abs(GRAPH[next_row][next_col] - GRAPH[now_row][now_col]) < L || abs(GRAPH[next_row][next_col] - GRAPH[now_row][now_col]) > R) continue;
			VISITED[next_row][next_col] = true;
			pair<int, int> next = make_pair(next_row, next_col);
			SUM_LIST.push_back(next);
			q.push(next);
		}
	}
}


int main(void){
	init();
	while (1) {
		bool flag = true; 
		memset(VISITED, 0, sizeof(VISITED));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (VISITED[i][j] == true) continue;
				BFS(i, j);
				if (SUM_LIST.size() > 1) {
					int temp_ans(0);
					for (int k = 0; k < SUM_LIST.size(); k++) {
						temp_ans += GRAPH[SUM_LIST[k].first][SUM_LIST[k].second];
					}
					temp_ans /= SUM_LIST.size();
					for (int k = 0; k < SUM_LIST.size(); k++) {
						GRAPH[SUM_LIST[k].first][SUM_LIST[k].second] = temp_ans;
					}
					flag = false;
				}
				SUM_LIST.clear();
			}
		}
		if (flag) {
			cout << ans;
			break;
		}
		ans++;
	}
	return 0;
}#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
using namespace std;

int N, L, R;
int GRAPH[50][50];
int ans(0);
bool VISITED[50][50]; 
vector<pair<int, int>> SUM_LIST;
int d_r[] = { -1, 0, 1, 0 };
int d_c[] = { 0, 1, 0 ,-1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> GRAPH[i][j];
		}
	}
}
void BFS(int init_row, int init_col) {
	VISITED[init_row][init_col] = true;
	queue<pair<int, int>> q;
	q.push(make_pair(init_row, init_col));
	SUM_LIST.push_back(make_pair(init_row, init_col));
	while (!q.empty()) {
		int now_row = q.front().first;
		int now_col = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = now_row + d_r[i];
			int next_col = now_col + d_c[i];
			if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
			if (VISITED[next_row][next_col]) continue;
			if (abs(GRAPH[next_row][next_col] - GRAPH[now_row][now_col]) < L || abs(GRAPH[next_row][next_col] - GRAPH[now_row][now_col]) > R) continue;
			VISITED[next_row][next_col] = true;
			pair<int, int> next = make_pair(next_row, next_col);
			SUM_LIST.push_back(next);
			q.push(next);
		}
	}
}


int main(void){
	init();
	while (1) {
		bool flag = true; 
		memset(VISITED, 0, sizeof(VISITED));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (VISITED[i][j] == true) continue;
				BFS(i, j);
				if (SUM_LIST.size() > 1) {
					int temp_ans(0);
					for (int k = 0; k < SUM_LIST.size(); k++) {
						temp_ans += GRAPH[SUM_LIST[k].first][SUM_LIST[k].second];
					}
					temp_ans /= SUM_LIST.size();
					for (int k = 0; k < SUM_LIST.size(); k++) {
						GRAPH[SUM_LIST[k].first][SUM_LIST[k].second] = temp_ans;
					}
					flag = false;
				}
				SUM_LIST.clear();
			}
		}
		if (flag) {
			cout << ans;
			break;
		}
		ans++;
	}
	return 0;
}