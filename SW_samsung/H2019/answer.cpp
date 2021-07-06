#define MAX_NAME_LEN (4+1)
 
void mstrcpy(char dst[], const char src[]) {
    int c = 0;
    while ((dst[c] = src[c]) != '\0') ++c;
}
 
int mstrcmp(const char str1[], const char str2[]) {
    int c = 0;
    while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
    return str1[c] - str2[c];
}
 
#define MAX_ACCOUNT_NUM 100000
#define MAX_USER_NUM 30000
#define MAX_GROUP_NUM 20
 
#define rint register int
#define NULL 0
 
#define CMD_OPEN 0
#define CMD_SEND 1
#define CMD_RECEIVE 2
 
typedef struct _ACCOUNT
{
    int accountNum;
    int time;
    int recentCmd;
    int balance;
    bool isClosed;
    char userName[MAX_NAME_LEN];
    int groupKey;
    struct _ACCOUNT *next, *prev;
} ACCOUNT;
ACCOUNT myArrAccount[MAX_ACCOUNT_NUM + 1];
ACCOUNT *myArrAccountAlloc(int time, int assets, int number, char userName[], int groupKey)
{
    ACCOUNT *a = &myArrAccount[number];
    a->accountNum = number;
    a->time = time, a->recentCmd = CMD_OPEN, a->balance = assets; a->isClosed = false;
    mstrcpy(a->userName, userName);
    a->groupKey = groupKey;
    a->prev = a->next = NULL;
    return a;
}
 
int getHashKey(char name[])
{
    int key = 0;
    for (rint i = 0; name[i]; i++)
        key = key * 26 + name[i] - 'a' + 1;
 
    return key;
}
 
typedef struct _ACCOUNTLIST
{
    ACCOUNT head, tail;
    void init()
    {
        head.next = &tail;
        tail.prev = &head;
    }
    ACCOUNT *getFirstNode()
    {
        if (head.next == &tail)
            return NULL;
        else
            return head.next;
    }
    void addAtFront(ACCOUNT *a)
    {
        a->next = head.next;
        a->prev = &head;
        a->next->prev = a;
        a->prev->next = a;
    }
    void del(ACCOUNT *e)
    {
        if(e->next) e->next->prev = e->prev;
        e->prev->next = e->next;
    }
} ACCOUNTLIST;
 
typedef struct _USER
{   
    int key;
    char name[MAX_NAME_LEN];
    ACCOUNTLIST alist;
    int id;
    struct _USER *next; // for hash table
} USER;
USER myArrUser[MAX_USER_NUM];
int myArrUserId;
USER *myArrUserAlloc(int key, char name[])
{
    USER *u = &myArrUser[myArrUserId++];
    u->key = key;
    mstrcpy(u->name, name);
    u->alist.init();
    u->id = myArrUserId - 1;
    return u;
}
#define USER_HASH_TBL_SIZE (2 * MAX_USER_NUM + 1)
USER hashUserTable[USER_HASH_TBL_SIZE];
USER *findUserHashTable(char name[])
{
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
USER* addUserHashTable(char name[])
{
    int key = getHashKey(name);
    USER *prev = &hashUserTable[key%USER_HASH_TBL_SIZE];
    USER *u = myArrUserAlloc(key, name);
    u->next = prev->next;
    prev->next = u;
 
    return u;
}
 
typedef struct _GROUP
{
    int key;
    char name[MAX_NAME_LEN];
    int userCnt;
    int userList[MAX_USER_NUM];
    int checkUser[MAX_USER_NUM];
    struct _GROUP *next; // for hash table
} GROUP;
GROUP myArrGroup[MAX_GROUP_NUM];
int myArrGroupId;
GROUP* myArrGroupAlloc(int key, char name[])
{
    rint i;
    GROUP *g = &myArrGroup[myArrGroupId++];
    g->key = key;
    g->userCnt = 0;
    mstrcpy(g->name, name);
    for (i = 0; i < MAX_USER_NUM; i++)
        g->checkUser[i] = 0;
    return g;
}
#define GROUP_HASH_TBL_SIZE 29
GROUP hashGroupTable[GROUP_HASH_TBL_SIZE];
GROUP *findGroupHashTable(char name[])
{
    int key = getHashKey(name);
    GROUP *prev = &hashGroupTable[key % GROUP_HASH_TBL_SIZE];
    while (prev->next)
    {
        if (prev->next->key == key)
            return prev->next;
        prev = prev->next;
    }
    return NULL;
}
GROUP* addGroupHashTable(char name[])
{
    int key = getHashKey(name);
    GROUP *prev = &hashGroupTable[key % GROUP_HASH_TBL_SIZE];
    GROUP *g = myArrGroupAlloc(key, name);
    g->next = prev->next;
    prev->next = g;
 
    return g;
}
 
void init() {
    rint i;
    for (i = 0; i <= MAX_ACCOUNT_NUM; i++)
        myArrAccount[i].isClosed = true;
    myArrGroupId = 0;
    for (i = 0; i < GROUP_HASH_TBL_SIZE; i++)
        hashGroupTable[i].next = NULL;
    myArrUserId = 0;
    for (i = 0; i < USER_HASH_TBL_SIZE; i++)
        hashUserTable[i].next = NULL;
}
 
void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset) {
    GROUP *g = findGroupHashTable(mGroup);
    if (g == NULL) g = addGroupHashTable(mGroup);
 
    USER *u = findUserHashTable(mName);
    if (u == NULL) u = addUserHashTable(mName);
 
    ACCOUNT *a = myArrAccountAlloc(mTime, mAsset, mNumber, mName, getHashKey(mGroup));
    u->alist.addAtFront(a);
 
    if (g->checkUser[u->id] == 0)
    {
        g->checkUser[u->id] = 1;
        g->userList[g->userCnt++] = u->id;
    }
}
 
