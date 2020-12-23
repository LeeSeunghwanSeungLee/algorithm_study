#include <iostream>
#include <algorithm>
using namespace std;

int find_d(int a, int b) {
	int ans(-1);
	for (int i = 1; i <= min(a, b); i++) {
		if (a % i == 0 && b % i == 0) ans = i;
	}
	if (ans == -1) ans = 1;
	return ans;
}
int main(void) {
	int temp, temp_s;
	cin >> temp >> temp_s;

	int defactor = find_d(temp, temp_s);
	cout << defactor << '\n' << temp * temp_s / defactor;

	return 0;
}