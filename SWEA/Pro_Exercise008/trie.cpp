#define MAXSTR 100
#define MAX_LEN 500010

struct node{
    int end;
    node* next[26];
}NODE[MAX_LEN];
int nodeId(0);

node* alloc(){
    NODE[nodeId].end = 0;
    for(int i = 0; i < 26; i++) NODE[nodeId].next[i] = 0;
    return &NODE[nodeId++];
}

node* root;

int prefix_res;

void init_trie(){
    nodeId = 0;
    root = alloc();
}
void Tries_insert(char key[MAXSTR+1]){
    node* curr = root;
    while(*key){
        int k = *key - 'a';
        if(curr -> next[k] == 0) curr -> next[k] = alloc();
        key++;
        curr = curr -> next[k];
    }
    curr -> end++;
    return;
}
bool Tries_search(char key[MAXSTR+1]){
    node* curr = root;
    while(*key){
        int k = *key - 'a';
        if(curr -> next[k] == 0) return false;
        key++;
        curr = curr -> next[k];
    }
    if(curr -> end <= 0) return false;
    return true;
}

void dfs(node* curr){
    //현재의 end 값을 더한다
    prefix_res += curr -> end;
    for(int i = 0; i < 26; i++){
        if(curr -> next[i] == 0) continue;
        dfs(curr -> next[i]);
    }
    return;
}
int Tries_CountofkeysWithPrefix(char key[MAXSTR+1]){
    prefix_res = 0;
    node* curr = root;
    while(*key){
        int k = *key - 'a';
        if(curr -> next[k] == 0) return 0;
        key++;
        curr = curr -> next[k];
    }
    dfs(curr);
    return prefix_res;
}
void Tries_deleteKey(char key[MAXSTR+1]){
    node* curr = root;
    while(*key){
        int k = *key - 'a';
        if(curr -> next[k] == 0) return;
        key++;
        curr = curr -> next[k];
    }
    if(curr -> end <= 0) return;
    curr -> end--;
    return;
}