int closeAccount(int mTime, int mNumber) {
    ACCOUNT *a = &myArrAccount[mNumber];
    a->isClosed = true;
    a->time = mTime;
 
    USER *u = findUserHashTable(a->userName);
    u->alist.del(a);
     
    return a->balance;
}
 
int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue) {
    if (mNumber < 1 || mNumber > MAX_ACCOUNT_NUM) return -1;
    if (mReceiveNumber < 1 || mReceiveNumber > MAX_ACCOUNT_NUM) return -1;
 
    ACCOUNT *sender = &myArrAccount[mNumber];
    ACCOUNT *receiver = &myArrAccount[mReceiveNumber];
    if (sender->isClosed == true || receiver->isClosed == true) return -1;
 
    if (sender->balance < mValue) return -1;
 
    sender->balance -= mValue;
    sender->time = mTime;
    sender->recentCmd = CMD_SEND;
 
    receiver->balance += mValue;
    receiver->time = mTime;
    receiver->recentCmd = CMD_RECEIVE;
 
    USER *senderU = findUserHashTable(sender->userName);
    senderU->alist.del(sender);
    senderU->alist.addAtFront(sender);
    USER *receiverU = findUserHashTable(receiver->userName);
    receiverU->alist.del(receiver);
    receiverU->alist.addAtFront(receiver);
 
    return receiver->balance;
}
 
int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue) {
    if (mNumber < 1 || mNumber > MAX_ACCOUNT_NUM) return -1;
    ACCOUNT *sender = &myArrAccount[mNumber];
    if (sender->isClosed == true) return -1;
    if (sender->balance < mValue) return -1;
 
    USER *u = findUserHashTable(mReceiveName);
    if (u == NULL) return -1;
 
    ACCOUNT *receiver = u->alist.getFirstNode();
    if (receiver == &u->alist.tail) return -1;
 
    sender->balance -= mValue;
    sender->time = mTime;
    sender->recentCmd = CMD_SEND;
 
    receiver->balance += mValue;
    receiver->time = mTime;
    receiver->recentCmd = CMD_RECEIVE;
 
    USER *senderU = findUserHashTable(sender->userName);
    senderU->alist.del(sender);
    senderU->alist.addAtFront(sender);
    USER *receiverU = findUserHashTable(receiver->userName);
    receiverU->alist.del(receiver);
    receiverU->alist.addAtFront(receiver);
 
    return receiver->balance;
}
 
void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue) {
    GROUP *g = findGroupHashTable(mGroup);
    rint i;
    for (i = 0; i < g->userCnt; i++)
    {
        USER *u = &myArrUser[g->userList[i]];
        ACCOUNT *prev = &u->alist.head;
        while (prev->next)
        {
            if (prev->next->groupKey == g->key)
            {
                prev->next->balance += mValue;
                prev->next->time = mTime;
                prev->next->recentCmd = CMD_RECEIVE;
 
                // list 제일 앞으로.
                ACCOUNT *temp = prev->next;
                u->alist.del(temp);
                u->alist.addAtFront(temp);
                break;
            }
            prev = prev->next;
        }
    }
}