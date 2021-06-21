#define MAX_ROW 1000
#define MAX_COL 100 // 도합 100,000 
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
    while(curr != tail[row]){
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
    }
}

void insert(int data){
    node* newNode = alloc_node(data);

    int row;
    for(row = 0; row < MAX_ROW; row++){
        if(len[row] == 0){ // 한개도 없는 경우
            cout << '1' << '\n';
            head[row] -> next = newNode;
            newNode -> prev = head[row];
            newNode -> next = tail[row];
            tail[row] -> prev = newNode;
            len[row]++;
            break;
        }
        else if(len[row] < MAX_COL){
            cout << '2' << '\n';
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


//     15
// 10
// 100 79679
// 100 889119
// 100 581719
// 300 1 581719
// 100 797738
// 300 2 797738
// 100 42035
// 100 722185
// 100 11881
// 100 541658