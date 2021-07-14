// SW Expert Academy 1767. 프로세서 연결하기
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
 
vector < pair<int, int>> v; // 가장자리를 제외하고 코어가 있는 위치를 저장하는 벡터
int vsz; // 벡터 사이즈
int T, N;
int cans, lans = 0; // 코어의 개수, 전선의 길이
int map[12][12]; // map 배열
int visited[12][12]; // visited 배열
 
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
 
// 시작 인덱스, 전선 길이, 코어 개수, 탐색 횟수
void simulate(int _idx, int line_cnt, int core_cnt, int n)
{
    // 더 탐색해도 저장된 코어 개수만큼 연결할 수 없다.
    if (cans > vsz - n + core_cnt) return;
    // 코어를 모두 탐색했다
    if (n == vsz)
    {
        // 저장된 코어 개수보다 많은 코어를 연결한 경우 갱신
        if (cans < core_cnt)
        {
            cans = core_cnt;
            lans = line_cnt;
        }
        // 저장된 코어 개수와 같고 전선의 길이가 짧은 경우 갱신
        else if (cans == core_cnt)
        {
            if (lans > line_cnt) lans = line_cnt;
        }
        return;
    }
 
    int temp[12][12] = { 0 };
 
    for (int m = 0; m < N; m++)
        for (int n = 0; n < N; n++)
            temp[m][n] = visited[m][n];
 
    for (int j = 0; j < 4; j++)
    {
        bool flag = true;
        int mx = 0;
        int my = 0;
        int cnt = 0;
        int x = v[_idx].first;
        int y = v[_idx].second;
 
        // 네 방향을 탐색하여 map의 끝까지 갈때, 도중에 코어가 있거나 이미 전선이 연결된 경우, false
        // 아닌 경우 true
        while (1)
        {
            mx = x + dx[j];
            my = y + dy[j];
            // 전원 연결!
            if (mx < 0 || mx >= N || my < 0 || my >= N) break;
            // 전원 연결 못함
            if (map[mx][my] == 1 || visited[mx][my] == 1)
            {
                flag = false;
                break;
            }
            visited[mx][my] = 1;
            cnt++;
            x = mx;
            y = my;
        }
        // gogo
        if (flag)
        {
            simulate(_idx + 1, line_cnt + cnt, core_cnt + 1, n + 1);
        }
        // 전선이 연결됐던 경우 visited를 이전의 값으로 되돌리기
        if (cnt != 0)
        {
            for (int m = 0; m < N; m++)
                for (int n = 0; n < N; n++)
                    visited[m][n] = temp[m][n];
        }
    }
    simulate(_idx + 1, line_cnt, core_cnt, n + 1);
 
    return;
}
 
int main(void)
{
    cin >> T;
 
    for (int t = 1; t <= T; t++)
    {
        cans = 0;
        lans = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> map[i][j];
                if (j != 0 && i != 0 && j != N - 1 && i != N - 1)
                {
                    if (map[i][j] == 1)
                    {
                        v.push_back(make_pair(i, j));
                    }
                }
            }
        }
        vsz = (int)v.size();
        simulate(0, 0, 0, 0);
        cout << '#' << t << ' ' << lans << '\n';
        // Test Case가 여러 개 이기 때문에 초기화시켜주는 것이 중요.
        memset(visited, 0, sizeof(visited));
        memset(map, 0, sizeof(map));
        v.clear();
    }
    return 0;
}
