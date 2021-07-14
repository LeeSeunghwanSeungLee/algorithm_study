#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> human;
int main(void) {
	int num;
	int ans(0);

	cin >> num;
	for (int i = 0; i < num; i++) {
		int temp;
		cin >> temp;
		human.push_back(temp);
	}

	sort(human.begin(), human.end()); // 오름차순으로 정렬
	int boudary = human.size();
	for (int i = boudary; i > 0; i--) {
		ans += i * human[boudary - i];
	}
	cout << ans;
	return 0;
}