#define MAX_NEWS 50001
#define SECTION 10
#define MAX_USER 100001
////////////////////////////////////////////////////
struct News{
    int newsId; // idx
    int heapId;
    int section;
    int readCnt;
    int sum;
    bool use;
    bool operator<(News &l){
        if(readCnt )
    }
}poolNews[MAX_NEWS];

////////////////////////////////////////////////////
struct User{
    int likeSec;
}poolUser[MAX_USER];
////////////////////////////////////////////////////
News* topList[SECTION][10];
int topLen;
void pushTopTen(News* target, int section){
    int plusPoint = 10;
    // News -> sum 을 확인한다
}
////////////////////////////////////////////////////
News* heap[SECTION][MAX_NEWS];
int heapLen[SECTION];
void push(int section, News* newNews){
    newNews -> heapId = heapLen[section];
    heap[section][ heapLen[section]] = newNews;
    heapLen[section]++;

    int curr = heapLen[section] - 1;
    while(curr != 0){

    }
    //newNews에 heapIdx 꼭 변경해줘야함
    //heapLen[section]++ 필수

    //완료가 되면 0를 push top ten 한다..
}
News* top(int section){

}
void update(int section, int heapIdx){

}
void remove(int section, int heapId){

}
////////////////////////////////////////////////////

void init(){
    for(register int i = 1; i < MAX_NEWS; i++)
        poolNews[i].use = false;
    for(register int i = 1; i < MAX_USER; i++)
        poolUser[i].likeSec = -1;
    for(register int i = 0; i < SECTION; i++) heapLen[i] = 0;
    
    topLen = 0;
}

void addNews(int mSection, int mNewsId){
    //뉴스 추가
    poolNews[mNewsId].use = true;
    poolNews[mNewsId].newsId = mNewsId;
    poolNews[mNewsId].heapId = -1;
    poolNews[mNewsId].section = mSection;
    poolNews[mNewsId].readCnt = 0;

    // 힙에 추가
    int section = poolNews[mNewsId].section;
    push(section, &poolNews[mNewsId]);
}

void eraseNews(int mNewsId){
    poolNews[mNewsId].use = false;
    remove(poolNews[mNewsId].section, poolNews[mNewsId].heapId);
}

void readNews(int mUserId, int mNewsId){
    News* targetNews = &poolNews[mNewsId];

    if(targetNews -> use == false) return;

    poolUser[mUserId].likeSec = targetNews -> section;
}

void changeSection(int mNewsId, int mSection){
    News* targetNews = &poolNews[mNewsId];

    if(targetNews -> use == false) return;

    remove(targetNews -> section, targetNews -> heapId);
    targetNews -> section = mSection;
    push(targetNews -> section, targetNews);
}

int getList(int mUserId, int mList[]){
    int preference = poolNews[mUserId].section;
    int res = 0;
    for(register int i = 0; i < topLen; i++){
        mList[i] = topList[i] -> newsId;
    }
	return topLen;
}