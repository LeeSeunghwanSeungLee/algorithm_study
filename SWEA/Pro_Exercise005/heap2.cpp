#define MAX_LEN 100002

void cpystr(char* dest, char* target) {
    while (*dest++ = *target++);
    return;
}
int cmpstr(char* left, char* right) { // left가 크면 1 // 같으면 0 // 아니면 -1
    while (*left != 0 && *right != 0) {
        if (*left > * right) return 1;
        else if (*left < *right) return -1;
        left++; right++;
    }
    if (*left != 0 && *right == 0) return 1;
    if (*right != 0 && *left == 0) return -1;
    if (*left == 0 && *right == 0) return 0;
    return 0;
}
struct node {
    int idx;
    int heapIdx;
    char name[11];
};
node poolNode[MAX_LEN];

node* alloc(int idx, int heapId, char* name) {
    poolNode[idx].idx = idx;
    poolNode[idx].heapIdx = heapId;
    cpystr(poolNode[idx].name, name);
    return &poolNode[idx];
}

bool cmpheap(node* a, node* b) {
    if (cmpstr(a->name, b->name) == 1) return true;
    else if (cmpstr(a->name, b->name) == 0 && a->idx < b->idx) return true;

    return false;
}


node* heap[MAX_LEN];
int hId = 0;

void init() {
    hId = 0;
}
void clear() {
    init();
}

void push(int idx, char* name) {
    node* newNode = alloc(idx, hId ,name);
    heap[hId++] = newNode;

    int curr = hId - 1;
    while (curr != 0) {
        if (cmpheap(heap[curr], heap[(curr - 1) / 2])) {

            int aTempIdx = heap[curr]->heapIdx;
            heap[curr]->heapIdx = heap[(curr - 1) / 2]->heapIdx;
            heap[(curr - 1) / 2]->heapIdx = aTempIdx;

            node* aTemp = heap[curr];
            heap[curr] = heap[(curr - 1) / 2];
            heap[(curr - 1) / 2] = aTemp;

            curr = (curr - 1) / 2;
        }
        else {
            break;
        }
    }
    return;
}
int pop() {
    heap[hId - 1]->heapIdx = heap[0]->heapIdx;
    node* res = heap[0];

    heap[0] = heap[hId - 1];

    hId--;
    int curr = 0;
    while (curr * 2 + 1 < hId) {
        int child;
        if (curr * 2 + 2 == hId) child = curr * 2 + 1;
        else child = cmpheap(heap[curr * 2 + 1], heap[curr * 2 + 2]) ? curr * 2 + 1 : curr * 2 + 2;

        if (cmpheap(heap[child], heap[curr])) {
            int aTempIdx = heap[curr]->heapIdx;
            heap[curr]->heapIdx = heap[child]->heapIdx;
            heap[child]->heapIdx = aTempIdx;
            // 교환
            node* aTemp = heap[curr];
            heap[curr] = heap[child];
            heap[child] = aTemp;

            curr = child;
        }
        else break;
    }

    return res->idx;
}

void mod(int idx, char name[]) {
    node* target = &poolNode[idx];
    int direction;
    if (cmpstr(target->name, name) == 1) { // 기존게 더 크면 아래로
        cpystr(target->name, name);
        int curr = target->heapIdx;
        //힙 아래로 업데이트
        while (curr * 2 + 1 < hId) {
            int child;
            if (curr * 2 + 2 == hId) child = curr * 2 + 1;
            else child = cmpheap(heap[curr * 2 + 1], heap[curr * 2 + 2]) ? curr * 2 + 1 : curr * 2 + 2;

            if (cmpheap(heap[child], heap[curr])) {
                int aTempIdx = heap[curr]->heapIdx;
                heap[curr]->heapIdx = heap[child]->heapIdx;
                heap[child]->heapIdx = aTempIdx;
                // 교환
                node* aTemp = heap[curr];
                heap[curr] = heap[child];
                heap[child] = aTemp;

                curr = child;
            }
            else break;
        }
    }
    else if (cmpstr(target->name, name) == -1) { // 기존게 더 작으면 위로
        int curr = target->heapIdx;
        cpystr(target->name, name);
         //힙 위로 업데이트
        while (curr != 0) {
            if (cmpheap(heap[curr], heap[(curr - 1) / 2])) {

                int aTempIdx = heap[curr]->heapIdx;
                heap[curr]->heapIdx = heap[(curr - 1) / 2]->heapIdx;
                heap[(curr - 1) / 2]->heapIdx = aTempIdx;

                node* aTemp = heap[curr];
                heap[curr] = heap[(curr - 1) / 2];
                heap[(curr - 1) / 2] = aTemp;

                curr = (curr - 1) / 2;
            }
            else {
                break;
            }
        }
    }
    return;
   
}