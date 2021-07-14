#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
//전역변수

vector<vector<long long>> tri;
vector<vector<long long>> dp_tri;

int main(void) {
	int layer;
	cin >> layer;

	for (int i = 0; i < layer; i++) { // draw triangle
		vector<long long> temp;
		for (int j = 0; j <= i; j++) {
			long long t;
			cin >> t;
			temp.push_back(t);
		}
		tri.push_back(temp);
	}

    int cnt = 0;
	for (int i = 1; i < layer; i++) { // 실제 연산부분
		for (int j = 0; j <= i; j++) {
            cnt++;
			if (j == 0) tri[i][j] = tri[i - 1][j] + tri[i][j]; // 왼쪽
			else if (j == i) tri[i][j] = tri[i - 1][j - 1] + tri[i][j]; // 오늘쪽
			else {
				tri[i][j] = max(tri[i - 1][j - 1], tri[i - 1][j]) + tri[i][j];
			}
		}
	}


	//마지막 layer 에서 최대값을 찾는다
	long long max = 0;
	for (int i = 0; i < layer; i++) {
		if (max < tri[layer - 1][i]) max = tri[layer - 1][i];
	}

	cout << max;

	return 0;
}