#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT	100
#define CMD_ADD		200
#define CMD_BUY		300
#define CMD_RENT	400
#define CMD_RETURN	500

#define MAXN		100
#define MAXL		8

extern void init(int N, int durableTime, int deliveryTimes[MAXN]);
extern void addBicycle(int cTimestamp, int pID, int bicycleNum);
extern void buyTicket(int cTimestamp, char uName[MAXL], int validTime);
extern int rentBicycle(int cTimestamp, char uName[MAXL], int pID);
extern int returnBicycle(int cTimestamp, char uName[MAXL], int pID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 246247151 + 9543169;
	return (mSeed >> 16) & 0x7FFFFFFF;
}

static bool run()
{
	int Q;
	int N, durableTime, deliveryTimes[MAXN], cTimestamp, pID, bicycleNum, validTime;
	int res = -1, ans;

	char uName[MAXL];
	
	int dT;
	
	scanf("%d %d", &Q, &mSeed);

	bool okay = false;
	
	if (mSeed == 0)
	{
		for (int q = 0; q <= Q; ++q)
		{
			int cmd;
			scanf("%d", &cmd);

			switch(cmd)
			{
			case CMD_INIT:
				scanf("%d %d", &N, &durableTime);
				for (int i = 0; i < N; ++i)
					scanf("%d", &deliveryTimes[i]);
				init(N, durableTime, deliveryTimes);
				okay = true;
				break;
			case CMD_ADD:
				scanf("%d %d %d", &cTimestamp, &pID, &bicycleNum);
				if (okay)
					addBicycle(cTimestamp, pID, bicycleNum);
				break;
			case CMD_BUY:
				scanf("%d %s %d", &cTimestamp, uName, &validTime);
				if (okay)
					buyTicket(cTimestamp, uName, validTime);
				break;
			case CMD_RENT:
				scanf("%d %s %d", &cTimestamp, uName, &pID);
				if (okay)
					res = rentBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			case CMD_RETURN:
				scanf("%d %s %d", &cTimestamp, uName, &pID);
				if (okay)
					res = returnBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			}
		}
	}
	else
	{
		scanf("%d", &dT);
		
		cTimestamp = 0;

		for (int q = 0; q <= Q; ++q)
		{
			int cmd;
			scanf("%d", &cmd);

			switch(cmd)
			{
			case CMD_INIT:
				scanf("%d %d", &N, &durableTime);
				for (int i = 0; i < N; ++i)
					scanf("%d", &deliveryTimes[i]);
				init(N, durableTime, deliveryTimes);
				okay = true;
				break;
			case CMD_ADD:
				cTimestamp += pseudo_rand() % dT + 1; 
				scanf("%d %d", &pID, &bicycleNum);
				if (okay)
					addBicycle(cTimestamp, pID, bicycleNum);
				break;
			case CMD_BUY:
				cTimestamp += pseudo_rand() % dT + 1; 
				scanf("%s %d", uName, &validTime);
				if (okay)
					buyTicket(cTimestamp, uName, validTime);
				break;
			case CMD_RENT:
				cTimestamp += pseudo_rand() % dT + 1; 
				scanf("%s %d", uName, &pID);
				if (okay)
					res = rentBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			case CMD_RETURN:
				cTimestamp += pseudo_rand() % dT + 1; 
				scanf("%s %d", uName, &pID);
				if (okay)
					res = returnBicycle(cTimestamp, uName, pID);
				scanf("%d", &ans);
				if (res != ans)
					okay = false;
				break;
			}
		}
	}
	
	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;

		printf("#%d %d\n", tc, score);
	}

	return 0;
}


//////////////////////////////////////////
#define MAX_STATION 100
#define MAX_BICYCLE 20001
#define HASH_CUSTOM 10007

