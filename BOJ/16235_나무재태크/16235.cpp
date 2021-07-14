#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int N, M, K;
int TOTAL_TREE(0);
int LAND[11][11] = { {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 },
					{5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5 }};
vector<pair<pair<int, int>, int>> ROBOT;
vector<int> TREE[11][11];
vector<int> DEAD_TREE[11][11];
int d_r[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int d_c[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int points;
			cin >> points;
			ROBOT.push_back(make_pair(make_pair(i, j), points));
		}
	}

	for (int i = 0; i < M; i++) {
		int row, col, size;
		cin >> row >> col >> size;
		TREE[row][col].push_back(size);
		TOTAL_TREE++;
	}
}
int main(void) {
	init();
	int year;
	for (year = 0; year < K; year++) {
		if (year != 0 && TOTAL_TREE <= 0) {
			break;
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				DEAD_TREE[i][j].clear();
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (TREE[i][j].size() == 0) continue;
				sort(TREE[i][j].begin(), TREE[i][j].end());
				for (int k = 0; k < TREE[i][j].size(); k++) {
					if (LAND[i][j] < TREE[i][j][k]) { // 여기 확인
						//LAND[i][j] = 0;
						int boundary = TREE[i][j].size();
						for (int a = boundary - 1; a >= k; a--) {
							DEAD_TREE[i][j].push_back(TREE[i][j][a]);
							TREE[i][j].pop_back();
							TOTAL_TREE--;
						}
						break;
					}
					LAND[i][j] -= TREE[i][j][k];
					TREE[i][j][k]++;
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				for (int k = 0; k < DEAD_TREE[i][j].size(); k++) {
					LAND[i][j] += (DEAD_TREE[i][j][k] / 2);
				}
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				for (int k = 0; k < TREE[i][j].size(); k++) {
					if (TREE[i][j][k] % 5 != 0) continue;
					for (int dir = 0; dir < 8; dir++) {
						int next_row = i + d_r[dir];
						int next_col = j + d_c[dir];
						if (next_row <= 0 || next_row > N || next_col <= 0 || next_col > N) continue;
						TREE[next_row][next_col].push_back(1);
						TOTAL_TREE++;
					}
				}
			}
		}
		for (int i = 0; i < ROBOT.size(); i++) {
			LAND[ROBOT[i].first.first][ROBOT[i].first.second] += ROBOT[i].second;
		}
	}
	cout << TOTAL_TREE << '\n';
	return 0;
}