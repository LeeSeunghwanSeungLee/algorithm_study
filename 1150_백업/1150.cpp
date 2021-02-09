#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long ll;
int N, K;
ll D_LIST[100000];
int CHECK[100000];
vector<int> NODE;
// DP를 어떻게 사용할지 고려해야함
ll ANS;
ll tmp_ans(0);
ll count() {
	ll tmp_ans(0);
	for (int i = 0; i < NODE.size() / 2; i++) {
		tmp_ans += (D_LIST[NODE[2 * i + 1]] - D_LIST[NODE[2 * i]]);
	}
	return tmp_ans;
}
void DFS(int depth, int start_p) {
	if (start_p >= N) return;
	if (depth >= 2) {
		if (NODE.size() / 2 >= K) {
			if (ANS == 0) ANS = tmp_ans + (D_LIST[NODE[NODE.size() - 1]] - D_LIST[NODE[NODE.size() - 2]]);
			else {
				ANS = min(ANS, tmp_ans + (D_LIST[NODE[NODE.size() - 1]] - D_LIST[NODE[NODE.size() - 2]]));
			}
			return;
		}
		tmp_ans += (D_LIST[NODE[NODE.size() - 1]] - D_LIST[NODE[NODE.size() - 2]]);
		DFS(0, NODE[NODE.size() - 1] + 1);
		tmp_ans -= (D_LIST[NODE[NODE.size() - 1]] - D_LIST[NODE[NODE.size() - 2]]);
		return;
	}

	for (int i = start_p; i < N; i++) {
		if (CHECK[i] == false) {
			CHECK[i] = true;
			NODE.push_back(i);
			DFS(depth + 1, i);
			CHECK[i] = false;
			NODE.pop_back();
		}
	}
}
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> D_LIST[i];
	}

	DFS(0, 0);
	cout << ANS;
	return 0;
}