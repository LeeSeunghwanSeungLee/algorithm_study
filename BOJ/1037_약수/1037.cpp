#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//전역
vector<int> defactor;

int find_min() {
	for (int i = 2; i <= defactor[0]; i++) {
		if (i == defactor[0]) return defactor[0]; // 마지막에 도달하면 0번째 값밖에 없어진다

		for (int j = 0; j < defactor.size(); j++){
			if (defactor[j] % i != 0) break;
			if (j == defactor.size() - 1) { // 마지막까지 도달했다면... 최소약수겠지?
				return i;
			}
		}
	}
}
int main(void) {
	int len;
	cin >> len;
	for (int i = 0; i < len; i++) {
		int temp;
		cin >> temp;
		defactor.push_back(temp);
	}

	sort(defactor.begin(), defactor.end()); //오름차순으로 정렬
	
	int ans;
	int min_defactor;
	//최소약수를 구한다
	min_defactor = find_min();

	//최소 약수 * vector에서 최대값 = ans
	ans = min_defactor * defactor[defactor.size() - 1];
	cout << ans;
	return 0;
}