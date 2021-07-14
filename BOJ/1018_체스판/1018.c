#include <iostream>
#include <stdio.h>

#define MAX 2147483647

using namespace std;
//전역변수
int N, M;
char** arr;
int ans = MAX;

//함수
void draw_ChessBoard(){ 
	cin >> N >> M;
	arr = new char* [N];
	for (int i = 0; i < N; i++) {
		arr[i] = new char[M];
	}

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			cin >> arr[j][i];
		}
	}
}

int cal_Number(int row, int col) {
	if (row + 7 > N || col + 7 > M) return MAX;
	char start = arr[row][col];
	int cnt = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {//짝수이면
				if (start != arr[row +i][col + j]) cnt++;
			}
			else {//홀수이면
				if (start == arr[row + i][col + j]) cnt++;
			}
		}
	}
	return cnt;
	
}

void main_Process() {
	int temp;
	for (int i = 0; i <= N - 8; i++) {
		for (int j = 0; j <= M -8; j++) {
			temp = cal_Number(i, j);
			if (temp < ans) ans = temp;
		}
	}
	printf("%d", ans);
	for (int i = 0; i < N; i++) {
		delete arr[i];
	}
	delete arr;
}



int main(void) {
	draw_ChessBoard();
	main_Process();
	return 0;
}