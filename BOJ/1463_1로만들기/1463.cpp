#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
//전역
vector<long long> dp; // 3열로 고정할 예정임
//함수
long long min_method(vector<long long> v) {
	long long min = 9223372036854775806;
	for (int i = 0; i < v.size(); i++) {
		if (min > v[i]) min = v[i];
	}
	return min;
}


int main(void) {
	
	int layer;
	cin >> layer;

	//0 번쨰의 경우
	dp.push_back(0);

	//1번쨰의 경우
	dp.push_back(0);
	//2번째의 경우
	dp.push_back(1);

	if (layer > 2) {
		for (int i = 3; i <= layer; i++) {
			vector<long long> temp;
			temp.push_back(dp[i - 1] + 1);
			if (i % 2 == 0) temp.push_back(dp[i / 2] + 1);
			if (i % 3 == 0) temp.push_back(dp[i / 3] + 1);
			dp.push_back(min_method(temp));
		}
	}

	cout << dp[layer] << '\n';
	
	return 0;
}