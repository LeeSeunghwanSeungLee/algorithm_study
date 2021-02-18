#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX 987654321

using namespace std;

int V, E, N_1, N_2;
vector<vector<pair<int, int>>> GRAPH;
vector<int> PARENTS;
int ANS(MAX);


void init(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E;
    for(int i = 0; i <= V; i++){
        vector<pair<int, int>> temp(1, make_pair(0, 0));
        GRAPH.push_back(temp);
        PARENTS[i] = i; 
    }
    for(int i = 0; i < E; i++){
        int temp_1, temp_2, temp_dis;
        cin >> temp_1 >> temp_2 >> temp_dis;
        GRAPH[temp_1].push_back(make_pair(temp_dis, temp_2));
        GRAPH[temp_2].push_back(make_pair(temp_dis, temp_1));
    }
    for(int i = 1; i <= V; i++){
        sort(GRAPH[i].begin(), GRAPH[i].end()); 
    }
    cin >> N_1 >> N_2;
}

void solve(){
    priority_queue<pair<pair<int, int>, pair<bool, bool>>> pq;
    pq.push(make_pair(make_pair(0, 1), make_pair(0, 0)));
    while(!pq.empty()){
        pair<pair<int, int>, pair<bool, bool>> now = pq.top();
        int total_dist = now.first.first, now_node = now.first.second;
        bool check_N_1 = now.second.first, check_N_2 = now.second.second;
        pq.pop();
        //정답지확인
        if(check_N_1 == true && check_N_2 == true && now_node == V) {
            ANS = min(ANS, total_dist);
            continue;
        }
        if(total_dist > ANS) continue;
        if(now_node == N_1) check_N_1 = true;
        else if(now_node == N_2) check_N_2 = true;
        for(int i = 1; i < GRAPH[now_node].size(); i++){
            int next_node = GRAPH[now_node][i].second, next_dist = GRAPH[now_node][i].first + total_dist;
            if(next_dist > ANS) continue;
            pq.push(make_pair(make_pair(next_dist, next_node), make_pair(check_N_1, check_N_2)));
        }
    }
}


int main(void){
    init();
    cout << '2' << '\n';
    // solve();
    // cout << '3' << '\n';
    // if(ANS == MAX) cout << -1;
    // else cout << ANS;
    return 0;
}