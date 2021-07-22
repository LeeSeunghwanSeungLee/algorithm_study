#define MAXN 100
#define MAXL 8
#define MAX_PQ 20000
#define MAX_USER 10000
#define MAX_BICYCLE 20000
#define MAX_TABLE 16383
 
void mystrcpy(char dst[], const char src[])
{
    int c = 0;
    while ((dst[c] = src[c]) != 0) ++c;
}
 
int mystrcmp(const char str1[], const char str2[])
{
    int c = 0;
    while (str1[c] != 0 && str1[c] == str2[c]) ++c;
    return str1[c] - str2[c];
}
 
unsigned long gethash(const char *str)
{
    unsigned long hash = 5381;
    int c;
 
    while (c = *str++)
    {
        hash = (((hash << 5) + hash) + c) % MAX_TABLE;
    }
 
    return hash % MAX_TABLE;
}
 
int user_cnt;
struct BICYCLE
{
    int start_time;
    int ride_time;
};
 
int alloc_idx;
BICYCLE alloc_node[3*(MAX_BICYCLE + 5)];
BICYCLE* myalloc_node(int start_time)
{
    BICYCLE* pnode = &alloc_node[alloc_idx++];
    pnode->start_time = start_time;
    pnode->ride_time = 0;
    return pnode;
}
 
void init_byclcle()
{
    alloc_idx = 0;
}
 
struct PQ
{
    BICYCLE* bicycle;
};
 
int max_durableTime;
 
struct STATION
{
    int deliveryTimes;
    int bicycleNum;
    PQ pq[MAX_PQ + 1];
    int lastnode;
    PQ pq2[MAX_PQ + 1];
    int lastnode2;
} station[MAXN + 5];
 
int PQ_COMPARE(BICYCLE* b1, BICYCLE* b2)
{
    return b1->ride_time - b2->ride_time;
}
 
int PQ2_COMPARE(BICYCLE* b1, BICYCLE* b2)
{
    return b1->start_time - b2->start_time;
}
 
void PQ_PUSH(BICYCLE* bicycle, int id)
{
    if (station[id].lastnode == MAX_PQ) { return; }
    ++station[id].lastnode;
 
    PQ* p_pq = &station[id].pq[station[id].lastnode];
    p_pq->bicycle = bicycle;
    int c = station[id].lastnode;
    int p = c / 2;
 
    while (p > 0) {
        BICYCLE* b1 = station[id].pq[c].bicycle;
        BICYCLE* b2 = station[id].pq[p].bicycle;
        int cmp = b1->ride_time - b2->ride_time;
        //int cmp = PQ_COMPARE(b1, b2);
        if (cmp < 0) {
            BICYCLE* tmp = station[id].pq[c].bicycle;
            station[id].pq[c].bicycle = station[id].pq[p].bicycle;
            station[id].pq[p].bicycle = tmp;
            c = p;
            p = c / 2;
        }
        else {
            break;
        }
    }
}
 
void PQ2_PUSH(BICYCLE* bicycle, int id)
{
    if (station[id].lastnode2 == MAX_PQ) { return; }
    ++station[id].lastnode2;
 
    PQ* p_pq = &station[id].pq2[station[id].lastnode2];
    p_pq->bicycle = bicycle;
    int c = station[id].lastnode2;
    int p = c / 2;
 
    while (p > 0) {
        BICYCLE* b1 = station[id].pq2[c].bicycle;
        BICYCLE* b2 = station[id].pq2[p].bicycle;
        int cmp = PQ2_COMPARE(b1, b2);
        if (cmp < 0) {
            BICYCLE* tmp = station[id].pq2[c].bicycle;
            station[id].pq2[c].bicycle = station[id].pq2[p].bicycle;
            station[id].pq2[p].bicycle = tmp;
            c = p;
            p = c / 2;
        }
        else {
            break;
        }
    }
}
 
