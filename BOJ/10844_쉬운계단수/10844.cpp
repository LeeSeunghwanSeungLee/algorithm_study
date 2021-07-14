#include <iostream>
#define MAX 100 + 1
#define MOD 1000000000

typedef long long ll;
using namespace std;

//전역변수
ll Answer(0);
ll DP[MAX][11];
int main(void){
	int layer;
	cin >> layer;

	DP[1][0] = 0;
	for (int i = 1; i <= 9; i++){
		DP[1][i] = 1;  // 0 제외 1개 추가
	}

	for (int i = 2; i <= layer; i++){
		for(int j = 0; j <= 9; j++){
			if(j == 0) DP[i][j] = DP[i - 1][j + 1] % MOD;
			else if(j == 9) DP[i][j] = DP[i - 1][j - 1] % MOD;
			else DP[i][j] = (DP[i - 1][j - 1] + DP[i - 1][j + 1]) % MOD;
		}
	}

	for (int i = 0; i < 10; i ++){
		Answer = Answer + DP[layer][i];
	}
	cout << Answer % MOD;

	return 0;
}
