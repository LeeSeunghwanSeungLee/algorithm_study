#define MAX_NAME_LEN (4+1)

void mstrcpy(char dst[], const char src[]){
    int c = 0;
    while((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]){
    int c = 0;
    while(str1[c] != '\0' && str1[c] == str2[c]) ++c;
    return str1[c] - str2[c];
}

#define MAX_ACCOUNT_NUM 100000
#define MAX_USER_NUM 30000
#define MAX_GROUP_NUM 20
#define NULL 0
#define CMD_OPEN 0
#define CMD_SEND 1
#define CMD_RECEIVE 2

typedef struct _ACCOUNT{
    int accountNum;
    int time;
    int recentCmd;
    int balance;
    bool isClosed;
    char userName[MAX_NAME_LEN];
    int grouopKey;
    _ACCOUNT *next, *prev;
}ACCOUNT;
ACCOUNT myArrAccount[MAX_ACCOUNT_NUM + 1];
ACCOUNT *myArrAccountAlloc(int time, int assets, int number, char userName[], int groupKey){
    ACCOUNT* a = &myArrAccount[number];
    a -> accountNum = number;
    a -> time = time;
    a -> recentCmd = CMD_OPEN;
    a -> balance = assets;
    a -> isClosed = false;
    mstrcpy(a -> userName, userName);
    a -> grouopKey = groupKey;
    a -> prev = a -> next = 0;
    return a;
}

int getHashKey(char name[])
{
    int key = 0;
    for (register int i = 0; name[i]; i++)
        key = key * 26 + name[i] - 'a' + 1;
    return key;
}

typedef struct _ACCOUNTLIST{
    ACCOUNT head, tail;
    void init(){
        head.next = &tail;
        tail.prev = &head;
    }
    ACCOUNT* getFirstNode(){
        if(head.next == &tail) return NULL;
        return head.next;
    }
    void addAtFront(ACCOUNT* a){
        a -> next = head.next;
        a -> prev = &head;

        head.next -> prev = a;
        head.next = a;
    }
    void del(ACCOUNT* e){
        if(e -> next) e -> next -> prev = e -> prev;
        e -> prev -> next = e -> next;
    }
} ACCOUNTLIST;

typedef struct _USER{
    int key;
    char name[MAX_NAME_LEN];
    ACCOUNTLIST alist;
    int id;
    struct _USER *next; // for hash table
} USER;
USER myArrUser[MAX_USER_NUM];
int myArrUserId;

USER* myArrUserAlloc(int key, char name[]){
    USER* u = &myArrUser[myArrUserId++];
    u -> key = key;
    mstrcpy(u -> name, name);
    u -> alist.init();
    u -> id = myArrUserId - 1;
    return u;
}

#define USER_HASH_TBL_SIZE ( 2 * MAX_USER_NUM + 1)
USER hashUserTable[USER_HASH_TBL_SIZE];

USER* addUserHashTable(char name[])
{
    int key = getHashKey(name);
    USER *prev = &hashUserTable[key%USER_HASH_TBL_SIZE];
    USER *u = myArrUserAlloc(key, name);
    u->next = prev->next;
    prev->next = u;
 
    return u;
}

USER* findUserHashTable(char name[]){
    int key = getHashKey(name);
    USER *prev = &hashUserTable[key%USER_HASH_TBL_SIZE];
    while (prev->next)
    {
        if (prev->next->key == key)
            return prev->next;
        prev = prev->next;
    }
    return NULL;
}