BICYCLE* PQ_POP(int id)
{
    if (station[id].lastnode == 0) { return (BICYCLE*)0; }
    BICYCLE* ret = station[id].pq[1].bicycle;
    station[id].pq[1] = station[id].pq[station[id].lastnode--];
 
    int p = 1, c, lc = 2, rc = 3;
    BICYCLE* b1;
    BICYCLE* b2;
    while (lc <= station[id].lastnode) {
        if (lc == station[id].lastnode) { c = lc; }
        else {
            b1 = station[id].pq[lc].bicycle;
            b2 = station[id].pq[rc].bicycle;
            int cmp2 = b1->ride_time - b2->ride_time;
            c = cmp2<0 ? lc : rc;
        }
        b1 = station[id].pq[c].bicycle;
        b2 = station[id].pq[p].bicycle;
        //int cmp = PQ_COMPARE(b1, b2);
        int cmp = b1->ride_time - b2->ride_time;
        if (cmp < 0) {
            BICYCLE* tmp = station[id].pq[c].bicycle;
            station[id].pq[c].bicycle = station[id].pq[p].bicycle;
            station[id].pq[p].bicycle = tmp;
            p = c;
            lc = 2 * p;
            rc = 2 * p + 1;
        }
        else {
            break;
        }
    }
    return ret;
}
 
BICYCLE* PQ2_POP(int id)
{
    if (station[id].lastnode2 == 0) { return (BICYCLE*)0; }
    BICYCLE* ret = station[id].pq2[1].bicycle;
    station[id].pq2[1] = station[id].pq2[station[id].lastnode2--];
 
    int p = 1, c, lc = 2, rc = 3;
    BICYCLE* b1;
    BICYCLE* b2;
    while (lc <= station[id].lastnode2) {
        if (lc == station[id].lastnode2) { c = lc; }
        else {
            b1 = station[id].pq2[lc].bicycle;
            b2 = station[id].pq2[rc].bicycle;
            c = PQ2_COMPARE(b1, b2)<0 ? lc : rc;
        }
        b1 = station[id].pq2[c].bicycle;
        b2 = station[id].pq2[p].bicycle;
        int cmp = PQ2_COMPARE(b1, b2);
        if (cmp < 0) {
            BICYCLE* tmp = station[id].pq2[c].bicycle;
            station[id].pq2[c].bicycle = station[id].pq2[p].bicycle;
            station[id].pq2[p].bicycle = tmp;
            p = c;
            lc = 2 * p;
            rc = 2 * p + 1;
        }
        else {
            break;
        }
    }
    return ret;
}
 
PQ* PQ2_TOP(int id){
    return &station[id].pq2[1];
}
 
void init_station()
{
    for (int i = 0; i < MAXN + 5; i++) {
        station[i].deliveryTimes = 0;
        station[i].bicycleNum = 0;
        station[i].lastnode = 0;
        station[i].lastnode2 = 0;
    }
}
 
struct TICKET
{
    int time_buy;
    int time_valid;
};
 
struct USER
{
    char name[MAXL];
    int isTicketBuy;
    TICKET ticketinfo;
    int rent_time;
    BICYCLE* bicycle;
} user[MAX_USER + 5];
 
struct HASH
{
    char name[MAXL];
    int id;
    HASH* next;
    HASH* prev;
} HT[MAX_TABLE];
 
int alloc_hash_idx;
HASH alloc_hash_node[MAX_TABLE];
HASH* myalloc_hash(char* name, int id) {
    HASH* phash = &alloc_hash_node[alloc_hash_idx++];
    mystrcpy(phash->name, name);
    phash->id = id;
    phash->next = (HASH*)0;
    phash->prev = (HASH*)0;
    return phash;
}
 
HASH* insert_HT(char* name)
{
    unsigned long key = gethash(name);
    HASH* prev = &HT[key];
    while (prev->next) {
        int cmp = mystrcmp(name, prev->next->name);
        if (cmp < 0) {
            break;
        }
        prev = prev->next;
    }
    HASH* newnode = myalloc_hash(name, user_cnt++);
    newnode->next = prev->next;
    newnode->prev = prev;
    newnode->prev->next = newnode;
    if (newnode->next){
        newnode->next->prev = newnode;
    }
    return newnode;
}
 
HASH* search_HT(char* name)
{
    unsigned long key = gethash(name);
    HASH* node = HT[key].next;
    while (node) {
        int cmp = mystrcmp(name, node->name);
        if (cmp == 0) {
            return node;
        }
        if (cmp < 0) {
            return (HASH*)0;
        }
        node = node->next;
    }
    return (HASH*)0;
}
 