void mstrcpy(char target[], char str[]){
    while((*target++ = *str++) !=0);
}
int mstrcmp(char str1[], char str2[]){
    int c = 0;
    while(str1[c] == str2[c] && str1[c] != 0) c++;
    return str1[c] - str2[c];
}
///////////////
struct Bicycle{
    int lifeTime;
    int rideStart;
    int returnTime;
    int returnIdx;
}poolBicycle[MAX_BICYCLE];
int bikeID;
Bicycle* alloc_b(){
    return &poolBicycle[bikeID++];
}
///////////////
struct Customer{
    char name[8];
    int hID;
    int start, duration, end;
    Bicycle* riding;
    Customer* next; // hash
}poolCustom[HASH_CUSTOM];
Customer* getHash(char name[]){ // oppen addressing 활용
    int h = 5381;
    int c;
    while(c = *name++){
        h = ((h << 5) + c) % HASH_CUSTOM;
    }
    h = h % HASH_CUSTOM;
    Customer* ret = &poolCustom[h];
    while(ret -> name[0] != '?'){
        if(mstrcmp(ret -> name, name) == 0) return ret;
        ret = ret -> next;
    }
    mstrcpy(ret -> name, name);
    return ret;
}
/////////////
struct Station{
    Bicycle* ready[MAX_BICYCLE];
    int bikeNum;
    int deliveryTime;
}STATION[MAX_STATION];
void push(int sID, Bicycle* usedBike){
    Station* currStation = &STATION[sID];
    currStation -> ready[currStation -> bikeNum++] = usedBike;
    int curr = currStation -> bikeNum - 1;
    while(curr){
        int parent = (curr - 1) / 2;
        if (currStation -> ready[parent] -> lifeTime <= currStation -> ready[curr] -> lifeTime) break;

        Bicycle* tmp = currStation -> ready[parent];
        currStation -> ready[parent] = currStation -> ready[curr];
        currStation -> ready[curr] = tmp;

        curr = parent;
    }
}
Bicycle* top(int sID){
    Station *currStation = &STATION[sID];
    if(currStation -> bikeNum <= 0) return 0;
    return currStation -> ready[0];
}
Bicycle* pop(int sID){
    Station *currStation = &STATION[sID];
    if(currStation -> bikeNum <= 0) return 0;
    Bicycle* res;
    res = currStation -> ready[0];

    currStation -> bikeNum--;
    currStation -> ready[0] = currStation -> ready[currStation -> bikeNum];

    int curr = 0;
    while(curr * 2 + 1 < currStation -> bikeNum){
        int child;
        if(2 * curr + 2 == currStation -> bikeNum) child = 2 * curr + 1;
        else child = (currStation -> ready[2 * curr + 1] -> lifeTime < currStation -> ready[2 * curr + 2] -> lifeTime) ? 2 * curr + 1 : 2 * curr + 2;

        if(currStation -> ready[curr] -> lifeTime <= currStation -> ready[child] -> lifeTime) break;

        Bicycle* tmp = currStation -> ready[curr];
        currStation -> ready[curr] = currStation -> ready[child];
        currStation -> ready[child] = tmp;

        curr = child;
    }
    return res;
}
/////////////
Bicycle* fixHeap[MAX_BICYCLE];
int fixID;
void pushFix(Bicycle* repairedBiCycle, int pID){
    repairedBiCycle -> returnIdx = pID;
    fixHeap[fixID] = repairedBiCycle;
    fixID++;
    int curr = fixID - 1;
    while(curr){
        int parent = (curr - 1) / 2;
        if(fixHeap[curr] -> returnTime >= fixHeap[parent] -> returnTime) break;

        Bicycle* tmp = fixHeap[curr];
        fixHeap[curr] = fixHeap[parent];
        fixHeap[parent] = tmp;

        curr = parent;
    }
}
Bicycle* topFix(){
    if(fixID <= 0) return 0;
    return fixHeap[0];
}
Bicycle* popFix(){
    if(fixID <= 0) return 0;
    Bicycle* res = fixHeap[0];
    fixID--;
    fixHeap[0] = fixHeap[fixID];
    int curr = 0;
    while(2 * curr + 1 < fixID){
        int child;
        if(2* curr + 2 == fixID) child = 2 * curr + 1;
        else child = (fixHeap[ 2 * curr + 1] -> returnTime < fixHeap[2 * curr + 2] -> returnTime)? 2 * curr + 1 : 2 * curr + 2;

        if(fixHeap[curr] -> returnTime <= fixHeap[child] -> returnTime) break;

        Bicycle * tmp = fixHeap[curr];
        fixHeap[curr] = fixHeap[child];
        fixHeap[child] = tmp;

        curr = child;
    }
    return res;
}
void deliverBike(int now){
    // 고치는 자전거 있는지 확인
        // 있다면 리턴타임이 현재시간 이하인지 확인해서 이하이면 해당 대여소에 추가
    if(fixID <= 0) return;
    Bicycle* tmp;
    while(1){
        tmp = topFix();
        if(tmp == 0) {
            return;
        }
        if(tmp -> returnTime <= now){
            popFix();
            tmp -> lifeTime = 0;
            tmp -> rideStart = 0;
            tmp -> returnTime = -1;
            push(tmp -> returnIdx, tmp);
        }
        else break;
    }
    return;
}
/////////////

