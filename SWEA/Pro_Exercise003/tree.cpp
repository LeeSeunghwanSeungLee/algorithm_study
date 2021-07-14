#include <iostream>
using namespace std;
// ===========================================================================
#define MAX_LEN 8000


struct node{
    int name;
    node* parent;
    node* children;
    int child_num;

    node* next; // sibling
};
node poolNode[MAX_LEN];


void init(){
    for(int i = 0; i < MAX_LEN; i++){
        poolNode[i].name = i;
        poolNode[i].parent = 0;
        poolNode[i].child_num = 0;
    }
}

void insert(int name, int parent){
    poolNode[name].parent = &poolNode[parent];

    node* curr = poolNode[parent].children;
    poolNode[parent].children = &poolNode[name];
    poolNode[name].next = curr;

    poolNode[parent].child_num++;
}
void remove(int name){
    node* curr = &poolNode[name];
    node* parent = curr -> parent;
    node* child = parent -> children;

    if(child == curr){
        parent -> children = curr -> next;
    }
    else{
        for(int i = 0; i < parent -> child_num - 1; i++){
            if(child -> next == curr) break;
            child = child -> next;
        }
        child -> next = curr -> next;
    }
    parent -> child_num--;
}

int findAnce(int name, int ance[]){
    node* curr = &poolNode[name];
    int i=0;
    while(curr -> parent){
        ance[i++] = curr -> parent -> name;
        curr = curr -> parent;
    }
    return i;
}
bool dfs(int name, int target){
    node* curr = &poolNode[name];
    if(curr -> name == target) return true;
    else{
        node* child = curr -> children;
        for(int i = 0; i < curr -> child_num; i++){
            if(dfs(child -> name, target)) return true;
            child = child -> next;
        }
    }
    return false;
}
int findDesc(int name, int target){
    if(dfs(name, target)) return 1;
    return 0;
}



// ===========================================================================
int main(void){
    init();
	insert(2, 1);
	insert(3, 1);
	int res = findAnce(2);
	cout << res << '\n';
	res =findDesc(1, 3);
	cout << res << '\n';
	insert(4, 2);
	res = findAnce(2);
	cout << res << '\n';
	insert(5, 4);
	insert(6, 3);
	remove(6);
	res = findDesc(3, 6);
	cout << res << '\n';
    return 0;
}