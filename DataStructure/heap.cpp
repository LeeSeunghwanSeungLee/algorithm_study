#include <iostream>
#define MAX_LEN 2000

using namespace std;

struct Heap{
    int val;
    void set(int num){
        this->val = num;
    }
};

Heap heap[MAX_LEN];
int now(0);

void push(int num){
    heap[now].set(num);
    now++;

    int cur = now - 1;
    while(cur > 0){
        //부모와 비교해서 더 크면 서로 바꾼다
        if(heap[cur].val > heap[(cur - 1) / 2].val){
            Heap tmp = heap[cur];
            heap[cur] = heap[(cur - 1) / 2];
            heap[(cur - 1) / 2] = tmp;
            cur = (cur - 1) / 2; 
        }
        else break;
    }
    return ;
}

void pop(){
    now--;
    cout << heap[0].val << '\n' ;
    heap[0] = heap[now];
    int cur = 0;
    int child;
    while(cur * 2 + 1 < now){ // 자식이 존재할 경우까지
        if(cur * 2 + 2 == now) // 만일 자식이 하나라면
            child = cur * 2 + 1;
        else{// 만일 자식이 2명이라면 l
            child = (heap[cur * 2 + 1].val < heap[cur * 2 + 2].val)? cur * 2 + 2 : cur * 2 + 1;
        }

        //서로 변경한다
        Heap tmp = heap[cur];
        heap[cur] = heap[child];
        heap[child] = tmp;

        cur = child;
    }
}
void size(){
    cout << now << '\n';
}

int main(void){
    size();
    push(5);
    size();
    push(6);
    size();
    push(1);
    size();
    pop();
    pop();
    pop();
    size();
    return 0;
}


