#define MAX_NODE 500000

struct Node{
    int bookHash;
    Node* prev, *next;
};
Node nodePool[MAX_NODE];
int nodeIdx;

Node* myalloc(){
    return &nodePool[nodeIdx++];
}

Node* listAdd(Node* base, int data, Node* newNode){
    Node* tmp = base -> next;
    newNode -> next = tmp;
    newNode -> prev = base;

    base -> next = newNode;
    tmp -> prev = newNode;

    newNode -> bookHash = data;
    return newNode;
}

void listDel(Node* target){
    target -> prev -> next = target -> next;
    target -> next -> prev = target -> prev;
}
/////////////////////////////////////////////////////////
#define MAX_TYPES_TABLE 1003
#define MAX_TAG_LEN 4
struct Type{
    char key[MAX_TAG_LEN];
    int id;
};
Type typeTable[MAX_TYPES_TABLE];

unsigned long typeHash(const char*str){
    unsigned long hash = 5381;
    int c;
    while(c = *str++){
        hash = ((hash << 5) + hash + c) % MAX_TYPES_TABLE;
    }
    return hash % MAX_TYPES_TABLE;
}

int mstrcmp(const char str1[], const car str2[]){
    int c = 0;
    while(str1[c] != '\0' && str1[c] == str2[c]) ++c;
    return str1[c] - str2[c];
}

int typeAddFind(const car *key){
    unsigned long h = typeHash(key);
    while(typeTable[h].key[0] != 0){
        if(mstrcmp(typeTable[h].key, key) == 0){ // 같으면
            return h;
        }
        h = (h + 1) % MAX_TYPES_TABLE; // 마이그레이션을 적용한것으로 보임
    }
    return h;
}
/////////////////////////////////////////////////////////////
#define MAX_BOOKS_TABLE 100003
#define MAX_NAME_LEN 7
struct Book{
    char key[MAX_NAME_LEN];
    int types[5];
    int typeCnt;
    int section;
    int dupCheck;
    Node* position[5];
};

Book bookTable[MAX_BOOKS_TABLE];
unsigned long bookHash(const char *str){
    unsigned long hash = 5381;
    int c;
    while(c = *str++) hash = ((hash << 5) + hash + c) % MAX_BOOKS_TABLE;
    return hash % MAX_BOOKS_TABLE;
}

int bookAddFind(const char* key){
    unsigned long h = bookHash(key);

    while(bookTable[h].key[0] != 0){
        if(mstrcmp(bookTable[h].key, key) == 0){
            return h;
        }
        h = (h + 1) % MAX_BOOKS_TABLE;
    }
    return h;
}

///////////////////////////////
#define MAX_SEC 101
#define MAX_TYPES 500
Node* head[MAX_SEC][MAX_TYPES];
Node* tail[MAX_SEC][MAX_TYPES];
int typeIdx;

void init(int M){
    nodeIdx = 0;
    typeIdx = 0;

    for(register int i = 0; i < MAX_SEC; i++){
        for(register int j = 0; j < MAX_TYPES; j++){
            head[i][j] = myalloc();
            tail[i][j] = myalloc();
            head[i][j] -> next = tail[i][j];
            tail[i][j] -> prev = head[i][j];
        }
    }

    for(register int i = 0; i < MAX_BOOKS_TABLE; i++){
        bookTable[i].key[0] = 0;
    }
    for(register int i = 0; i < MAX_TYPES_TABLE; i++){
        typeTable[i].key[0] = 0;
        typeTable[i].id = -1;
    }
}
void mstrcpy(char dst[], const char src[]){
    int c = 0;
    while( (dst[c] = src[c]) != '\0') ++c;
}

#define MAX_N 5
void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection){
    int bh = bookAddFind(mName);
    mstrcpy(bookTable[bh].key, mName);
    bookTable[bh].section = mSection;
    bookTable[bh].typeCnt = mTypeNum;

    for(register int i = 0; i < mTypeNum; i++){
        int th = typeAddFind(mTypes[i]);
        int tId = typeTable[th].id;
        if(tId == -1){
            tId = typeIdx++;
            typeTable[th].id = tId;
            mstrcpy(typeTable[th].key, mTypes[i]);
        }
        bookTable[bh].types[i] = tId;
        bookTable[bh].position[i] = listAdd(head[mSection][tId], bh, myalloc());
    }
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo){
    
}
