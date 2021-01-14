#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321

using namespace std;

vector<pair<int, int>> GRAPH[20001];


int main(void){
    // 입력받는다
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int v, e, start;
    cin >> v >> e >> start;

    int fr, to, w;
    for(int i = 0; i < e; i++){
        cin >> fr >> to >> w;
        GRAPH[fr].push_back(make_pair(to, w));
    }

    //다익스트라 알고리즘
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, start));
    vector<int> d(v + 1, INF);
    d[start] = 0;

    while(!pq.empty()){
        pair<int, int> cur = pq.top();
        int cur_distance = - cur.first;
        int cur_index = cur.second;
        pq.pop();

        if(cur_distance > d[cur_index]){
            continue;
        }

        for(int i = 0; i < GRAPH[cur_index].size(); i++){
            int next_distance = GRAPH[cur_index][i].first;
            int next_index = GRAPH[cur_index][i].second;
            if(next_distance + cur_distance < d[next_index]){
                d[next_index] = next_distance + cur_distance;
                pq.push(make_pair(-d[next_index], next_index));
            }
        }
    }
    
}