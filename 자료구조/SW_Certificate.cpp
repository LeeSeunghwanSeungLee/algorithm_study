// 1. 문자열 체크할때는 => %s 를 이용한다

// 2. dfs 이용
int boundary;
void dfs(int depth){
    if(depth >= boundary) return; // 종료한다

    for(int i = 0; i < 4; i++){
        //만일 이동햇던 방향 플래그이면 continue;


        //이동하려고 하는방향 플래그 체크
        //dfs(depth + 1);
        //이동하려고 하는 방향 플레그 체크
    }
    return;
}

// 3. bfs 
void bfs(){
    // 시작값 세팅
    // 큐에 담는다
    
    //while(q존재){
        // 현재 위치를 큐에서 꺼낸다
        // 플래그에 표시한다
        // for(int i = 0; i < 4; i++){
            // 다음 위치를 계산한다
            // 만일 기존에 갓던 방향향이면 컨티뉴
            // 아니라면 큐에 담는다
        //}
    //}
}

// 4. heap

struct Test{
    int key;
    int value;
    bool operator<(Test &l){
        if (key != l.key) return key < l.key;
        else return value < l.value;
    }
};

Test heap[1000];
void push(Test* node){
    //만일 제한범위를 넘어서면 리턴

    //마지막항에 추가한다
    int curr = boundary; 
    while(curr > 0 && heap[curr] < heap[(curr - 1) / 2]){
        //swap
        // curr = (curr - 1) / 2;
    }
    boundary++;
}

void pop(){

}
void update(int i){ // pop 과 동일한 작업임

}

// 5. 해쉬

 unsigned long hash(char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }


// 6. 머지소팅
void mergesort(int left, int right){
	if(left < right){
		int mid = (left + right) >> 1;
		mergesort(left, mid);
		mergesort(mid + 1, right);

		int i = left;
		int j = mid + 1;
		int k = left;
		while( i <= mid && j <= right){
			if(arr[i] < arr[j])
				arr2[k++] = arr[i++];
			else
				arr2[k++] = arr[j++];
		}

		int tmp = (i > mid) ? j : i;
		while(k <= right) arr2[k++] = arr[tmp++];

		for(register int i = left; i <= right; i++){
			arr[i] = arr2[i];
		}
	}
}

