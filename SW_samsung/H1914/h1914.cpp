#define MAX_N    100
#define MAX_TOOL 50
#define MAX_TOTAL_TOOL 5000
#define MAX_LOT 100000
 
int last;
int ptest;
 
struct sLot {
    int et;
    int stepNo;
    int toolNo;
    int pt;
 
    bool operator<(sLot& l) {
        if (et != l.et) return et < l.et;
        else return (stepNo != l.stepNo)? stepNo > l.stepNo : pt < l.pt;
    }
}lot;
int lotNum;
 
struct sTool {
    int idx;
    int stepNo;
    int pt;
    int et;
 
    bool operator<(sTool& t) {
        if (pt != t.pt) return pt < t.pt;
        else return et < t.et;
    }
}tool[MAX_TOTAL_TOOL];
 
struct sStep {
    int toolCnt;
    int waitingLotCnt;
 
    void init() {
        toolCnt = 0;
        waitingLotCnt = 0;
    }
}step[MAX_N];
int stepNum;
 
struct waitingToolHeap {
    int heapsize;
    sTool* heap[MAX_TOOL];
 
    void init() {
        heapsize = 0;
    }
 
    void push(sTool* t) {
        heap[heapsize] = t;
        update(heapsize++);
    }
 
    sTool* pop(void) {
        sTool *t = heap[0];
        heapsize--;
 
        heap[0] = heap[heapsize];
        downdate(0);
        return t;
    }
     
    void update(int current) {
        while (current > 0 && *heap[current] < *heap[(current - 1) / 2])
        {
            swap(current, (current - 1) / 2);
            current = (current - 1) / 2;
        }
    }
 
    void downdate(int current) {
        while (current * 2 + 1 < heapsize)
        {
            int child;
            if (current * 2 + 2 == heapsize) child = current * 2 + 1;
            else child = *heap[current * 2 + 1] < *heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
 
            if (*heap[current] < *heap[child]) break;
            swap(current, child);
            current = child;
        }
    }
 
    void swap(int a, int b) {
        sTool* temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }
}waitingth[MAX_N];
 
struct workinglotHeap {
    int heapsize;
    sLot heap[MAX_LOT];
 
    void init() {
        heapsize = 0;
    }
 
    void push(sLot l) {
        heap[heapsize] = l;
        update(heapsize++);
    }
 
    void pop(sLot* l) {
        *l = heap[0];
        heapsize--;
 
        heap[0] = heap[heapsize];
        downdate(0);
    }
 
    void update(int current) {
        while (current > 0 && heap[current] < heap[(current - 1) / 2])
        {
            swap(current, (current - 1) / 2);
            current = (current - 1) / 2;
        }
    }
 
    void downdate(int current) {
        while (current * 2 + 1 < heapsize)
        {
            int child;
            if (current * 2 + 2 == heapsize) child = current * 2 + 1;
            else child = (heap[current * 2 + 1] < heap[current * 2 + 2])? current * 2 + 1 : current * 2 + 2;
 
            if (heap[current] < heap[child]) break;
            swap(current, child);
            current = child;
        }
    }
 
    void swap(int a, int b) {
        sLot temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }
}workinglot;
 
void init(int N) {
    last = 0;
    lotNum = 0;
    stepNum = N;
    workinglot.init();
 
    for (register int i = 0; i < N; i++)
    {
        step[i].init();
        waitingth[i].init();
    }
    ptest = 0;
}
 
void setupTool(int T, int stepNo[5000], int procTime[5000]) {
    for (register int i = 0; i < T; i++)
    {
        tool[i] = { i, stepNo[i], procTime[i], 0 };
        waitingth[stepNo[i]].push(&tool[i]);
        step[stepNo[i]].toolCnt++;
    }
}
 
void move(sLot l) {
    if (l.stepNo == stepNum)
    {
        last++;
        return;
    }
 
    if (waitingth[l.stepNo].heapsize)
    {
        register sTool* t = waitingth[l.stepNo].pop();
 
        l.toolNo = t->idx;
        l.et += t->pt;
        l.pt = t->pt;
        workinglot.push(l);
    }
    else
        step[l.stepNo].waitingLotCnt++;
}
 
void process(int time) {
    if (!time) return;
    while(workinglot.heapsize)
    {
        if (workinglot.heap[0].et > time) break;
 
        sLot l;
        workinglot.pop(&l);
        waitingth[l.stepNo].push(&tool[l.toolNo]);
 
        register int si = l.stepNo;
        register int et = l.et;
        l.stepNo++;
        move(l);
        if (step[si].waitingLotCnt)
        {
            register sTool *t = waitingth[si].pop();
            sLot lo;
            lo.stepNo = si;
            lo.toolNo = t->idx;
            lo.et = et + t->pt;
            lo.pt = t->pt;
            workinglot.push(lo);
            step[si].waitingLotCnt--;
        }
    }
}
 
void addLot(int time, int number) {
    process(time);
 
    register int n = number;
    while (n--)
    {
        sLot lot = {time, 0, -1, 0};
        move(lot);
    }
}
 
int simulate(int time, int wip[MAX_N]) {
    process(time);
    for (register int i = 0; i < stepNum; i++)
        wip[i] = step[i].waitingLotCnt + step[i].toolCnt - waitingth[i].heapsize;
 
    return last;
}