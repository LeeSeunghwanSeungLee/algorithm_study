// BFS는 너비를 우선해서 탐색하는 알고리즘
// 특징은 아래와 같음

// 1. 최단경로를 찾을 수 있다
// 2. 응용하면 미로찾기와 같은 알고리즘도 구현할 수 있다
// 3. 큐를 이용한다

// 알고리즘은 다음과 같음

// 1. 큐 생성
// 2. 큐가 비워질떄까지 무한루프를 돌린다
// 3. 큐에서 처음 자료를 꺼낸다
// 4. 미로찾기 등,, 내가 원하는 작업을 진행하고, 큐에 추가한다
// 5. 비워져있다면 특정 조건을 진행하거나 또는 1로 돌아간다


#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int number = 9;
int visit[9];
vector<int> a[10];

void BFS(int start){
    queue<int> q;
    q.push(start);
    visit[start] = true;

    while(!q.empty()){ // FIFO 구조인 큐가 비워질떄까지 진행된다
        int x = q.front();
        q.pop();

        printf("%d", x);
        for(int i = 0; i < a[x].size(); i++){
            int y = a[x][i];
            if(!visit[y]){
                q.push(y);
                visit[y] = true;
            }
        }
    }
}

