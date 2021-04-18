#define MAX_NODE 1000001
#define BUCKET 1000
#define rint register int
#define NULL 0
 
typedef struct node{
    int data;
    struct node* prev;
    struct node* next;
}NODE;
 
NODE a[MAX_NODE];
int a_cnt;
 
NODE *pHead[BUCKET + 1], *pTail[BUCKET + 1];
int cnt[BUCKET + 1];
 
NODE* myalloc()
{
    a[a_cnt] = { 0, };
    return &a[a_cnt++];
}
 
void init() {
    a_cnt = 0;
    for (rint i = 0; i < BUCKET + 1; i++) {
        pHead[i] = myalloc();
        pTail[i] = myalloc();
        pHead[i]->next = pTail[i];
        pTail[i]->prev = pHead[i];
        cnt[i] = 0;
    }
}
 
void insert(int data) {
    rint index = data / BUCKET;
    NODE* p = myalloc();
    p->data = data;
    if (pHead[index]->next == pTail[index])
    {
        p->next = pTail[index];
        p->prev = p->next->prev;
        p->next->prev = p;
        p->prev->next = p;
        ++cnt[index];
    }
    else
    {
        for (NODE* iter = pHead[index]->next; iter != pTail[index]; iter = iter->next)
        {
            if (p->data < iter->data)
            {
                p->next = iter;
                p->prev = p->next->prev;
                p->next->prev = p;
                p->prev->next = p;
                ++cnt[index];
                break;
            }
            else if (iter->next == pTail[index])
            {
                p->next = pTail[index];
                p->prev = p->next->prev;
                p->next->prev = p;
                p->prev->next = p;
                ++cnt[index];
                break;
            }
        }
    }
}
 
int remove(int index) {
    rint idx = index, i = 0;
    NODE* iter = NULL;
 
    for (i = 0; i < BUCKET + 1; i++)
    {
        if (cnt[i] != 0)
        {
            if (idx >= cnt[i])
                idx -= cnt[i];
            else
                break;
        }
    }
 
    for (iter = pHead[i]->next; iter != pTail[i]; iter = iter->next)
    {
        if (idx == 0)
            break;
        idx--;
    }
    iter->next->prev = iter->prev;
    iter->prev->next = iter->next;
    --cnt[i];
    return iter->data;
}
 
int searchByIndex(int index) {
    rint idx = index, i = 0;
    NODE* iter = NULL;
 
    for (i = 0; i < BUCKET + 1; i++)
    {
        if (cnt[i] != 0)
        {
            if (idx >= cnt[i])
                idx -= cnt[i];
            else
                break;
        }
    }
 
    for (iter = pHead[i]->next; iter != pTail[i]; iter = iter->next)
    {
        if (idx == 0)
            break;
        idx--;
    }
    return iter->data;
}