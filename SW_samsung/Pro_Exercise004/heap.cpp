
// ====================================================================================================
#define MAX_LEN 7000

void cpystr(char* dest, char* target){
    while(*dest++ = *target++);
    return;
}
int cmpstr(char* left, char* right){ // left가 크면 1 // 같으면 0 // 아니면 -1
    while(*left != 0 && *right != 0){
        if(*left > *right) return 1;
        else if(*left < *right) return -1;
        left++; right++;
    }
    if(*left != 0 && *right == 0) return 1;
    if(*right != 0 && *left == 0) return -1;
    if(*left == 0 && *right == 0) return 0;
}
struct node{
    int idx;
    char name[11];
};
node poolNode[MAX_LEN];
int nId = 0;

node* alloc(int idx, char* name){
    poolNode[nId].idx = idx;
    cpystr(poolNode[nId].name, name);
    return &poolNode[nId++];
}

bool cmpheap(node* a, node* b){
    if(cmpstr(a -> name, b -> name) == 1) return true;
    else if(cmpstr(a -> name, b -> name) == 0 && a -> idx < b -> idx) return true;

    return false;
}


node* heap[MAX_LEN];
int hId = 0;

void init(){
    nId = 0;
    hId = 0;
}
void clear(){
    init();
}

void push(int idx, char* name){
    node* newNode = alloc(idx, name);
    heap[hId++] = newNode;

    int curr = hId - 1;
    while(curr != 0){
        if(cmpheap(heap[curr], heap[(curr - 1) / 2])){
            node* aTemp = heap[curr];
            heap[curr] = heap[(curr - 1) / 2];
            heap[(curr - 1) / 2] = aTemp;

            curr = (curr - 1) / 2;
        }
        else{
            break;
        }
    }
    return;
}
int pop(){
    node* res = heap[0];

    heap[0] = heap[hId - 1];
    hId--;
    int curr = 0;
    while(curr * 2 + 1 < hId){
        int child;
        if(curr * 2 + 2 == hId) child = curr * 2 + 1;
        else child = cmpheap(heap[curr * 2 + 1], heap[curr * 2 + 2])? curr * 2 + 1: curr * 2 + 2;

        if(cmpheap(heap[child], heap[curr])){
            // 교환
            node* aTemp = heap[curr];
            heap[curr] = heap[child];
            heap[child] = aTemp;

            curr = child;
        }
        else break;
    }

    return res -> idx;
}
int top(){
    return heap[0] -> idx;
}



// 20
// 200 543659 ghyrzb
// 200 163936 zekavhbo
// 200 633396 zluef
// 200 873015 lnavtb
// 200 262907 vzkdxuhlxm
// 200 965046 algmu
// 200 732960 dbktwnpmuq
// 200 889356 onogtaeixy
// 200 949529 viheoqbujr
// 300 633396
// 200 524763 qutlvykuug
// 300 163936
// 200 950294 algmu
// 200 19468 yvhdcfvugm
// 200 711511 dufjvvoms
// 200 850743 bmojssxze
// 300 19468
// 200 176866 qpaj
// 300 262907
// 300 949529