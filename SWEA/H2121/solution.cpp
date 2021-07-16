#define MAX_H 207
#define MAX_M 101
#define MAX_N 10000
#define NULL 0

struct Machine{
    int idx;
    int id;
    int duration;
    int capacity;
    int waitCnt;
    int time;
}machinePool[MAX_M];
Machine* machineArr[MAX_M];

struct Node{
    int num;
    int priority;
}nodePool[MAX_N];
int nodeSize;

int hTbl[MAX_H];

void addHash(int id, int idx){
    int h = id % MAX_H;

    while(machinePool[hTbl[h]].id != id){
        if(hTbl[h] == -1) break;
        h = (h + 1) % MAX_H;
    }

    hTbl[h] = idx;
}

int findHash(int id){
    int h = id % MAX_H;
    int cnt = MAX_H;

    while(machinePool[hTbl[h]].id != id && cnt--){
        if(hTbl[h] == -1){
            return -1;
        }
        h = (h + 1) % MAX_H;
    }
    return hTbl[h];
}

Node* Heap[MAX_M][MAX_N];
int HeapSize[MAX_M];

void heapPush(int mIdx, Node* value){
    Heap[mIdx][HeapSize[mIdx]] = value;

    int current = HeapSize[mIdx];
    while(current > 0 && Heap[mIdx][current]->priority > Heap[mIdx][(current - 1) / 2]->priority) {
        Node* temp = Heap[mIdx][(current - 1) / 2];
        Heap[mIdx][(current - 1) / 2] = Heap[mIdx][current];
        Heap[mIdx][current] = temp;
        current = (current - 1) / 2;
    }
    HeapSize[mIdx]++;
}

Node* heapPop(int mIdx){
    if(HeapSize[mIdx] <= 0) return NULL;

    Node* ret = Heap[mIdx][0];
    HeapSize[mIdx]--;

    Heap[mIdx][0] = Heap[mIdx][HeapSize[mIdx]];

    int current = 0;
    while(2 * current + 1 < HeapSize[mIdx]){
        int child;
        if (current * 2 + 2 == HeapSize[mIdx]) 
        {
            child = current * 2 + 1;
        }
        else
        {
            child = Heap[mIdx][current * 2 + 1]->priority > Heap[mIdx][current * 2 + 2]->priority ? current * 2 + 1 : current * 2 + 2;
        }
 
 
        if (Heap[mIdx][current]->priority > Heap[mIdx][child]->priority)
        {
            break;
        }
 
        Node* temp = Heap[mIdx][current];
        Heap[mIdx][current] = Heap[mIdx][child];
        Heap[mIdx][child] = temp;
 
        current = child;
    }
    return ret;
}

void update(Machine* m, int tStamp){
    while(m -> time <= tStamp && HeapSize[m -> idx] > 0){
        int remainder = m -> capacity;
        while(remainder > 0 && HeapSize[m -> idx] > 0){
            Node* curr = Heap[m -> idx][0];
            if(remainder < curr -> num){
                curr -> num -= remainder;
                m -> waitCnt -= remainder;
                break;
            }
            remainder -= curr -> num;
            m -> waitCnt -= curr -> num;
            heapPop(m -> idx);
        }
        m -> time += m->duration;
    }
}

int N;
void init(int N, int mId[], int mDuration[], int mCapacity[]){
    ::N = N;
    for(register int i = 0; i < MAX_H; i++){
        hTbl[i] = -1;
    }
    for(register int i = 0; i < MAX_M; i++){
        HeapSize[i] = 0;
    }
    for(register int i = 0; i < N; i++){
        Machine* m = &machinePool[i];
        m -> id = mId[i];
        m->idx = i;
        m->duration = mDuration[i];
        m->capacity = mCapacity[i];
        m->time = 0;
        m->waitCnt = 0;
 
        machineArr[i] = m;
 
        addHash(mId[i], i);
    }
    nodeSize = 0;
}

int add(int tStamp, int mId, int mNum, int mPriority){
    int idx = findHash(mId);
    Machine* m = &machinePool[idx];

    update(m, tStamp - 1);
    if(m -> time < tStamp){
        m -> time = tStamp;
    }
    m -> waitCnt += mNum;

    Node* n = &nodePool[nodeSize++];
    n -> num = mNum;
    n -> priority = mPriority;

    heapPush(m -> idx, n);
    update(m, tStamp);

    int ret = 0;
    if(HeapSize[m -> idx] > 0) ret = Heap[m ->idx][0] -> priority;
    return ret;
}

void search(int tStamp, int mCount, int mId[], int mWait[]) 
{
    for (register int i = 0; i < N; ++i) 
    {
        update(&machinePool[i], tStamp);
    }
 
    for (register int i = 0; i < mCount; ++i) 
    {
        for (register int j = i + 1; j < N; ++j) 
        {
            if ((machineArr[i]->waitCnt < machineArr[j]->waitCnt) ||
                (machineArr[i]->waitCnt == machineArr[j]->waitCnt && machineArr[i]->id < machineArr[j]->id)) 
            {
                Machine* tmp = machineArr[i];
                machineArr[i] = machineArr[j];
                machineArr[j] = tmp;
            }
        }
        mId[i] = machineArr[i]->id;
        mWait[i] = machineArr[i]->waitCnt;
    }
 
}