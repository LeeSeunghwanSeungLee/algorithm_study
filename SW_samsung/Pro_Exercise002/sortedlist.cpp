#define MAX_ROW 100
#define MAX_COL 1000 // 도합 100,000 
#include <iostream>
using namespace std;


struct node{
    int value;
    node* next;
    node* prev;
};

node poolNode[120000];
int nodeId(0);
node* alloc_node(int value){
    poolNode[nodeId].value = value;
    poolNode[nodeId].next = 0;
    poolNode[nodeId].prev = 0;
    return &poolNode[nodeId++];
}

node* head[MAX_ROW];
node* tail[MAX_ROW];
int len[MAX_ROW];

void init(){
    nodeId = 0;
    for(int i = 0; i < MAX_ROW; i++){
        head[i] = alloc_node(-1);
        tail[i] = alloc_node(-1);
        len[i] = 0;
        head[i] -> next = tail[i];
        tail[i] -> prev = head[i];
    }
}

void insertAtRow(int row, node* newNode){
    node* curr = head[row] -> next;
    while(curr != 0){
        if(curr -> value >= newNode -> value || curr == tail[row]){
            newNode -> next = curr;
            newNode -> prev = curr -> prev;
            curr -> prev -> next = newNode;
            curr -> prev = newNode;
            len[row]++;
            break;
        }
        else curr = curr -> next;
    }
    if(len[row] > MAX_COL){
        node* lastNode = tail[row] -> prev;
        lastNode -> prev -> next = lastNode -> next;
        lastNode -> next -> prev = lastNode -> prev;
        len[row]--;
        insertAtRow(row + 1, lastNode);
        insertAtRow(row + 1, lastNode);
    }
}

void insert(int data){
    node* newNode = alloc_node(data);

    int row;
    for(row = 0; row < MAX_ROW; row++){
        if(len[row] == 0){ // 한개도 없는 경우
            head[row] -> next = newNode;
            newNode -> prev = head[row];
            newNode -> next = tail[row];
            tail[row] -> prev = newNode;
            len[row]++;
            break;
        }
        else if(len[row] < MAX_COL){
            node* curr = head[row] -> next;
            while(curr != 0){
                if(curr -> value >= data || curr == tail[row]){
                    newNode -> next = curr;
                    newNode -> prev = curr -> prev;
                    curr -> prev -> next = newNode;
                    curr -> prev = newNode;
                    len[row]++;
                    break;
                }
                else curr = curr -> next;
            }
            break;
        }
        else{
            //마지막과 비교후 insertAtRow 시전 아니면 컨티뉴
            node* lastNode = tail[row] -> prev;
            if(lastNode -> value > data){
                insertAtRow(row, newNode);
                break;
            }
        }
    }
    return;
}

void removeAtRow(int row){
    node* curr = head[row] -> next;
    curr -> prev -> next = curr -> next;
    curr -> next -> prev = curr -> prev;
    len[row]--;
    curr -> prev = tail[row - 1] -> prev;
    curr -> next = tail[row - 1];
    tail[row - 1] -> prev -> next = curr;
    tail[row - 1] -> prev = curr;
    len[row - 1]++;

    if(row + 1 >= MAX_ROW) return;
    else if(len[row + 1] > 0){
        removeAtRow(row + 1);
    }
    return;
}
int remove(int index){
    index = index + 1;
    int row;
    for(row= 0; row < MAX_ROW; row++){
        if(len[row] >= index) break;
        index -= len[row];
    }
    node* curr = head[row];
    for(int start = index; start > 0; start--){
        curr = curr -> next;
    }
    curr -> prev -> next = curr -> next;
    curr -> next -> prev = curr -> prev;
    len[row]--;
    if(len[row + 1] > 0){
        removeAtRow(row + 1);
    }
    return curr -> value;
}

int searchByIndex(int index){
    index = index + 1;
    int row;
    for(row= 0; row < MAX_ROW; row++){
        if(len[row] >= index) break;
        index -= len[row];
    }
    cout << row << '\n';
    node* curr = head[row];
    for(int start = index; start > 0; start--){
        curr = curr -> next;
    }
    return curr -> value;
}

int main(void){
    init();
    insert(79679);
    insert(889119);
    insert(581719);
    int res = searchByIndex(1);
    cout << res <<'\n';
    insert(797738);
    res = searchByIndex(2);
    cout << res <<'\n';
    insert(42035);
    insert(722185);
    insert(11881);
    insert(541658);
    return 0;
}

100
100 188505
100 721940
100 314136
100 466046
300 1 314136
200 1 314136
300 1 466046
100 82534
100 169235
100 585149
100 100130
100 673014
200 7 721940
200 5 585149
100 187895
100 519112
100 458128
100 705710
300 9 705710
100 898091
100 455642
200 2 169235
100 220009
100 26169
100 453714
100 587498
100 273743
100 205544
100 896670
100 843658
100 437714
200 0 26169
100 710063
100 163627
100 635194
200 2 163627
100 711506
100 894876
100 490622
100 208989
100 3211
100 793916
300 18 673014
100 781260
200 12 458128
100 143163
100 959173
200 3 143163
200 27 959173
100 390921
100 441297
100 831714
100 721037
100 446784
100 56919
100 956365
100 624778
100 84697
200 1 56919
200 19 587498
100 817483
200 32 896670
200 28 817483
100 793642
100 317726
100 383377
100 991296
100 900636
200 12 390921
200 23 705710
100 829536
100 302702
200 6 205544
100 977203
100 197469
100 259815
100 110770
100 969263
300 13 317726
300 5 187895
100 463857
100 276102
200 3 100130
300 36 894876
300 36 894876
100 867570
300 19 455642
200 22 490622
200 27 711506
100 487767
100 960296
100 173158
100 182594
300 29 710063
100 913822
200 36 843658
200 14 302702
100 643270
200 28 673014
100 716747