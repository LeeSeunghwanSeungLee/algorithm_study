#include <iostream>
#include <stdio.h>
#include <string>


using namespace std;
//전역변수
int num_tray[1001];//숫자를 담을 배열
int N;
//함수
void pre_Scann() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num_tray[i];
	}
}

void swap(int* a, int* b) {//위치 바꾸기
	int temp = *a;
	*a = *b;
	*b = temp;
}

void act_Sort() {//bubble sort
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j <= i ; j++) {
			if (num_tray[j] > num_tray[j + 1]) swap(num_tray + j, num_tray + j + 1);
		}
	}
}

void final_Print() {
	for (int i = 0; i < N; i++) {
		if (num_tray[i] == num_tray[i + 1]) continue;
		cout << num_tray[i] << "\n";
	}
}

int main(void) {
	pre_Scann();
	act_Sort();
	final_Print();
	return 0;
}