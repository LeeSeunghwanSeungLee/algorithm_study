// DFS 또한 탐색 알고리즘 중 하나이다
// 특징은 아래와 같다

// 1. 스택이나 재귀함수를 통해서 구현한다
// 2. BFS와 같이 미로찾기 등 완전탐색을 이용한다
// 3. 예제 코드는 아래와 같다

void DFS(int start){
    //기저조건
    if(visit[start]){
        return;
    }

    //End 조건
    if(cnt >= boundary){
        return;
    }

    print("%d", start);
    for(int i = 0; i < a[start].size(); i++){
        int x = a[start][i];
        dfs(x);
    }
}