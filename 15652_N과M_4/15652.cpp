#include <iostream>
#include <vector>


using namespace std;

//전역변수
int N, M;
vector<int> ans;

void act_Recur(int depth, int boundary, int num_init, int num_boundary) {
    if (depth >= boundary) {
        for (int i = 0; i < boundary; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for (int i = num_init; i <= num_boundary; i++) {
        ans.push_back(i);
        act_Recur(depth + 1, boundary, i,num_boundary);
        ans.pop_back();
    }
}


int main(void) {
    //N 과 M을 입력받는다
    cin >> N >> M;
    act_Recur(0, M, 1, N);

    return 0;
}