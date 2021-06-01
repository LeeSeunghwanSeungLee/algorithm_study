// 1. 전체 메모리는 100002 으로 선정한다
// 2. 구조체에는 key, value 형태로 저장한다
// 3. 2차원 메트릭스로 저장하고 key 를 형태로 링크드 리스트 형태로 저장한다 !! 중요
// 4. top 10 링크드 리스트로 key, value 를 저장한다
// 5. 

//수도코드
#define MAX_LEN 1000002
#define SEMI_LEN sqrt(MAX_LEN)
#define TOP_LEN 10

typedef struct _Node{
    int key;
    int value;
    _Node* next;
    _Node* prev;
}Node;


Node node_pool[MAX_LEN];
int now_idx(0);

Node* head[SEMI_LEN];
Node* tail[SEMI_LEN];
int nodePoolLen[SEMI_LEN];

Node* rank[TOP_LEN];
Node* allocatePool(){
    return &node_pool[now_idx++];
}



void init(){
    now_idx = 0;
    for(register int i = 0; i < SEMI_LEN; i++){
        head[i] = allocatePool();
        tail[i] = allocatePool();
        nodePoolLen[i] = 0;
    }
}

void insertNode(){

}

void insertTotal(){

}

void push(int key, int value){

}

int top(int K){
    int res = 0;
    for(register int i = 0; i < K; i++){
        res += rank[i] -> value;
    }
    return res;
}

void erase(int key){

}

void modify(int key, int value){

}
