#include <stdio.h>
#define MAX 1001
int len;
int sightSeeing[MAX];
int height[MAX];
int cmp(int l_index, int r_index) { // 비교해서 큰 높이 인덱스 반환
	if (height[l_index] > height[r_index]) return l_index;
	return r_index;
}
void checkLeft(int target_index, int check_index) {
	if (check_index < 0) return;
	if (height[target_index] <= height[check_index]) {
		sightSeeing[target_index] = -1;
		return;
	}
	sightSeeing[target_index] = height[target_index] - height[check_index];
	return;
}
void checkRight(int target_index, int check_index) {
	if (check_index >= len || height[target_index] == -1) return;
	if (height[target_index] <= height[check_index]) {
		sightSeeing[target_index] = -1;
		return;
	}
	if (sightSeeing[target_index] <= height[target_index] - height[check_index]) return;
	sightSeeing[target_index] = height[target_index] - height[check_index];
	return;
}
int main(void)
{
	int test_case;
	int T;
	
	setbuf(stdout, NULL);
	scanf("%d", &T);
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &len);
		
		scanf("%d", &height[0]);
		scanf("%d", &height[1]);
		for (register int i = 2; i < len; i++) {
			scanf("%d", &height[i]);

			int left_index = cmp(i - 1, i - 2);
			checkLeft(i, left_index);
			if (i <= len - 3) {
				checkRight(i - 2, i);
				checkRight(i - 1, i);
			}
		}
		int res = 0;
		for (register int i = 2; i < len; i++) {
			if (sightSeeing[i] != -1) {
				res += sightSeeing[i];
			}
		}
		printf("#%d %d\n", test_case, res);
	}
	return 0; 
}