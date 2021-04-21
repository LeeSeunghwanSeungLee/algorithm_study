#define MAX_SIZE 100001
#define MAXLEN 10
typedef unsigned long long ull;
 
ull getHash(char str[]) // 테이블이 따로 존재하지는 않고 그저 숫자형태로 바뀌었을 뿐임.. 겹치지 않는다고 가정한것으로 보임 왜냐하면 str이 10자 이하이기 때문임
{
    int c = 0;
    ull hash = 0;
    while (str[c])
    {
        hash = (hash << 5) | (str[c] - 'a' + 1);
        c++;
    }
    hash = (hash << 5 * (MAXLEN - c));
    return hash;
}
 
struct Node
{
    int idx;
    ull hash;
};
 
Node* heap[MAX_SIZE];
Node heapPool[MAX_SIZE];
int heapSize = 0;
int id;
 
bool comp(const Node* a, const Node* b) {
    if (a->hash > b->hash || (a->hash == b->hash && a->idx < b->idx))
    {
        return true;
    }
    return false;
}
 
void heapInit()
{
    heapSize = 0;
}
 
void heapPush(int p)
{
 
    int current = p;
    while (current > 0 && comp(heap[current], heap[(current - 1) / 2]))
    {
        Node* temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
 
 
}
 
void heapPop(int p)
{
 
    int current = p;
    while (current * 2 + 1 < heapSize)
    {
        int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = comp(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (comp(heap[current], heap[child]))
        {
            break;
        }
 
        Node* temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
        current = child;
    }
}
 
void init() {
    id = 0;
    heapInit();
}
 
void clear() {
    heapInit();
}
 
void push(int idx, char* name) {
    if (heapSize + 1 > MAX_SIZE)
    {
        return;
    }
    ull hash = getHash(name);
    heapPool[id].hash = hash;
    heapPool[id].idx = idx;
    heap[heapSize] = &heapPool[id];
    heapPush(heapSize);
    id++;
    heapSize++;
}
 
int pop() {
    if (heapSize <= 0)
    {
        return -1;
    }
 
    int res = heap[0]->idx;
    heapSize = heapSize - 1;
    heap[0] = heap[heapSize];
    heapPop(0);
    return res;
 
}
 
int top() {
    return heap[0]->idx;
}

// #define MAX_SIZE 100002

// typedef struct _NODE{
//     char* name;
//     int idx;
//     _NODE* left;
//     _NODE* right;
// }NODE;

// NODE* Head; 
// NODE* Tail;
// NODE ALOC_LIST[MAX_SIZE];
// int size = 0;

// NODE* myalloc(){
//     return &ALOC_LIST[size++];
// }

// void init(){
//     size = 0;
//     Head = myalloc();
//     Tail = myalloc();
// }

// void push(int idx, char* name){
//     // idx와 name이 주어지는 Data를 저장한다.
//     NODE* n_node = myalloc();
//     for(register int i = 0; i < 10; i++){
//         if(name[i] == '\0') break;
//         n_node -> name[i] = name[i];
//     }
//     n_node -> idx = idx;

//     //root 노드부터 시작해서 내려간다..
// }

// int pop(){
//     // 1. name이 사전 순으로 큰 Data

//     // 2. name이 같은 경우 idx가 작은 Data를 삭제하고 idx를 반환한다. 

//     // Returns

//     // idx : 삭제한 Data의 idx
// }

// int top(){
//     // 1. name이 사전 순으로 큰 Data

//     // 2. name이 같은 경우 idx가 작은 Data의 idx를 반환한다. 

 

//     // Returns

//     // idx : 반환하는 Data의 idx
// }



// // 전략
// // 1. 링크드리스트로 맥스힘을 구현한다
// // 2. push와 pop 이 대부분이므로 nlogn 이내에서 끝낼 수 있음