const int MAXN = 100001;
const int HASH_SIZE = 30007;
typedef unsigned long long u64;

struct Node{
    u64 key;
    int data;
    Node* next;
}node_pool[MAXN], htable[HASH_SIZE];

int node_idx = 0;

u64 str2num(char* str){
    u64 value = 0;

    while(*str){
        value <<= 5;
        value |= *str++ & 0x1F;
    }

    return value;
}

void init() {
    node_idx = 0;
    for(register int i = 0; i < HASH_SIZE; i++){
        htable[i].next = 0;
    }
}

int find(char key[]){
    register u64 hkey = str2num(key);
    register int hvalue = hkey % HASH_SIZE;

    Node* temp = htable[hvalue].next;

    while(temp){
        if(temp->key == hkey){
            return temp->data;
        }
        temp = temp->next;
    }
    //원래 없을때 하는 행동도 보여줘야하는데 없음
}

void add(char key[], int data){
    register u64 hkey = str2num(key);
    register int hvalue = hkey % HASH_SIZE;

    Node* new_node = &node_pool[node_idx++];

    new_node -> key = hkey;
    new_node -> data = data;

    new_node -> next = htable[hvalue].next;
    htable[hvalue].next = new_node; // 앞에다 갖다놓음

}

