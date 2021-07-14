#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


int GRAPH[50][50];
int R_GRAPH[50][50];
int R, C, T;
int ROBOT_UP(-1), ROBOT_DOWN(-1);
int d_r[] = { -1, 0, 1, 0 };
int d_c[] = { 0, 1, 0, -1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> C >> T;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> GRAPH[i][j];
			if (GRAPH[i][j] == -1) {
				if (ROBOT_UP == -1) ROBOT_UP = i;
				else ROBOT_DOWN = i;
			}
		}
	}

}


int main(void) {
	init();
	for (int i = 0; i < T; i++) {

		memset(R_GRAPH, 0, sizeof(R_GRAPH));

		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				int now_row = r, now_col = c;
				vector<pair<int, int>> around;
				for (int dir = 0; dir < 4; dir++) {
					int next_row = now_row + d_r[dir], next_col = now_col + d_c[dir];
					if (next_row < 0 || next_row >= R || next_col < 0 || next_col >= C || GRAPH[next_row][next_col] == -1) continue;
					around.push_back(make_pair(next_row, next_col));
				}
				int dust_points = GRAPH[now_row][now_col] / 5;
				for (int j = 0; j < around.size(); j++) {
					int new_row = around[j].first, new_col = around[j].second;
					R_GRAPH[new_row][new_col] += dust_points;
				}
				GRAPH[now_row][now_col] -= dust_points * around.size();
			}
		}
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				GRAPH[r][c] += R_GRAPH[r][c];
			}
		}

		GRAPH[ROBOT_UP - 1][0] = 0;
		for (int r = ROBOT_UP - 1; r >= 1; r--) {
			GRAPH[r][0] = GRAPH[r - 1][0];
		}
		for (int c = 0; c <= C - 2; c++) {
			GRAPH[0][c] = GRAPH[0][c + 1];
		}

		for (int r = 0; r <= ROBOT_UP - 1; r++) {
			GRAPH[r][C - 1] = GRAPH[r + 1][C - 1];
		}
		
		for (int c = C - 1; c >= 2; c--) {
			GRAPH[ROBOT_UP][c] = GRAPH[ROBOT_UP][c - 1];
		}
		GRAPH[ROBOT_UP][1] = 0;

		GRAPH[ROBOT_DOWN + 1][0] = 0;
		for (int r = ROBOT_DOWN + 1; r <= R - 2; r++) {
			GRAPH[r][0] = GRAPH[r + 1][0];
		}
		for (int c = 0; c <= C - 2; c++) {
			GRAPH[R - 1][c] = GRAPH[R - 1][c + 1];
		}
		for (int r = R - 1; r >= ROBOT_DOWN + 1; r--) {
			GRAPH[r][C - 1] = GRAPH[r - 1][C - 1];
		}
		for (int c = C - 1; c >= 2; c--) {
			GRAPH[ROBOT_DOWN][c] = GRAPH[ROBOT_DOWN][c - 1];
		}
		GRAPH[ROBOT_DOWN][1] = 0;
	}
	int ans(0);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (GRAPH[i][j] != 0 && GRAPH[i][j] != -1) ans += GRAPH[i][j];
			//cout << GRAPH[i][j] << ' ';
		}
		//cout << '\n';
	}
	cout << ans;
	return 0;
}