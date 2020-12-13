#include <iostream>
#include <vector>

using namespace std;

//전역변수
vector<int> ans_v;
int N;//length

void pre_Scan() {
	cin >> N;
	for (int i = 0; i < N; i++) {
        int temp;
		cin >> temp;
        ans_v.push_back(temp);
	}
}

int main(void) {
	pre_Scan();
    sort(ans_v.begin(), ans_v.end());
	for (int i = 0; i < N; i++) {
		cout << ans_v[i] << '\n';
	}
	return 0;
}