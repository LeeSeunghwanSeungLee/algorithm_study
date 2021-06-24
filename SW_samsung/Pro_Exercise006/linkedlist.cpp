
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

void init();
void insert(int data);
int remove(int index);
int searchByIndex(int index);

#define INSERT	100
#define REMOVE	200
#define SBI		300

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d", &T);
    int N;
    int cmd, ret;
    int idx, data;
    for (int TC = 1; TC <= T; TC++) {

        init();

        int score = 100;

        scanf("%d", &N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &cmd);

            switch (cmd) {

            case INSERT:
                scanf("%d", &data);
                insert(data);

                break;

            case REMOVE:
                scanf("%d %d", &idx, &data);

                ret = remove(idx);

                if (ret != data) {
                    score = 0;
                }
                break;

            case SBI:
                scanf("%d %d", &idx, &data);

                ret = searchByIndex(idx);
                if (ret != data) {
                    score = 0;
                }
                break;
            }
        }

        printf("#%d %d\n", TC, score);
    }

    return 0;
}



#define MAX_SIZE 450
#define MAX_LEN 201000

struct node{
    int value;
    node* next;
    node* prev;
}NODE[MAX_LEN];
int nodeId(0);
node* alloc(int value){
    NODE[nodeId].value = value;
    return &NODE[nodeId++];
}

node* head[MAX_SIZE];
node* tail[MAX_SIZE];

int len[MAX_SIZE];

void insertAtRow(int row, node* newNode){
    node* curr = head[row] -> next;
    while(curr != tail[row]){
        if(curr -> value > newNode -> value) break;
        curr = curr -> next;
    }
    newNode -> prev = curr -> prev;
    newNode -> next = curr;
    curr -> prev -> next = newNode;
    curr -> prev = newNode;
}
void removeAtRow(node* target){
    target -> next -> prev = target -> prev;
    target -> prev -> next = target -> next;
}
void downdate(int row){ // 아래로 한칸식 추가
    node* aTarget = tail[row] -> prev;
    aTarget -> prev -> next = aTarget -> next;
    aTarget -> next -> prev = aTarget -> prev;
    len[row]--;

    row++;
    if(len[row] < MAX_SIZE) {
            insertAtRow(row, aTarget);
            len[row]++;
    }
    else if(len[row] >= MAX_SIZE && tail[row] -> prev -> value > aTarget -> value){
        insertAtRow(row, aTarget);
        len[row]++;
        downdate(row);
    }
}

void update(int row){ // 위로 한카씩 옮기기
    if(len[row + 1] <= 0) return;

    node* aTarget = head[row + 1] -> next;
    removeAtRow(aTarget);
    len[row + 1]--;


    aTarget -> prev = tail[row] -> prev;
    aTarget -> next = tail[row];
    tail[row] -> prev -> next = aTarget;
    tail[row] -> prev = aTarget;
    len[row]++;

    if(row + 1 >= MAX_SIZE - 1) return;

    if(len[row + 2] > 0){
        update(row + 1);
    }
}

void init(){
    nodeId = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        len[i] = 0;
        head[i] = alloc(-1);
        tail[i] = alloc(-1);
        head[i] -> next = tail[i];
        tail[i] -> prev = head[i];
    }
}

void insert(int data){
    node* newNode = alloc(data);

    for(int i = 0; i < MAX_SIZE; i++){
        if(len[i] < MAX_SIZE) {
            insertAtRow(i, newNode);
            len[i]++;
            break;
        }
        else if(len[i] >= MAX_SIZE && tail[i] -> prev -> value > data){
            insertAtRow(i, newNode);
            len[i]++;
            downdate(i);
            break;
        }
    }
    printf("%d", head[0] -> next -> value);
    return;
}

int remove(int index){
    int row;
    for(int i = 0; i < MAX_SIZE; i++){
        if(len[i] >= index){
            row = i;
            break;
        }
        else index -= len[i];
    }
    // row 행, index 열
    node* curr = head[row];
    for(int i = index; i > 0; i--){
        curr = curr -> next;
    }

    if(len[row] >= MAX_SIZE){
        removeAtRow(curr);
        len[row]--;
        update(row);
    }
    else {
        removeAtRow(curr);
        len[row]--;
    }
    return curr -> value;
}
int searchByIndex(int index){
    int row;
    for(int i = 0; i < MAX_SIZE; i++){
        if(len[i] >= index){
            row = i;
            break;
        }
        else index -= len[i];
    }
    // row 행, index 열
    node* curr = head[row];
    for(int i = index; i > 0; i--){
        curr = curr -> next;
    }
    return curr -> value;
}