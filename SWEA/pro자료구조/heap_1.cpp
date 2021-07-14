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