#define MAXM    3
#define MSG_MAX 100001
#define UID_MAX 1001
 
typedef struct Node
{
    //int cTimestamp;
    int sendID;
    int recvID;
    int schTimestamp;
    int isSentBoxRead; // 1: read
    int isInBoxRead; // 1: read
    int isSentBoxDeleted; // 1: deleted
    int isInBoxDeleted; // 1: deleted
    int mID; // Node Number
    Node* snext;
    Node* inext;
}Node;
 
Node data[MSG_MAX];
int di = 1;
 
#define UID_SENT 0
#define UID_IN 1
#define UID_INOUT_MAX 2
Node* uid_tb[UID_MAX][UID_INOUT_MAX]; // 0: Sent 1: In
 
typedef struct Heap
{
    int mID; // Node Number
    int value; //  schTimestamp;
}Heap;
 
Heap heap[MSG_MAX];
int heapSize = 0;
 
void init(int N)
{
    di = 1;
    heapSize = 0;
    register int i, j;
 
    for (i = 0; i < MSG_MAX; i++)
    {
        heap[i].mID = 0;
        heap[i].value = 0;
    }
 
    for (i = 0; i < UID_MAX; i++)
        for (j = 0; j < UID_INOUT_MAX; j++)
            uid_tb[i][j] = 0;
 
}
 
//TODO : 포인터를 가지는 힙으로 동작하게 만들기
int heapPush(int mID, int value)
{
    if (heapSize + 1 > MSG_MAX)
        return 0;
 
    //맨뒤에 값을 넣는다
    heap[heapSize].mID = mID;
    heap[heapSize].value = value;
 
    //parent 가 크면 swap, 작은게 앞으로
    int current = heapSize;
    while (current > 0 && heap[current].value < heap[(current - 1) / 2].value)
    {
        int temp = heap[(current - 1) / 2].value;
        heap[(current - 1) / 2].value = heap[current].value;
        heap[current].value = temp;
        temp = heap[(current - 1) / 2].mID;
        heap[(current - 1) / 2].mID = heap[current].mID;
        heap[current].mID = temp;
 
        current = (current - 1) / 2;
    }
 
    heapSize = heapSize + 1;
 
    return 1;
}
 
int heapPop()
{
    if (heapSize <= 0)
        return -1;
 
    heapSize = heapSize - 1;
 
    heap[0].mID = heap[heapSize].mID;
    heap[0].value = heap[heapSize].value;
 
    int current = 0;
    while (current * 2 + 1 < heapSize)
    {
        int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = heap[current * 2 + 1].value < heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (heap[current].value < heap[child].value)
        {
            break;
        }
 
        int temp = heap[current].value;
        heap[current].value = heap[child].value;
        heap[child].value = temp;
        temp = heap[current].mID;
        heap[current].mID = heap[child].mID;
        heap[child].mID = temp;
 
        current = child;
    }
    return 1;
}
 
int action(int cTimestamp)
{
    while (cTimestamp >= heap[0].value && heapSize > 0)
    {
        if (data[heap[0].mID].isSentBoxDeleted == 0)
        {
            //add heap[0] to uID inbox list
            int uid = data[heap[0].mID].recvID;
            Node* cur = &data[heap[0].mID];
            cur->inext = uid_tb[uid][UID_IN];
            uid_tb[uid][UID_IN] = cur;
        }
 
        //update heap
        heapPop();
    }
 
    return 1;
}
 
void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
    Node* cur = &data[di++];
     
    //sendbox on sendID
    cur->sendID = uID1;
    cur->recvID = uID2;
    cur->schTimestamp = scheduleTimestamp;
    cur->isSentBoxRead = 0;
    cur->isInBoxRead = 0;
    cur->isSentBoxDeleted = 0;
    cur->isInBoxDeleted = 0;
 
    cur->mID = di - 1;
 
    //uid's send
    cur->snext = uid_tb[uID1][UID_SENT];
    uid_tb[uID1][UID_SENT] = cur;
    cur->inext = nullptr;
 
    //add to heap
    heapPush(cur->mID, cur->schTimestamp);
 
    //action
    action(cTimestamp);
}
 
int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    action(cTimestamp);
 
    int i = 0;
    Node* cur = uid_tb[uID][UID_SENT];
 
    while (cur && i < 3)
    {
        if (cur->isSentBoxDeleted == 0)
        {
            mIDList[i] = cur->mID;
            uIDList[i] = cur->recvID;
 
            int checkuID = data[cur->mID].recvID;
            int checkmID = cur->mID;
 
            Node* cur2 = uid_tb[checkuID][UID_IN];
            while (cur2 != nullptr && cur2->inext != nullptr && cur2->mID != checkmID)
                cur2 = cur2->inext;
 
            if(cur2 == nullptr || (cur2->inext == nullptr && cur2->mID != checkmID))
                readList[i] = 0;
            else
                readList[i] = cur2->isInBoxRead;
 
            i++;
        }
 
        cur = cur->snext;
    }
 
    return i;
}
 
int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    action(cTimestamp);
 
    int i = 0;
    Node* cur = uid_tb[uID][UID_IN];
 
    while (cur && i < 3)
    {
        if (cur->isInBoxDeleted == 0)
        {
            mIDList[i] = cur->mID;
            uIDList[i] = cur->sendID;
            readList[i] = cur->isInBoxRead;
 
            i++;
        }
        cur = cur->inext;
    }
 
    return i;
}
 
int readMessage(int cTimestamp, int uID, int mID)
{
    int result = 0;
    action(cTimestamp);
 
    //Find mID on UID, change to read
    Node* cur = uid_tb[uID][UID_SENT];
    while (cur)
    {
        if (cur->mID == mID && cur->isSentBoxDeleted == 0)
        {
            cur->isSentBoxRead = 1;
            result++;
        }
        cur = cur->snext;
    }
    cur = uid_tb[uID][UID_IN];
    while (cur)
    {
        if (cur->mID == mID && cur->isInBoxDeleted == 0)
        {
            cur->isInBoxRead = 1;
            result++;
        }
        cur = cur->inext;
    }
    if (result > 0) return 1;
    else return 0;
}
 
int deleteMessage(int cTimestamp, int uID, int mID)
{
    int result = 0;
    action(cTimestamp);
 
    //Find mID on UID, change to delete
    Node* cur = uid_tb[uID][UID_SENT];
    while (cur)
    {
        if (cur->mID == mID && cur->isSentBoxDeleted == 0)
        {
            cur->isSentBoxDeleted = 1;
            result++;
        }
        cur = cur->snext;
    }
    cur = uid_tb[uID][UID_IN];
    while (cur)
    {
        if (cur->mID == mID && cur->isInBoxDeleted == 0)
        {
            cur->isInBoxDeleted = 1;
            result++;
        }
        cur = cur->inext;
    }
 
    if (result > 0) return 1;
    else return 0;
}