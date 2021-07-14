#define MAX_LIST 1000001
#define NULL 0
 
typedef struct _node { // double linked list 로 선언함
    int data;
    struct _node *prev, *next;
}NODE;
 
NODE *pHead, *pTail; // No constructer...
 
NODE a[MAX_LIST];
 
int arr_idx = 0;
 
NODE* my_alloc(void) // 무슨 성능이 있는질 모르겟네?
{
    return &a[arr_idx++];
}
 
 
void init() {
    arr_idx = 0;
 
    pHead = my_alloc();
    pTail = my_alloc();
 
    pHead->next = pTail;
    pTail->prev = pHead;
}
 
void insert(int data) {
    NODE *p = my_alloc();
    p->data = data;
 
 
    if (pHead->next == pTail) { // 만일 첫 생성이라면..
        p->next = pTail;
        p->prev = pTail -> prev;
        pTail -> prev = p;
        pHead->next = p;
 
    }
    else { // 첫 생성이 아니라면..
        for (NODE *iter = pHead->next; iter != pTail; iter = iter->next) {
 
            if (iter->data > p->data) { // 만일 더 큰값을 만나게되면
                p->next = iter;
                p->prev = p->next->prev;
                p->next->prev = p;
                p->prev->next = p;
                 
                break;
            }
            else if (iter->next == pTail){ // 만일 끝까지 다왓다면
                p->next = pTail;
                p->prev = p->next->prev;
                p->next->prev = p;
                p->prev->next = p;
                break;
            }
        }       
    }
}
 
int remove(int index) {
    int cnt = 0;
 
    for (NODE* iter = pHead->next; iter != pTail ; iter = iter->next) {
        if (cnt == index) {
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            return iter->data;
        }
        cnt++;
    }
    return 0;
}
 
int searchByIndex(int index) {
    int cnt = 0;
 
    for (NODE* iter = pHead->next; iter != pTail ; iter = iter->next) {
        if (cnt == index) {
            return iter->data;
        }
        cnt++;
    }
    return -1; // 아무것도 없을때..?
}

// 링크드 리스트로 단순하게 구현완료!!