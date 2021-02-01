#include <iostream>
#include <deque>
#include <queue>
using namespace std;

struct belt {
	int count = 0;
	bool isRobot = false;
};

bool is_done(deque<belt>& belts, int k) {
	int tmp = 0;
	for (auto belt : belts) {
		if (belt.count == 0) tmp++;
	}
	if (tmp >= k) return true;
	else return false;
}

void rotate_belt(deque<belt>& belts) {
	belts[(belts.size() / 2) - 1].isRobot = false;
	belts.push_front(belts.back());
	belts.pop_back();
}

void move_robots(deque<belt>& belts) {
	for (int i = (belts.size() / 2) - 1; i >= 0; i--) {
		if (i == (belts.size() / 2) - 1) {
			belts[i].isRobot = false;
		}
		else if(i==0){
			if (belts[i].isRobot && !belts[i + 1].isRobot && belts[i + 1].count > 0) {
				belts[i].isRobot = false;
				belts[i + 1].isRobot = true;
				belts[i + 1].count--;
			}

			if (!belts[i].isRobot && belts[i].count > 0) {
				belts[i].isRobot = true;
				belts[i].count--;
			}
		}
		else {
			if (belts[i].isRobot && !belts[i + 1].isRobot && belts[i + 1].count > 0) {
				belts[i].isRobot = false;
				belts[i+1].isRobot = true;
				belts[i+1].count--;
			}
		}
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	deque<belt> belts(2 * n);
	int answer = 1;

	//로봇 내구도 설정
	for (int i = 0; i < 2 * n; i++) {
		cin >> belts[i].count;
	}

	//이동
	while (1) {
		rotate_belt(belts);
		move_robots(belts);
		if (is_done(belts, k)) break;
		answer++;
	}
	cout << answer;
}
