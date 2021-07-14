#include <iostream>
#include <queue>
#include <tuple>
#define INF 1000000000

using namespace std;

int graph[101][101] = {0};
queue<tuple<int, int, int>> q_;

int main(void){
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) graph[i][j] = 0;
            else{
                graph[i][j] = INF;
            }
        }
    }
    
    for(int i = 0; i < m; i++){
        int temp_1, temp_2, temp_3;
        cin >> temp_1 >> temp_2 >> temp_3;
        if(graph[temp_1][temp_2] > temp_3){
            graph[temp_1][temp_2] = temp_3;
        }
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <=n; j++){
                if(i ==j) continue;
                if(graph[i][k] != 0 && graph[k][j] != 0){
                    if(graph[i][k] + graph[k][j] < graph[i][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(graph[i][j] == INF){
                cout << '0' << ' ';
            }
            else{
                cout << graph[i][j] << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}


