#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
using namespace std;
int visited[50][50], dp[50][50];
char board[50][50];
int dir[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
int N, M;
int dfs(int r, int c) {
	if (visited[r][c]) {
		cout << -1 << '\n';
		exit(0);
	}

	int&ret = dp[r][c];
	
	if (ret != -1)return ret;

	visited[r][c] = true;

	ret = 0;
	
	for (int d = 0; d < 4; ++d) {
		int jump = board[r][c] - '0';
		int nr = r + dir[d][0] * jump;
		int nc = c + dir[d][1] * jump;

		if (nr < 0 || nr >= N || nc < 0 || nc >= M || board[nr][nc] == 'H')continue;
		
		ret = max(ret, 1 + dfs(nr, nc));
	}
	visited[r][c] = 0;

	return ret;
}
int main() {
	memset(dp, -1, sizeof(dp));

	cin >> N >> M;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j) 
			cin >> board[i][j];

	cout << dfs(0, 0) + 1 << '\n';

	return 0;
}