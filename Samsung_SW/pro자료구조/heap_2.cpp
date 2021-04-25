#define NULL 0
#define MAX_N 100010
#define MAX_KEY 11
#define ULL unsigned long long
 
struct NODE {
    int idx;
    ULL name;
};
 
int _arrIndex = 0;
NODE _arrTable[MAX_N];
 
NODE* myAlloc() {
    return &_arrTable[_arrIndex++];
}
 
ULL _str2ull(char* name) { // hasing!
    int i = 0;
    int count = MAX_KEY;
    ULL result = 0;
 
    while (name[i] != '\0') {
        result = result << 5;
        result = result + (name[i] - 'a' + 1);
        i++;
        count--;
    }
 
    result = result << (count*5);
    return result;
}
 
int _compare(NODE* a, NODE* b) {
    if (a->name < b->name) return 1;
    else if (a->name > b->name) return -1;
    else {
        if (a->idx < b->idx) return -1;
        else return 1;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////
 
NODE* heap[MAX_N];
int heapSize = 0;
int indexTable[MAX_N];
 
void init() {
    _arrIndex = 0;
    heapSize = 0;
}
 
void clear() {
    init();
}
 
void _upHeapify(int current) {
    while (current > 0 && _compare(heap[current], heap[(current - 1) / 2]) == -1)
    {
        NODE* temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
 
        indexTable[heap[current]->idx] = current;
        indexTable[heap[(current - 1) / 2]->idx] = (current - 1) / 2;
 
        current = (current - 1) / 2;
    }
}
 
int _downHeapify(int current) {
    while (current * 2 + 1 < heapSize)
    {
        int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = _compare(heap[current * 2 + 1], heap[current * 2 + 2]) == -1 ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (_compare(heap[current], heap[child]) == -1)
        {
            break;
        }
 
        NODE* temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
 
        indexTable[heap[current]->idx] = current;
        indexTable[heap[child]->idx] = child;
 
        current = child;
    }
    return current;
}
 
void push(int idx, char name[]) {
    NODE* node = myAlloc();
    node->idx = idx;
    node->name = _str2ull(name);
 
    heap[heapSize] = node;
    indexTable[heap[heapSize]->idx] = heapSize;
 
    int current = heapSize;
    _upHeapify(current);
 
    heapSize = heapSize + 1;
 
    return;
}
 
int pop() {
    int idx = heap[0]->idx;
    heapSize = heapSize - 1;
 
    heap[0] = heap[heapSize];
    indexTable[heap[0]->idx] = 0;
 
    int current = 0;
    _downHeapify(current);
    return idx;
 
}
 
void mod(int idx, char name[]) {
    NODE* node = heap[indexTable[idx]]; 
 
    node->name = _str2ull(name);
 
    int current = indexTable[idx];
 
    current = _downHeapify(current);
    _upHeapify(current);
}