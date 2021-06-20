/*
  제약사항
  1. 호출횟수는 총 100,000 이하
  2. find 는 20% 내외
  3. remove 는 20퍼 내외
  3. add 60 퍼내외
*/

#define HASH_VAL 10000
#define MAX_LEN 200000


unsigned long hashing(char *a)
{
    unsigned long h = 5381;
    int c;
 
    while (c = *a++)
        h = (((h << 5) + h) + c % HASH_VAL);
    return h % HASH_VAL;
}

void strCopy(char* dest, char* key){ 
    register int i = 0;
    while(key[i]){
        dest[i] = key[i];
        i++;
    }
    dest[i] = '\0';
    return;
}
bool strCmp(char* str1, char* str2){
    register int i = 0;
    while(str1[i]){
        if(str1[i] != str2[i]) return false;
        i++;
    }
    if(str1[i] != 0 || str2[i] != 0) return false;
    return true;
}

struct node{
    char key[11];
    int value;
    node* next;
};
node nodePool[MAX_LEN];
int nId(0);
node* alloc_node(char *key, int value){
    strCopy(nodePool[nId].key, key);
    nodePool[nId].value = value;
    nodePool[nId].next = 0;
    return &nodePool[nId++];
}

node nodeHash[HASH_VAL];


void init(){
    nId = 0;
    for (register int i = 0; i < HASH_VAL; i++)
        nodeHash[i].next = 0;
}

void add(char key[], int data){
    int row = hashing(key);
    node* newNode = alloc_node(key, data);
    node* next = nodeHash[row].next;
    nodeHash[row].next = newNode;
    newNode -> next = next;

    return;
}

int find(char key[]){
    int row = hashing(key);
    node* curr = nodeHash[row].next;
    while(curr){
        if(strCmp(key, curr -> key)) {
            return curr -> value;
        }
        curr = curr -> next;
    }
    return -1;
}

int remove(char key[]){
    int row = hashing(key);
    int res;
    node* curr = nodeHash[row].next;
    node* temp = &nodeHash[row];
    while(curr){
        if(strCmp(key, curr -> key)) {
            res = curr -> value;
            temp -> next = curr -> next;
            break;
        }
        temp = curr;
        curr = curr -> next;
    }
    return res;
}