#include <iostream>


using namespace std;

//전역변수
int arr[1000001] = { 0, };
int N;//length

void pre_Scan() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

void swap(int* a, int* b) {// 두 숫자를 바꾼다
	int temp = *a;
	*a = *b;
	*b = temp;
}

void act_Sort(int start, int end) {
	if (start >= end) return;//원소가 1개이면 종료시킨다

	int pivot = start;
	int i = pivot + 1; // 왼쪽 출발 지점
	int j = end; // 오른쪽 출발지점

	int temp;

	while (i <= j) {//포인터가 엇갈릴때까지 반복한다
		while (i <= end && (arr[i] <= arr[pivot])) {
			i++;
		}
		while (j > start&& arr[j] >= arr[pivot]) {
			j--;
		}

		if (i > j) swap(arr + pivot, arr + j);
		else swap(arr + i, arr + j);
	}

	//재귀
	act_Sort(start, j - 1);
	act_Sort(j + 1, end);



}

int main(void) {
	pre_Scan();
	act_Sort(0, N-1);
	for (int i = 0; i < N; i++) {
		cout << arr[i] << '\n';
	}
	return 0;
}