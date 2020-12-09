#include <iostream>
#include <utility>

using namespace std;

//Brute Force 적용
int main(void) {
	int num;
	int rank = 1;
	pair<int, int> arr[51];
	cin >> num;
	for(int i = 0; i < num; i++)
		cin >> arr[i].first >> arr[i].second;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if ((arr[i].first < arr[j].first) && (arr[i].second < arr[j].second)) {
				rank++;
			}
		}
		cout << rank << ' ';
		rank = 1;//초기화
	}

	return 0;
}