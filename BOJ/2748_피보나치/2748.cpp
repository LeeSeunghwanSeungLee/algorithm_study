#include <iostream>

using namespace std;

//동적 계획법 배열
long long dp[92] = { 0, 1, };

//함수
long long fibo(int num) {
	if(num == 0) return dp[0];
	if (dp[num] != 0) return dp[num];
	if (dp[num] == 0) {
		dp[num] = fibo(num - 1) + fibo(num - 2);
	}
	return dp[num];
}


int main(void) {

	int len;
	cin >> len;
    long long ans = fibo(len);
	cout << ans << '\n';


	return 0;
}

// 자료형 굉장히 중요하다!! 