#include <iostream>
#include <vector>

using namespace std;

//전역
vector<vector<int>> paper;
int paper_size;
int white;
int blue;

bool check_paper(int start_row, int start_col, int len) {
	for (int i = start_row; i < start_row + len; i++) {
		for (int j = start_col; j < start_col + len; j++) {
			if (paper[i][j] != paper[start_row][start_col]) {
				return false;
			}
			else {
				continue;
			}
		}
	}
	if (paper[start_row][start_col] == 0)  white++;
	else if (paper[start_row][start_col] == 1) blue++;
	return true;
}

void divide_con(int start_row, int start_col, int len) {
	if (len == 1) { // 1칸만 남았을때
		bool temppp = check_paper(start_row, start_col, len);
		return;
	}
	else {
		if (check_paper(start_row, start_col, len)) return;
		else {
			len /= 2;
			divide_con(start_row, start_col, len);
			divide_con(start_row, start_col + len, len);
			divide_con(start_row + len, start_col, len);
			divide_con(start_row + len, start_col + len, len);
			return;
		}
	}
}

int main(void) {
	cin >> paper_size;
	
	for (int i = 0; i < paper_size; i++) { //색종이표시
		vector<int> temp;
		for (int j = 0; j < paper_size; j++) {
			int tempp;
			cin >> tempp;
			temp.push_back(tempp);
		}
		paper.push_back(temp);
	}

	divide_con(0, 0, paper_size);
	cout << white << '\n' << blue;

	return 0;
}