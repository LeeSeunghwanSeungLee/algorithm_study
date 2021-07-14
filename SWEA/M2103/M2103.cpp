#include <iostream>
using namespace std;


pair<int, int> ANS;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

	int T;
    cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case)
	{
        char tmp[31] = {0, };
        cin >> tmp;
        ANS = make_pair(1, 1);
        for(int i = 0; i < 31; i++){
            if((int)tmp[i] == 0) break;
            pair<int, int> now = ANS;
            if(tmp[i] == 'L'){
                ANS.first = now.first;
                ANS.second = now.first + now.second;
            }
            else {
                ANS.first = now.first + now.second;
                ANS.second = now.second;
            }
        }
        cout << "#" << test_case << " " << ANS.first << ' ' << ANS.second << '\n'; 
	}
