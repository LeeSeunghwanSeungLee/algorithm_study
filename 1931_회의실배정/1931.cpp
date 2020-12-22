#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//전역변수
vector<pair<int, int>> meeting;
int ans;

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (b.second != a.second) return a.second < b.second;

	return a.first <= b.first;
}


int main(void) {
	int cnt;
	cin >> cnt;
	for (int i = 0; i < cnt; i++) { // 회의실을 입력받는다
		pair<int, int> temp;
		cin >> temp.first >> temp.second;
		meeting.push_back(temp);
	}

	sort(meeting.begin(), meeting.end(), cmp);

	
	//첫번째
	ans++; // 무조건 1번째를 사용한다
	int p = 0; // 첫번째를 가리킨다

	for (int idx = 1; idx < cnt; idx++) {
		if (meeting[idx].first >= meeting[p].second) {
			p = idx;
			ans++;
		}
	}
	cout << ans;

	return 0;
}