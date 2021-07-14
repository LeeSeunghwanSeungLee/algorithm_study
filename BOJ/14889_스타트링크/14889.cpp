#include <iostream>
#include <vector>
#include <math.h>
#define MAX 2147483647
using namespace std;

vector<bool> CHECK;
int SINERGY_TABLE[21][21] = { 0, };
int ans = MAX;
int N;
vector<int> TEAM_A;
vector<int> TEAM_B;

void pre_process() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> SINERGY_TABLE[i][j];

		}
		CHECK.push_back(false);
	}
}
int calc_TotalNumber() {
	int temp(0);
	for (int i = 0; i < N; i++) {
		if (CHECK[i] == true) temp++;
	}
	return temp;
}

void DFS(int depth, int start_num) {
	if (start_num >= N && depth < N / 2) { // except stage
		return;
	}
	if (depth >= N / 2) { // final stage
		TEAM_A.clear();
		TEAM_B.clear();
		for (int i = 0; i < N; i++) {
			if (CHECK[i] == true) {
				TEAM_A.push_back(i);
			}
			else TEAM_B.push_back(i);
		}
		
		//A팀 B팀 계산한다
		int temp_ans(0);
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				temp_ans += SINERGY_TABLE[TEAM_A[i]][TEAM_A[j]];
			}
		}
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				temp_ans -= SINERGY_TABLE[TEAM_B[i]][TEAM_B[j]];
			}
		}
		//ans와 비교한다!
		if (ans > abs(temp_ans)) ans = abs(temp_ans);
		return;
	}
	for (int i = start_num; i < N; i++) {
		if (CHECK[i] == true) continue;
		CHECK[i] = true;
		DFS(depth + 1, i + 1);
		CHECK[i] = false;
	}
}

int main(void) {
	pre_process();
	DFS(0,0);
	cout << ans;
	return 0;
}