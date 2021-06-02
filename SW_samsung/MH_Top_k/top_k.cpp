#define ll long long
#define MAX_LEN 100002
#define SEMI_LEN 320
#define NULL 0

typedef struct _Node{
    ll key = -1;
    int value = -1;
    _Node* next = NULL;
    _Node* prev = NULL;
}Node;


// 메모리 풀
Node node_pool[MAX_LEN];
int now_idx(0);

Node* allocatePool(){
    return &node_pool[now_idx++];
}

// 링크드 리스트 
Node* head[SEMI_LEN];
Node* tail[SEMI_LEN];
int nodePoolLen[SEMI_LEN];

// Top Rank 를 계산하기 위한 자료구조
int TOP[10] = {0,};

void init(){
    now_idx = 0;
    for(register int i = 0; i < 10; i++){
        TOP[i] = 0;
    }
    for(register int i = 0; i < SEMI_LEN; i++){
        head[i] = allocatePool();
        tail[i] = allocatePool();
        head[i] -> next = tail[i];
        tail[i] -> prev = head[i];
        nodePoolLen[i] = 0;
    }
}

void insertNode(int row, Node* new_node){
    Node* target = head[row] -> next;
    while(target -> key < new_node -> key && target -> next!= tail[row]){
        target = target -> next;
    }
    new_node -> next = target -> next;
    new_node -> prev = target;
    target -> next -> prev = new_node;
    target -> next = new_node;
}
void overInsert(int row){
    Node* target;
    if(nodePoolLen[row] > SEMI_LEN){
        target = tail[row] -> prev;
        tail[row]-> prev = target -> prev;
        target -> prev -> next = tail[row];
        row++;
        insertNode(row, target);
        nodePoolLen[row]++;
        overInsert(row);
    }
}
void push(int key, int value){
    Node* new_node = allocatePool();
    new_node -> key = key;
    new_node -> value = value;

    if(now_idx <= 10){
        TOP[now_idx] = value;
    }
    else{
        int min = 10001;
        int idx = 0;
        for(register int i = 0; i < 10; i++){
            if(min > TOP[i]){
                idx = i;
                min = TOP[i];
            }
        }
        TOP[idx] = value;
    }
    // 삽입
    register int i = 0;
    while(nodePoolLen[i] >= SEMI_LEN && tail[i] -> prev -> key < key){
        i++;
    }
    insertNode(i, new_node);
    nodePoolLen[i]++;
    overInsert(i);
}



int top(int K){
  //TODO
}

void deleteNode(int row, Node* target){
    target -> prev -> next = target -> next;
    target -> next -> prev = target -> prev;
}

void overDelete(int row){
    if(nodePoolLen[row] < SEMI_LEN && nodePoolLen[row + 1] > 0){
        Node* target = head[row + 1] -> next;
        deleteNode(row + 1, target);
        nodePoolLen[row + 1]--;
        insertNode(row, target);
        nodePoolLen[row]++;
        overDelete(row + 1);
    }
}

void erase(int key){
    for(register int i = 0; i < SEMI_LEN; i++){
        if(tail[i] -> prev -> key < key) continue;

        Node* target = head[i] -> next;
        while(target -> key != key){
            target = target -> next;
        }
        deleteNode(i, target);
        nodePoolLen[i]--;
        overDelete(i);
        break;
    }
}

void modify(int key, int value){
    register int i;
    for(i = 0; i < SEMI_LEN;){
        if(head[i] -> next -> key <= key && tail[i] -> prev -> key >= key) break;
        i++;
    }
    Node* target = head[i] -> next;
    while(target != tail[i]){
        if(target -> key != key){
            target = target -> next;
            continue;
        }
        target -> value = value;
        return;
    }
}