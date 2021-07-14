#include <iostream>

using namespace std;

int main(void) {
	int n, r;
	int ans(1);
	cin >> n >> r;

	for (int i = 0; i < r; i++) { // 분자
		ans *= (n - i);
	}
	
	for (int i = 1; i <= r; i++) { // 분모
		ans /= i;
	}
	cout << ans;
	return 0;
}