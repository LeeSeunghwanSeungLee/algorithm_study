#define MAX_SIZE 100001
#define MAX_LEN 10


typedef unsigned long long ull;

ull getHash(char str[]){
    int c = 0;
    ull result = 0;
    while(str[c]){
        result = (result << 5) | (str[c] - 'a' + 1);
        c++;
    }
    return (result << 5) * (MAX_LEN - c);
}

struct Node{
    int idx;
    ull hash;
};

Node* HEAP[MAX_SIZE];
Node HEAP_POOL[MAX_SIZE];
int heapsize = 0;
int id = 0;
bool findPosFlag = false;

bool comp(const Node* a, const Node* b){
    if(a -> hash > b -> hash || ((a -> hash == b -> hash) && (a -> idx < b -> idx))){
        return true;
    }
    return false;
}
void pushHeap(int p){
    int current = p;
    while(current > 0 && comp(HEAP[current], HEAP[(current - 1) / 2])){
        Node* temp = HEAP[(current - 1) / 2];
        HEAP[(current - 1) / 2] = HEAP[current];
        HEAP[current] = temp;
        current = (current - 1) / 2;
    }   
}

void popHeap(){
    int current = 0;
    while(current * 2 + 1 < heapsize){
        int child;
        if(current * 2 + 2 == heapsize){
            child = current * 2 + 1;
        }
        else{
            child = comp(HEAP[current * 2 + 1], HEAP[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }

        if(comp(HEAP[current], HEAP[child])){
            break;
        }
        Node* temp = HEAP[current];
        HEAP[current] = HEAP[child];
        HEAP[child] = temp;
        current = child;
    }
}
void findPosition(int cur, int& idx, ull& n_hash){
    if(cur >= heapsize) return;
    if(findPosFlag) return;
    if(HEAP[(cur * 2) + 1] -> idx == idx){
        HEAP[(cur * 2) + 1] -> hash = n_hash;
        pushHeap((cur * 2) + 1);
        findPosFlag = true;
        return;
    }
    else{
        findPosition((cur * 2) + 1, idx, n_hash);
    }

    if(HEAP[(cur * 2) + 2] -> idx == idx){
        HEAP[(cur * 2) + 2] -> hash = n_hash;
        pushHeap((cur * 2) + 2);
        findPosFlag = true;
        return;
    }
    else{
        findPosition((cur * 2) + 2, idx, n_hash);
    }
}


void clear(){
    id = 0;
    heapsize = 0;
}

void init(){
    clear();
}

void push(int idx, char name[]){
    if(heapsize > MAX_LEN - 1) return;
    HEAP_POOL[id].hash = getHash(name);
    HEAP_POOL[id].idx = idx;

    HEAP[heapsize] = &HEAP_POOL[id];
    pushHeap(heapsize);
    id++;
    heapsize++;
}

int pop(){
    if(heapsize <= 0) return -1;

    int result = HEAP[0] -> idx;
    heapsize--;
    HEAP[0] = HEAP[heapsize];
    popHeap();
    return result;
}

void mod(int idx, char name[]){
    findPosFlag = false;
    ull n_hash = getHash(name);
    findPosition(0, idx, n_hash);
}