#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MALE   0
#define FEMALE 1

#define INIT         0
#define ADDMEMBER    1
#define GETDISTANCE  2
#define COUNTMEMBER  3

#define COUPLE  0
#define PARENT  1
#define CHILD   2

#define NAME_LEN_MAX 19

////////////////////////////////////////////////////////////////////////////////

void init(char initialMemberName[], int initialMemberSex);
bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]);
int  getDistance(char nameA[], char nameB[]);
int  countMember(char name[], int dist);

////////////////////////////////////////////////////////////////////////////////

static int score = 0;

static void cmd_init()
{
	char initialMemberName[NAME_LEN_MAX + 1];
	int initialMemberSex;

	scanf("%s %d", initialMemberName, &initialMemberSex);
	
	init(initialMemberName, initialMemberSex);
}

static void cmd_addMember()
{
	char newMemberName[NAME_LEN_MAX + 1];
	int newMemberSex;
	int relationship;
	char existingMemberName[NAME_LEN_MAX + 1];

	scanf("%s %d %d %s", newMemberName, &newMemberSex, &relationship, existingMemberName);
	
	bool userAns = addMember(newMemberName, newMemberSex, relationship, existingMemberName);

	int ans;
	scanf("%d", &ans);
	bool ansbool = ans == 1 ? true : false;
	
	if (ansbool != userAns)
	{
		score = 0;
	}
}

static void cmd_getDistance()
{
	char nameA[NAME_LEN_MAX + 1];
	char nameB[NAME_LEN_MAX + 1];

	scanf("%s %s", nameA, nameB);
	
	int userAns = getDistance(nameA, nameB);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
	}
}

static void cmd_countMember()
{
	char name[NAME_LEN_MAX + 1];
	int dist;

	scanf("%s %d", name, &dist);
	
	int userAns = countMember(name, dist);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
	}
}

int main()
{
	setbuf(stdout, NULL);

	//	freopen("sample_input.txt", "r", stdin);

	int T, scoreIdx;
	scanf("%d %d", &T, &scoreIdx);
	
	for (int TC = 1; TC <= T; TC++)
	{
		score = scoreIdx;
		
		int cmdL;
		scanf("%d", &cmdL);
		
		for (int cmdIdx = 0; cmdIdx < cmdL; ++cmdIdx)
		{
			int c_num;
			scanf("%d", &c_num);
			
			switch (c_num)
			{
			case INIT: 
				cmd_init(); 
				break;
				
			case ADDMEMBER: 
				cmd_addMember();  
				break;
				
			case GETDISTANCE: 
				cmd_getDistance();  
				break;
				
			case COUNTMEMBER: 
				cmd_countMember();  
				break;
				
			default: 
				break;
			}
		}
		
		printf("#%d %d\n", TC, score == scoreIdx ? scoreIdx : 0);
	}
	return 0;
}



#define HASH_NUM 313
#define NAME_LEN 20
#define BOUNDARY 100000
// int mstrcmp(const char str1[], const char str2[]){ // return 0 : same
//     int c=0;
//     while(str1[c] != '\0' && str1[c] == str2[c]) c++;
//     return str1[c] - str2[c];
// }
// void mstrcpy(char dest[], const char str[]){
//     while(*dest++ = *str++);
// }
int mstrcmp(const char a[], const char b[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
    return a[i] - b[i];
}
   
void mstrcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = src[i];
}
unsigned long djb2(const char str[]){
    unsigned long h = 5381;
    int c;
    while(c = (int)*str++){
        h = ((h << 5) + h + c - 'a') % HASH_NUM;
    }
    return h % HASH_NUM;
}
////////////////////////////////////////////
struct Member{
    char name[NAME_LEN];
    Member* parent;
    Member* partner;
    int sex;
}MEMBER[BOUNDARY];
int memberID;
Member* alloc_member(){
    return &MEMBER[memberID++];
}
////////////////////////////////////////////
int DIST[HASH_NUM][HASH_NUM];
////////////////////////////////////////////
Member* MEMBER_INFO[HASH_NUM];
int hashing(char name[]){
    unsigned long h = djb2(name);
    while(MEMBER_INFO[h] != 0) {
        if(mstrcmp(MEMBER_INFO[h] -> name, name) == 0) break;
        h = (h + 1) % HASH_NUM;
    }
    return h;
}
////////////////////////////////////////////

