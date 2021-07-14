#include<iostream>

using namespace std;

int ans;
char TEXT[21]; 
char REAL_TEXT[21];
char text_sort[21]; 
char dfs_sort[21];
bool CHECK[21];
int length;
void _msort(int l, int r, char* a) {
    if (l < r) {
        int m = (l + r) >> 1;
        int i = l, j = m + 1, k = l, u;
        _msort(l, m, a);
        _msort(m + 1, r, a);
        
        while (i <= m && j <= r) {
            if (a[i] <= a[j])
                text_sort[k++] = a[i++];
            else
                text_sort[k++] = a[j++];
        }
        if (i > m) {
            for (u = j; u <= r; u++)
                text_sort[k++] = a[u];
        }
        else {
            for (u = i; u <= m; u++)
                text_sort[k++] = a[u];
        }
        for (u = l; u <= r; u++)
			TEXT[u] = text_sort[u];
    }
}

void DFS(int depth){
    if(depth >= length){
        for(int i = 0; i < length; i++){
            cout << dfs_sort[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for(int i = 0; i < length ; i++){
        if(CHECK[i] == true) continue;
        CHECK[i] = true;
        dfs_sort[depth] = TEXT[i];
        DFS(depth + 1);
        CHECK[i] = false;
    }
}


void resetArray(){
    ans = 0;
    for(int i = 0; i < 21; i++){
        TEXT[i] = '\0';
        text_sort[i] = '\0';
    }
}


int main(int argc, char** argv)
{
	int T;
	cin>>T;

	for(int test_case = 1; test_case <= T; ++test_case)
	{
        resetArray();
        cin >> TEXT;
        for(int j = 0; j < 21; j++){
            if(TEXT[j] == '\0'){
                length = j;
                break;
            }
            REAL_TEXT[j] = TEXT[j];
        }
        _msort(0, length - 1, TEXT);
        DFS(0);
        //cout << '#' << test_case << ' ' << ans << '\n';
	}
	return 0;
}


//개선사항

// 1. 바나나의 경우 중복을 어떻게 고려할것인지 확인해봐야함