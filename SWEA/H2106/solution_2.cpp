bool mstrcmp(const char str1[], const char str2[]){

}
void mstrcpy(char dest[],const char str[]){

}

#define MAX_NODE 402000
struct BookNode{
    BookNode *prev, *next;
    int book_hash_id;
}BOOKNODE[MAX_NODE];
int bookNodeID;
BookNode* alloc_book_node(int h){
    BOOKNODE[bookNodeID].prev = 0;
    BOOKNODE[bookNodeID].next = 0;
    BOOKNODE[bookNodeID].book_hash_id = h;
    return &BOOKNODE[bookNodeID++];
}
//////////////////////////////////////////
#define MAX_TYPE 501
struct Type{
    char type[3];
    int idx; // 1 ~ 500을 의미
    Type* next;
}TYPE[MAX_TYPE];
int typeID;
Type* alloc_type(){
    typeID++;
    TYPE[typeID].idx = typeID;
    TYPE[typeID].next = 0;
    return &TYPE[typeID];
}
//////////////////////////////////////////
#define HASH_TYPE 1009
Type* hash_type[HASH_TYPE];
int hashing_type(char type[]){
    unsigned long h = 5381;
    int c;
    while(c = *type++)
        h = ((h << 5) + h + c) % HASH_TYPE;
    return h % HASH_TYPE;
}
int getTypeIndex(char type[]){
    int h = hashing_type(type);
    Type * curr = hash_type[h];
    if(curr == 0){ // 없을떄
        curr = alloc_type();
        return curr -> idx;
    }

    while(curr){
        if(mstrcmp(curr -> type, type)) return curr -> idx;
        curr = curr -> next;
    }
    curr = alloc_type();
    return curr -> idx;
}
//////////////////////////////////////////
#define MAX_BOOK 80001
struct Book{
    int typeLen;
    int typeIdx[5];
    int section;
    Book* next;
    BookNode* target[5];
}BOOK[MAX_BOOK];
int bookID;
Book* alloc_book(int typeLen, int typeIdx[],int section){
    BOOK[bookID].typeLen = typeLen;
    for(register int i = 0; i < typeLen; i++) BOOK[bookID].typeIdx[i] = typeIdx[i];
    BOOK[bookID].section = section;
    BOOK[bookID].next = 0;
    return &BOOK[bookID++];
}
//////////////////////////////////////////
#define HASH_BOOK 100019
Book* hash_book[HASH_BOOK];
int hashing_book(char name[]){
    unsigned long h = 5381;
    int c;
    while(c = *name++)
        h = ((h << 5) + h + c) % HASH_BOOK;
    return h % HASH_BOOK;
}
//TODO 
//////////////////////////////////////////
#define MAX_SECTION 101
struct Section{
    BookNode* head[MAX_TYPE];
    BookNode* tail[MAX_TYPE];
    int cnt[MAX_TYPE];
}SECTION[MAX_TYPE];
int sectionID;
//////////////////////////////////////////



//////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////
void init(int M){
    bookNodeID = 0;
    typeID = 0;
    for(register int i = 1; i <= M; i++){
        for(register int j = 1; j <= MAX_TYPE; j++){
            SECTION[i].head[j] = alloc_book_node(0);
            SECTION[j].tail[j] = alloc_book_node(0);

            SECTION[i].head[j] -> next = SECTION[i].tail[j];
            SECTION[i].tail[j] -> prev = SECTION[i].head[j];

            SECTION[i].cnt[j] = 0;
        }
    }

    for(register int i = 0; i < HASH_TYPE; i++) hash_type[i] = 0;

}
void add(char mName[], int mTypeNum, char mTypes[][], int mSection){

}
int moveType(char mType[], int mFrom, int mTo){

}
void moveName(char mName[], int mSection){

}
void deleteName(char mName[]){

}
int countBook(int mTypeNum, char mTypes[][], int mSection){

}