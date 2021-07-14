#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

void init();
void push(int key, int value);
int top(int K);
void erase(int key);
void modify(int key, int value);

#define CMD_PUSH	100
#define CMD_TOP		200
#define CMD_ERASE	300
#define CMD_MODIFY	400

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
	setbuf(stdout, NULL);
	int T, N;
	int cmd, ret;
	int key, value, K;

	scanf("%d", &T);
	for (int TC = 1; TC <= T; TC++) {
		init();
		int score = 100;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &cmd);

			switch (cmd) {
			case CMD_PUSH:
				scanf("%d %d", &key, &value);
				push(key, value);
				break;

			case CMD_TOP:
				int ans;
				scanf("%d %d", &ans, &K);
				ret = top(K);

				if (ret != ans) score = 0;
				break;

			case CMD_ERASE:
				scanf("%d", &key);
				erase(key);
				break;

			case CMD_MODIFY:
				scanf("%d %d", &key, &value);
				modify(key, value);
				break;
			}
		}
		printf("#%d %d\n", TC, score);
	}
	return 0;
}

#define MAX_LEN 100001
#define HASH_LEN 10007

struct node{
    int key;
    int value;
    int hId;
    node* next;
}NODE[MAX_LEN];
int nodeId(0);

node* alloc(int key, int value){
    NODE[nodeId].key = key;
    NODE[nodeId].value = value;
    NODE[nodeId].hId = 0;
    NODE[nodeId].next = 0;
    return &NODE[nodeId++];
}

int hashing(int key){
    return key % HASH_LEN;
}
node* HASH_TABLE[HASH_LEN];

node* getNode(int key){
    int row = hashing(key);
    node* curr = HASH_TABLE[row] -> next;
    while(curr){
        if(curr -> key == key) break;
        curr = curr -> next;
    }
    return curr;
}
node* getBeforeNode(int key){
    int row = hashing(key);
    node* curr = HASH_TABLE[row];
    while(curr){
        if(curr -> next -> key == key) break;
        curr = curr -> next;
    }
    return curr;
}
node* HEAP[MAX_LEN];
int heapId(0);


void pushHeap(node* newNode){
    HEAP[heapId] = newNode;
    newNode -> hId = heapId;
    heapId++;
    int curr = heapId - 1;
    while(curr != 0){
        if(HEAP[curr] -> value <= HEAP[(curr - 1) / 2] -> value) break;

        int aTemp = HEAP[curr] -> hId;
        HEAP[curr] -> hId = HEAP[(curr - 1) / 2] -> hId;
        HEAP[(curr - 1) / 2] -> hId = aTemp;

        node* aTempNode = HEAP[curr];
        HEAP[curr] = HEAP[(curr - 1) / 2];
        HEAP[(curr - 1) / 2] = aTempNode;
        curr = (curr - 1) / 2;
    }
    return;
}
void updateHeap(int index){
    if(index != 0 && HEAP[index] -> value > HEAP[(index - 1) / 2] -> value){ // 위로 올라가야하는경우
        while(index != 0){
            if(HEAP[index] -> value <= HEAP[(index - 1) / 2] -> value) break;

            int aTemp = HEAP[index] -> hId;
            HEAP[index] -> hId = HEAP[(index - 1) / 2] -> hId;
            HEAP[(index - 1) / 2] -> hId = aTemp;

            node* aTempNode = HEAP[index];
            HEAP[index] = HEAP[(index - 1) / 2];
            HEAP[(index - 1) / 2] = aTempNode;
            index = (index - 1) / 2;
        }
    }
    else{
        while(index * 2 + 1 < heapId){ // 아래로 내려가야하는경우
            int child;
            if(index * 2 + 2 == heapId) child = index * 2 + 1;
            else child = (HEAP[index * 2 + 1] -> value < HEAP[index * 2 + 2] -> value)? index * 2 + 2 : index * 2 + 1;
            
            if(HEAP[index] -> value >= HEAP[child] -> value) break;

            int aTemp = HEAP[index] -> hId;
            HEAP[index] -> hId = HEAP[child] -> hId;
            HEAP[child] -> hId = aTemp;

            node* aTempNode = HEAP[index];
            HEAP[index] = HEAP[child];
            HEAP[child] = aTempNode;
            
            index = child;
        }
    }
    return;
}

node* pop(int index){
    node* res = HEAP[index];

    heapId--;
    HEAP[index] = HEAP[heapId];
    HEAP[index] -> hId = index;

    updateHeap(index);
    return res;
}

void init(){
    nodeId = 0;
    heapId = 0;
    for(int i = 0; i < HASH_LEN; i++) {
        HASH_TABLE[i] = alloc(0, 0);
    }
}

void push(int key, int value){
    node* newNode = alloc(key, value);
    // 해시 링리에 넣는다
    int row = hashing(key);
    newNode -> next = HASH_TABLE[row] -> next;
    HASH_TABLE[row] -> next = newNode;
    // 힙에 넣는다
    pushHeap(newNode);
}
int top(int k){
    int res = 0;
    node* pocket[k];
    for(int i = 0; i < k; i++){
        pocket[i] = pop(0);
        res += pocket[i] -> value;
    }
    for(int i = 0; i < k; i++) pushHeap(pocket[i]);
    return res;
}
void erase(int key){
    node* aBeforeTarget = getBeforeNode(key);
    //힙에서 제거
    pop(aBeforeTarget -> next -> hId);
    //링크드 리스트에서 제거
    aBeforeTarget -> next = aBeforeTarget -> next -> next;
}
void modify(int key, int value){
    node* aTarget = getNode(key);
    aTarget -> value = value;
    updateHeap(aTarget -> hId);
    return;
}