void init_user()
{
    for (int i = 0; i < MAX_USER + 5; i++){
        for (int j = 0; j < MAXL; j++){
            user[i].name[j] = 0;
        }
        user[i].isTicketBuy = 0;
        user[i].ticketinfo.time_buy = 0;
        user[i].ticketinfo.time_valid = 0;
        user[i].rent_time = 0;
        user[i].bicycle = (BICYCLE*)(0);
    }
 
    for (int i = 0; i < MAX_TABLE; i++) {
        HT[i].id = 0;
        for (int j = 0; j < MAXL; j++) {
            HT[i].name[j] = 0;
        }
        HT[i].next = (HASH*)0;
    }
    alloc_hash_idx = 0;
    user_cnt = 0;
}
 
int cur_time;
 
void init(int N, int durableTime, int deliveryTimes[MAXN])
{
    init_byclcle();
    init_station();
    init_user();
    cur_time = 0;
    max_durableTime = durableTime;
 
    for (int i = 0; i < N; i++) {
        station[i].deliveryTimes = deliveryTimes[i];
    }
}
 
void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
    cur_time = cTimestamp;
    station[pID].bicycleNum += bicycleNum;
    for (int i = 0; i < bicycleNum; i++) {
        BICYCLE* new_bicycle = myalloc_node(cTimestamp);
        new_bicycle->start_time = cur_time;
        PQ_PUSH(new_bicycle, pID);
    }
}
 
int checkUser(char uName[MAXL])
{
    HASH* node = search_HT(uName);
    if (node == (HASH*)0) {
        node = insert_HT(uName);
        mystrcpy(user[node->id].name, uName);
    }
    return node->id;
}
 
void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
{
    cur_time = cTimestamp;
    int id = checkUser(uName);
    int TicketBuy = user[id].isTicketBuy;
    int TicketValidTime = (user[id].ticketinfo.time_buy + user[id].ticketinfo.time_valid - 1) - cTimestamp;
    int TicketValid = (TicketValidTime >= 0) ? 1 : 0;
 
    if (TicketBuy && TicketValid) {
        user[id].ticketinfo.time_valid += validTime;
    }
    else {
        user[id].isTicketBuy = 1;
        user[id].ticketinfo.time_buy = cTimestamp;
        user[id].ticketinfo.time_valid = validTime;
    }
}
 
int check_rentBicycle(int userID, int pID)
{
    //update station
    if (station[pID].lastnode2 > 0) {
        PQ* tmp = &station[pID].pq2[1];
        if (tmp->bicycle->start_time <= cur_time) {
            station[pID].bicycleNum++;
            BICYCLE* new_bicycle = PQ2_POP(pID);
            PQ_PUSH(new_bicycle, pID);
        }
    }
 
    if (station[pID].bicycleNum == 0) { return 0; }
    else if (user[userID].bicycle && user[userID].rent_time > 0) { return 0; }
    else if (user[userID].isTicketBuy == 0) { return 0; }
    else if (((user[userID].ticketinfo.time_buy + user[userID].ticketinfo.time_valid - 1) - cur_time)<0) {
        return 0;
    }
    else { return 1; }
}
 
int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    int userid = checkUser(uName);
    int ret = -1;
    cur_time = cTimestamp;
 
    if (check_rentBicycle(userid, pID))
    {
        station[pID].bicycleNum--;
        BICYCLE* rent_bicycle = PQ_POP(pID);
        user[userid].rent_time = cur_time;
        user[userid].bicycle = rent_bicycle;
        ret = rent_bicycle->ride_time;
    }
 
    return ret;
}
 
void returnBicycleToStation(int userid, int pID)
{
    BICYCLE* rent = user[userid].bicycle;
    rent->ride_time += cur_time - user[userid].rent_time;
    user[userid].rent_time = 0;
 
    if (rent->ride_time > max_durableTime) {
        //rent = (BICYCLE*)0;
        BICYCLE* newbicycle = myalloc_node(cur_time + station[pID].deliveryTimes);
        PQ2_PUSH(newbicycle, pID);
    }
    else {
        station[pID].bicycleNum++;
        PQ_PUSH(rent, pID);
    }
}
 
int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    int ret = 0;
    cur_time = cTimestamp;
    int userid = checkUser(uName);
 
    if (user[userid].rent_time == 0) {
        ret = -1;
    }
    else {
        returnBicycleToStation(userid, pID);
        int TicketValidTime = (user[userid].ticketinfo.time_buy + user[userid].ticketinfo.time_valid - 1);
        int TicketValid = (TicketValidTime - cTimestamp >= 0) ? 1 : 0;
        if (TicketValid) {
            ret = 0;
        }
        else {
            ret = cur_time - TicketValidTime;
        }
    }
 
    return ret;
}