////////////////////////////////////////////
void init(char initialMemberName[], int initialMemberSex){
    memberID = 0;
    for(int i = 0; i < HASH_NUM; i++){
        MEMBER_INFO[i] = 0;
        for(int j = 0; j < HASH_NUM; j++) DIST[i][j] = -1;
    }

    Member* newMember = alloc_member();
    mstrcpy(newMember -> name, initialMemberName);
    newMember -> parent = 0;
    newMember -> partner = 0;
    newMember -> sex = initialMemberSex;
    // hashing 
    int n_h = hashing(initialMemberName);
    MEMBER_INFO[n_h] = newMember;
}
bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]){
    // 신규 멤버 추가
    Member* newMember = alloc_member();
    mstrcpy(newMember -> name, newMemberName);
    newMember -> parent = 0;
    newMember -> partner = 0;
    newMember -> sex = newMemberSex;
    // hashing 
    int n_h = hashing(newMemberName);
    MEMBER_INFO[n_h] = newMember;
    // get existing Member hashing
    int e_h = hashing(existingMemberName);
    Member* oldMember = MEMBER_INFO[e_h];
    int relation_cnt = 0;
    // set relation
    switch (relationship)
    {
    case 0: // 신입을 배우자로
        if(oldMember -> sex == newMember -> sex) {
            MEMBER_INFO[n_h] = 0;
            return false;
        }
        if(oldMember -> partner != 0) {
            MEMBER_INFO[n_h] = 0;
            return false;
        }
        oldMember -> partner = newMember;
        newMember -> partner = oldMember;
        DIST[n_h][e_h] = relation_cnt;
        DIST[e_h][n_h] = relation_cnt;
        break;
    case 1: // 신입을 부모로 
        if(oldMember -> parent == 0){ // 부모가 없을경우
            oldMember -> parent = newMember;
            relation_cnt = 1;
            DIST[n_h][e_h] = relation_cnt;
            DIST[e_h][n_h] = relation_cnt;
        }
        else{ // 부모가 있을경우
            if(oldMember -> parent -> sex == newMember -> sex) {
                MEMBER_INFO[n_h] = 0;
                return false;
            }
            if(oldMember -> parent -> partner != 0) {
                MEMBER_INFO[n_h] = 0;
                return false;
            }
            oldMember -> parent -> partner = newMember;
            newMember  -> partner = oldMember -> parent;
            DIST[n_h][e_h] = 1;
            DIST[e_h][n_h] = 1;
            e_h = hashing(oldMember -> parent -> name);
            DIST[n_h][e_h] = 0;
            DIST[e_h][n_h] = 0;
            relation_cnt = 0;
        }
        break;
    case 2: // 신입을 자식으로
        newMember -> parent = oldMember;
        relation_cnt = 1;
        DIST[n_h][e_h] = relation_cnt;
        DIST[e_h][n_h] = relation_cnt;
        break;
    default:
        break;
    }
    // calc dist
    for(int i = 0; i < HASH_NUM; i++){
        if(DIST[e_h][i] == -1) continue;
        if(i == n_h || i == e_h) continue;
        DIST[n_h][i] = DIST[e_h][i] + relation_cnt;
        DIST[i][n_h] = DIST[n_h][i];
    }
    return true;
}
int getDistance(char nameA[], char nameB[]){
    int a_h = hashing(nameA);
    int b_h = hashing(nameB);
    printf("%d\n", DIST[a_h][b_h]);
    return DIST[a_h][b_h];

}
int countMember(char name[], int dist){

    int res = 0;
    int hash = hashing(name);
    for(int i = 0; i < HASH_NUM; i++){
        if(DIST[hash][i] == dist) res++;
    }
    return res;
}