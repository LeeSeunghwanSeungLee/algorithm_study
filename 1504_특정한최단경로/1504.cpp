#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX 987654321

using namespace std;

int V, E, N_1, N_2;
vector<vector<pair<int, int>>> GRAPH;
int ANS(MAX);

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}
void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E;
    for(int i = 0; i <= V; i++){
        vector<pair<int, int>> temp(1, make_pair(0, 0));
        GRAPH.push_back(temp);
    }
    for(int i = 0; i < E; i++){
        int temp_1, temp_2, temp_dis;
        cin >> temp_1 >> temp_2 >> temp_dis;
        GRAPH[temp_1].push_back(make_pair(temp_dis, temp_2));
        GRAPH[temp_2].push_back(make_pair(temp_dis, temp_1));
    }
    for(int i = 1; i <= V; i++){
        sort(GRAPH[i].begin(), GRAPH[i].end(), cmp); 
    }
    cin >> N_1 >> N_2;
}

void solve(){
    priority_queue<pair<pair<int, int>, pair<int, int>>> pq;
    pq.push(make_pair(make_pair(0, 1), make_pair(0, 0)));
    while(!pq.empty()){
        pair<pair<int, int>, pair<int, int>> now = pq.top();
        int total_dist = now.first.first, now_node = now.first.second;
        int check_N_1 = now.second.first, check_N_2 = now.second.second;
        pq.pop();
        //정답지확인
        if(check_N_1 != 0 && check_N_2 != 0 && now_node == V) {
            ANS = min(ANS, total_dist);
            continue;
        }
        if(total_dist > ANS) continue;
        if(check_N_1 >= 3 || check_N_2 >= 3) continue;
        if(now_node == N_1) check_N_1++;
        else if(now_node == N_2) check_N_2++;
        for(int i = 1; i < GRAPH[now_node].size(); i++){
            int next_node = GRAPH[now_node][i].second, next_dist = GRAPH[now_node][i].first + total_dist;
            if(next_dist > ANS) continue;
            pq.push(make_pair(make_pair(next_dist, next_node), make_pair(check_N_1, check_N_2)));
        }
    }
}


int main(void){
    init();
    solve();
    cout << '3' << '\n';
    if(ANS == MAX) cout << -1;
    else cout << ANS;

    return 0;
}