#include <iostream>
#include <vector>
#include <algorithm>
#define max 100001


int N,M,result;


using namespace std;


int parent[max];
vector <pair<int,pair<int,int>>> adj;


int find(int node){
    if(parent[node] == node){return node;}
    else{return parent[node] = find(parent[node]);}
}
void Union(int x,int y){
    x = find(x);
    y = find(y);
    if(x != y){parent[y] = x;}
}
bool solve(int x,int y){
    x = find(x);
    y = find(y);
    if(x ==y){return true;}
    else{return false;}
}
int main(void){
    cin >> N >> M;
    for(int i = 0;i<M;i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj.push_back(make_pair(c,make_pair(a,b))); // 가중치, 노드_1, 노드_2
    }
    sort(adj.begin(),adj.end()); // 가중치, a, b 순서대로 오름차순으로 정렬하게 됨
    for(int i = 1;i <= N; i++) {parent[i] = i;}
    for(int i = 0;i<M;i++){
        if(solve(adj[i].second.first,adj[i].second.second) == false){ //연결이 안되어있으면
            Union(adj[i].second.first,adj[i].second.second);
            result = result+adj[i].first;
        }
    }
    cout << result << '\n';
}