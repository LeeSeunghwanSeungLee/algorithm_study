#define MAX_LEN 100001
#define GROUP 6
//////////////////////////////////////////
struct Soldier{
    int sID;
    int gID;
    int hID;
    int score;
}poolSoldier[MAX_LEN];
//////////////////////////////////////////
Soldier* heap[GROUP][MAX_LEN];
int heapID[GROUP];
//////////////////////////////////////////
void up(int gId, int hId){
    int curr = hId;
    while(curr > 0){
        int parent = (curr - 1) / 2;
        if(heap[gId][parent] -> score > heap[gId][curr] -> score) break;
        else if(heap[gId][parent] -> score == heap[gId][curr] -> score && heap[gId][parent] -> sID > heap[gId][curr] -> sID) break;

        int aTmp = heap[gId][curr] -> hID;
        heap[gId][curr] -> hID = heap[gId][parent] ->hID;
        heap[gId][parent]->hID = aTmp;

        Soldier* sTmp = heap[gId][curr];
        heap[gId][curr] = heap[gId][parent];
        heap[gId][parent] = sTmp;

        curr = parent;
    }
}
void down(int gId, int hId){
    int curr = hId;
    while(2*curr + 1 < heapID[gId]){
        int child;
        if(2*curr + 2 == heapID[gId]) child = 2 * curr + 1;
        else child = (heap[gId][2 * curr + 1] -> score > heap[gId][2 * curr + 2] -> score || (heap[gId][2 * curr + 1] -> score == heap[gId][2 * curr + 2] -> score && heap[gId][2 * curr + 1] -> sID > heap[gId][2 * curr + 2] -> sID))? 2 * curr + 1 : 2 * curr + 2;

        if(heap[gId][curr] -> score > heap[gId][child] -> score) break;
        else if(heap[gId][curr] -> score == heap[gId][child] -> score && heap[gId][curr] -> sID > heap[gId][child] ->sID) break;

        int aTmp = heap[gId][curr] -> hID;
        heap[gId][curr] -> hID = heap[gId][child] ->hID;
        heap[gId][child]->hID = aTmp;

        Soldier* sTmp = heap[gId][curr];
        heap[gId][curr] = heap[gId][child];
        heap[gId][child] = sTmp;

        curr = child;
    }
}
void pushHeap(int gId, Soldier* newSoldier){
    newSoldier -> hID = heapID[gId];
    heap[gId][heapID[gId]] = newSoldier;
    
    int curr = heapID[gId];
    while(curr > 0){
        int parent = (curr - 1) / 2;
        if(heap[gId][parent] -> score > heap[gId][curr] -> score) break;
        else if(heap[gId][parent] -> score == heap[gId][curr] -> score && heap[gId][parent] -> sID > heap[gId][curr] -> sID) break;

        int aTmp = heap[gId][curr] -> hID;
        heap[gId][curr] -> hID = heap[gId][parent] ->hID;
        heap[gId][parent]->hID = aTmp;

        Soldier* sTmp = heap[gId][curr];
        heap[gId][curr] = heap[gId][parent];
        heap[gId][parent] = sTmp;

        curr = parent;
    }

    heapID[gId]++;
}
void removeHeap(int gId, int hId){
    heapID[gId]--;
    heap[gId][hId] = heap[gId][heapID[gId]];
    heap[gId][hId] -> hID = hId;
    up(gId, hId);
    down(gId, hId);
}
Soldier* popHeap(int gId){
    Soldier* res = heap[gId][0];

    heapID[gId]--;
    heap[gId][0] = heap[gId][heapID[gId]];
    heap[gId][0] -> hID = 0;
    down(gId, 0);

    return res;
}

//////////////////////////////////////////

void init(){
    for(int i = 1; i <= 5; i++) heapID[i] = 0;
}

void hire(int mID, int mTeam, int mScore){
    poolSoldier[mID].sID = mID;
    poolSoldier[mID].gID = mTeam;
    poolSoldier[mID].score = mScore;
    pushHeap(mTeam, &poolSoldier[mID]);
}

void fire(int mID){
    Soldier* aTarget = &poolSoldier[mID];
    removeHeap(aTarget -> gID, aTarget -> hID);
}

void updateSoldier(int mID, int mScore){
    Soldier* aTarget = &poolSoldier[mID];
    aTarget -> score = mScore;

    int groupId = aTarget -> gID;
    int heapId = aTarget -> hID;
    up(groupId, heapId);
    down(groupId, heapId);
;}

void updateTeam(int mTeam, int mChangeScore){
    int num = heapID[mTeam];
    Soldier* temp[MAX_LEN];
    for(int i = 0; i < num; i++){
        Soldier* aTarget = popHeap(mTeam);
        aTarget -> score = aTarget -> score + mChangeScore;
        if(aTarget -> score > 5) aTarget -> score = 5;
        else if(aTarget -> score < 1) aTarget -> score = 1;

        temp[i] = aTarget;
    }
    for(int i = 0; i < num; i++){
        pushHeap(mTeam, temp[i]);
    }
}

int bestSoldier(int mTeam){
    return heap[mTeam][0]->sID;   
}