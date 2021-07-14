
#include <iostream>

using namespace std;


int N;
int SERIES[21];
int ans;

bool cmp(int a, int b, int c){
    if(a > b && a > c) return false;
    else if(a < b && a < c) return false;
    return true;
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
	int T;
	
    cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case)
	{
        ans = 0;
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> SERIES[i];
            if (i < 2) continue;
            
            int check_point = SERIES[i - 1];
            int cmp_1 = SERIES[i - 2];
            int cmp_2 = SERIES[i];
            if (cmp(check_point, cmp_1, cmp_2))
            {
                ans++;
            }
        }
        cout << '#' << test_case << ' ' <<  ans << '\n';
	}
	return 0; 
}