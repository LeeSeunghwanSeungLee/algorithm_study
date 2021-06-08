#define MAXM 3
#define MSG_MAX 100001
#define UID_MAX 1001

typedef struct Node{
    int sendID;
    int recvID;
    int schTimestamp;
    int isSentBoxRead;
    int isInBoxRead;
    int isSentBoxDeleted;
    int isInBoxDeleted;
    int mID;
    Node* snext;
    Node* inext;
}Node;

Node data[MSG_MAX];
int di = 1;

#define UID_SENT 0
#define UID_IN 1
#define UID_INOUT_MAX 2
Node* uid_tb[UID_MAX][UID_INOUT_MAX];

typedef struct Heap{
    int mID;
    int value;
}Heap;

Heap heap[MSG_MAX];
int heapSize = 0;

void init(int N){
    di = 1;
    heapSize = 0;
    register int i, j;

    for(i = 0; i < MSG_MAX; i++){
        heap[i].mID = 0;
        heap[i].value = 0;
    }

    for(i = 0; i < UID_MAX; i++){
        for( j = 0; j < UID_INOUT_MAX; j++){
            uid_tb[i][j] = 0; // NULL 값으로 초기화한다
        }
    }
}

bool heapPush(int mID, int value){
    if(heapSize >= MSG_MAX) return false;

    //맨 뒤에 값을 넣는다
    heap[heapSize].mID = mID;
    heap[heapSize].value = value;

    int current = heapSize;
    while(current > 0 && heap[current].value < heap[(current - 1) / 2].value ){
        //swap
        Heap tmp = heap[current];
        heap[current] = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = tmp;

        current = (current - 1) / 2;
    }

    heapSize--;
    return true;
}

bool heapPop(){
    if(heapSize <= 0) return false;

    heapSize--;
    heap[0] = heap[heapSize];

    int current = 0;
    while(current * 2 + 1 < heapSize){
        int child;
        
        if(current * 2 + 2 == heapSize){
            child = current * 2 + 1;
        }
        else{
            child = heap[current * 2 + 1].value < heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2; 
        }

        if (heap[current].value < heap[child].value) break;

        Heap tmp = heap[current];
        heap[current] = heap[child];
        heap[child] = tmp;
        
        current = child;
    }
    return true;
}
// 특정 시간때마다 메시지박스 수신함에 나타나도록 해주기 위한 함수
int action(int cTimestamp){
    while(cTimestamp >= heap[0].value && heapSize >0){
        if(data[heap[0].mID].isSentBoxDeleted == 0){
            // add heap[0] to uID inbox list
            int uid = data[heap[0].mID].recvID;
            Node* cur = &data[heap[0].mID];
            cur -> inext = uid_tb[uid][UID_IN];
            uid_tb[uid][UID_IN] = cur;
        }
        heapPop();
    }
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp){
    Node* cur = &data[di++];

    cur -> sendID = uID1;
    cur -> recvID = uID2;
    cur -> schTimestamp = scheduleTimestamp;
    cur -> isSentBoxRead = 0;
    cur -> isInBoxRead = 0;
    cur -> isSentBoxDeleted = 0;
    cur -> isInBoxDeleted = 0;

    cur -> mID = di - 1;

    //uid's send
    cur -> snext = uid_tb[uID1][UID_SENT];
    uid_tb[uID1][UID_SENT] = cur;
    cur -> inext = nullptr;

    heapPush(cur -> mID, cur -> schTimestamp);

    action(cTimestamp);
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]){
    action(cTimestamp);

    int i = 0;
    Node* cur = uid_tb[uID][UID_SENT];

    while(cur && i < 3){
        if(cur -> isSentBoxDeleted == 0){
            mIDList[i] = cur -> mID;
            uIDList[i] = cur -> recvID;

            int checkuID = data[cur -> mID].recvID;
            int checkmID = cur -> mID;

            Node* cur2 = uid_tb[checkuID][UID_IN];
            while(cur2 != nullptr && cur2 -> inext != nullptr && cur2 -> mID != checkmID){
                cur2 = cur2 -> inext;
            }
            if(cur2 == nullptr || (cur2->inext == nullptr && cur2->mID != checkmID))
                readList[i] = 0;
            else   
                readList[i] = cur2 -> isInBoxRead;

            i++;
        }
        cur = cur -> snext;
    }
    return i;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]){
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

int readMessage(int cTimestamp, int uID, int mID){
    int result = 0;
    action(cTimestamp);

    Node* cur = uid_tb[uID][UID_SENT];
    while(cur){
        if(cur -> mID == mID && cur -> isSentBoxDeleted == 0){
            cur -> isSentBoxRead = 1;
            result++;
        }
        cur = cur -> snext;
    }

    cur = uid_tb[uID][UID_IN];
    while(cur){
        if(cur -> mID && cur -> isInBoxDeleted == 0){
            cur -> isInBoxRead = 1;
            result++;
        }
        cur = cur -> inext;
    }
    if(result > 0) return 1;
    return 0;
}

int deleteMessage(int ctimestamp, int uID, int mID){
    int result = 0;
    action(ctimestamp);

    //Find mID on UID, change to delete
    Node* cur = uid_tb[uID][UID_SENT];
    while(cur){
        if(cur -> mID == mID && cur -> isSentBoxDeleted == 0){
            cur -> isSentBoxDeleted = 1;
            result++;
        }
        cur = cur -> snext;
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
