
#include <iostream>
#include <queue>

using namespace std;

struct bead {
	int rx, ry, bx, by, d;
};

int m = 0, n = 0;
char map[10][10];
bool check[10][10][10][10];
queue<bead> q;
const int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, -1, 0, 1 };

void move(int& x, int& y, int& c, int dx, int dy) {
	while (map[x][y] != 'O' && map[x + dx][y + dy] != '#') {
		x += dx;
		y += dy;
		c++;
	}
}

void bfs() {
	while (!q.empty()) {
		int rx = q.front().rx;
		int ry = q.front().ry;
		int bx = q.front().bx;
		int by = q.front().by;
		int d = q.front().d;

		q.pop();

		if (d >= 10) break;

		for (int i = 0; i < 4; i++) {
			int nrx = rx, nry = ry, nbx = bx, nby = by, nd = d + 1;
			int rc = 0, bc = 0;

			move(nrx, nry, rc, dx[i], dy[i]);
			move(nbx, nby, bc, dx[i], dy[i]);

			if (map[nbx][nby] == 'O') continue;
			if (map[nrx][nry] == 'O') {
				cout << 1;
				return;
			}

			if (nrx == nbx && nry == nby) {
				if (rc > bc) nrx -= dx[i], nry -= dy[i];
				else nbx -= dx[i], nby -= dy[i];
			}

			if (check[nrx][nry][nbx][nby]) continue;
			check[nrx][nry][nbx][nby] = true;
			q.push({ nrx, nry, nbx, nby, nd });
		}
	}
	cout << 0;
}

int main() {
	int rx = 0, ry = 0, bx = 0, by = 0;

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%1s", &map[i][j]);

			if (map[i][j] == 'R') rx = i, ry = j;
			else if (map[i][j] == 'B') bx = i, by = j;
		}
	}

	check[rx][ry][bx][by] = true;
	q.push({ rx, ry, bx, by, 0 });
	bfs();

	return 0;
}