int DURABLE_TIME;
void init(int N, int durableTime, int deliveryTimes[]){
    DURABLE_TIME = durableTime;

    //자전거 대여소 N개 전부 초기화한다
    for(int i = 0; i < N; i++){
        STATION[i].bikeNum = 0;
        STATION[i].deliveryTime = deliveryTimes[i];
    }
        
    //자전거 개수 초기화한다
    bikeID = 0;
    //고객 해시테이블 초기화한다
        //이름 첫글자를 ? 로 선언하고
        //start, duration, end 0 으로 초기화한다.
    for(int i = 0; i < HASH_CUSTOM; i++){
        poolCustom[i].name[0] = '?';
        poolCustom[i].start = poolCustom[i].duration = poolCustom[i].end = 0;
    }
    //픽스 힙 넘버 초기화한다
    fixID = 0;
}
void addBicycle(int cTimestamp, int pID, int bicycleNum){
    deliverBike(cTimestamp);

    //자전거 개수만큼
        //신규 자전거 초기화 및 생성
        //해당 pID 대여소에 푸시
    for(int i = 0; i < bicycleNum; i++){
        Bicycle* newOne = alloc_b();
        newOne -> lifeTime = 0;
        newOne -> rideStart = 0;
        newOne -> returnTime = -1;
        newOne -> returnIdx = -1;
        push(pID, newOne);
    }
}
void buyTicket(int cTimestamp, char uName[], int validTime){


    // 고객을 호출해온다 (업다면 새로 생성할 수 잇게)
    Customer* nowCustom = getHash(uName);
    // 고객의 이용권이 없는 경우 또는 유효기간이 지난경우
        //현재시간, validTime, validTime + 현재시간 - 1 선언한다
    if(nowCustom -> end < cTimestamp || nowCustom -> duration == 0){
        nowCustom -> start = cTimestamp;
        nowCustom -> duration = validTime;
        nowCustom -> end = cTimestamp + validTime - 1;
    }
    // 유효기간이 지나지 않은 경우
        //duration + validTime, end + validTime 로 변경한다
    else{
        nowCustom -> duration += validTime;
        nowCustom -> duration += validTime;
    }
}
int rentBicycle(int cTimestamp, char uName[], int pID){
    deliverBike(cTimestamp);
    //대여소에 접근한다
    Station* nowStation = &STATION[pID];
    //만약 대기중 자전거가 없으면 return -1;

    if(nowStation -> bikeNum <= 0) return -1;
    //자전거 탑을 선언한다
    Bicycle* topBiCycle = top(pID);
    
    //고객에 접근한다
    Customer* nowCustomer = getHash(uName);
    if(cTimestamp == 39){
        if(nowCustomer -> riding == 0) printf("33");
        else printf("44");
        printf("%d", nowCustomer -> end);
    }
    //이미 자전거를 타고 있거나, 이용권확인시 불가능하면 return -1;
    if(nowCustomer -> riding != 0 || nowCustomer -> end < cTimestamp) return -1;

    //고객에 자전거에 포인터를 적용한다
    topBiCycle -> rideStart = cTimestamp;
    nowCustomer -> riding = topBiCycle;
    //대여소 자전거 팝
    pop(pID);
    //return 자전거 수명
    return topBiCycle -> lifeTime;
}
int returnBicycle(int cTimestamp, char uName[], int pID){
    deliverBike(cTimestamp);

    //고객에 접근한다
    Customer* nowCustomer = getHash(uName);
    //자전거 포인터 선언
    Bicycle* topBicycle;
    //ret = -1;
    int ret = -1;

    

    //자전거를 타고 있지 않은경우 return ret;
    if(nowCustomer -> riding == 0) return ret;

    
    else{
        topBicycle = nowCustomer -> riding;
        topBicycle -> lifeTime += cTimestamp - topBicycle -> rideStart;
        nowCustomer -> riding = 0;
        //자전거를 타고 있는대 유효기간이 지난 경우 
            //자전거 포인터를 0으로 바꾸고 위 선언한 자전거 포인터에 매단다
            //ret = 현재시간 - 고객 종료시간
        if(nowCustomer -> end < cTimestamp)
            ret = cTimestamp - nowCustomer -> end;
       
        //자전거를 타고 있는대 유효기간이 지나지 않은경우
        //자전거 포인터를 0으로 바꾸고 위 선언한 자전거 포인터에 매단다
        //ret = 0;
        else ret = 0;
    }
    //자전거 포인터가 0 ㅁ이아니면 
        // DURABLE_TIME과 비교한다 만약 초과햇으면 픽스 힙에 추가한다
    if(topBicycle -> lifeTime > DURABLE_TIME) {
        topBicycle -> lifeTime = 0;
        topBicycle -> rideStart = 0;
        topBicycle -> returnTime = STATION[pID].deliveryTime + cTimestamp;
        pushFix(topBicycle, pID);
    }
    else{
        push(pID, topBicycle);
    }
    return ret;
}
