#define MAX_SIZE    100000
#define HASH        5381 // 해시를 사용하기 위함
 
struct E {
    int k;
    int v;
    bool del;
    E* next;
};
 
E elem[MAX_SIZE];
int e_idx;
 
E* my_alloc(int k, int v) {
    E* n_e = &elem[e_idx++];
    n_e->k = k;
    n_e->v = v;
    n_e->del = false;
    n_e->next = 0; // NULL 값을 대체하기 위해서 0으로 넣는다 .. nullptr 을 대신하기 위함인가봄
    return n_e;
}
 

E* h_table[HASH];
 
void put_elem(E* n) {
    int h = n->k % HASH;
    n->next = h_table[h];
    h_table[h] = n;
}
 
E* get_elem(int key) {
    int h = key % HASH;
    E* e = h_table[h];
    while (e->k != key) {
        e = e->next;
    }
    return e;
}
 
E* heap[MAX_SIZE];
int heapSize = 0;
 
int heapPush(E* n) {
    heap[heapSize] = n;
 
    int current = heapSize;
    while (current > 0 && heap[current]->v > heap[(current - 1) / 2]->v) {
        E* temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
 
    heapSize = heapSize + 1;
 
    return 1;
}
 
E* heapPop() {
    if (heapSize <= 0) {
        return 0;
    }
 
    E* res = heap[0];
    heapSize = heapSize - 1;
 
    heap[0] = heap[heapSize];
 
    int current = 0;
    while (current * 2 + 1 < heapSize) {
        int child;
        if (current * 2 + 2 == heapSize) {
            child = current * 2 + 1;
        }
        else {
            child = heap[current * 2 + 1]->v > heap[current * 2 + 2]->v ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (heap[current]->v > heap[child]->v) {
            break;
        }
 
        E* temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
 
        current = child;
    }
    return res;
}
 
void init() {
    e_idx = heapSize = 0;
    for (register int i = 0; i < HASH; i++) {
        h_table[i] = 0;
    }
}
 
void push(int key, int value) {
    E* n = my_alloc(key, value);
    put_elem(n);
    heapPush(n);
}
 
int top(int K) {
    int res = 0;
    E* temp[10];
    register E* e;
    for (int i = 0; i < K; i++) {
        e = heapPop();
        while (e->del) {
            e = heapPop();
        }
        res += e->v;
        temp[i] = e;
    }
    for (int i = 0; i < K; i++) {
        heapPush(temp[i]);
    }
    return res;
}
 
void erase(int key) {
    E* e = get_elem(key);
    e->del = true;
}
 
void modify(int key, int value) {
    erase(key);
    push(key, value);
}