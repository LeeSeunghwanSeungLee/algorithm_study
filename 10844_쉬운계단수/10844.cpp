#include <iostream>
#include <vector>



using namespace std;

//전역변수
vector<long long> dp;


int main(void) {
	int num;
	cin >> num;

	dp.push_back(0);
	dp.push_back(9);
	dp.push_back(17);

	if (num > 2) {
		for (int i = 3; i <= num; i++) {
			dp[i] = (dp[i - 1] * 2 - 3) % 1000000000;
		}
	}
	cout << dp[num];
	return 0;
}