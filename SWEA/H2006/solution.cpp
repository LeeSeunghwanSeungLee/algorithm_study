#define MAX_USER 23
#define MAX_GROUP 11
#define CHAR_LEN 9
#define MAX 10007

/* -------Common API ------*/
int mstrcmp(const char *a, const char *b){
int i;
for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
return a[i] - b[i];
}

void mstrcpy(char *dest, const char *src){
    while(*dest++ = *src);
}
/* -------그룹 ---------- */
struct Group{
    char name[CHAR_LEN];
}group[MAX_GROUP];
Group* getGroup(char name[]){
    unsigned long h = 5381;
    int c;
    while(c = *name++){
        h = ((h << 5) + h + c) % MAX_GROUP;
    }
    h %= MAX_GROUP;
    while(group[h].name[0] != '?'){
        if(mstrcmp(group[h].name, name)) return &group[h];
        h = (h + 1) % MAX_GROUP;
    }
    mstrcmp(group[h].name, name);
    return &group[h];
}
/* -------유저---------- */
struct User{
    char name[CHAR_LEN];
    Group* group;

}user[MAX_USER];
User* getUser(char name[]){
    unsigned long h = 5381;
    int c;
    while(c = *name++){
        h = ((h << 5) + h + c) % MAX_USER;
    }
    h %= MAX_USER;
    while(user[h].name[0] != '?'){
        if(mstrcmp(user[h].name, name)) return &user[h];
        h = (h + 1) % MAX_USER;
    }
    mstrcmp(user[h].name, name);
    return &user[h];
}
/* ------- 디렉토리 및 파일 ---------- */
struct Dir_Fil{
    char name[CHAR_LEN];
    char extend[CHAR_LEN]; // '?' : directory, other : file
    int auth; // 0 : only creator, 1 : same group, 2 : other
    Dir_Fil *parent, *child, *sib_p, *sib_n;
    int child_cnt;
    Dir_Fil *prev, *next;
    Group* group; // owner group
    User* user; // owner user
}poolDirFil[MAX];
int pool_cnt;

Dir_Fil* alloc_d_f(char name[], char extend[], int auth, Group* g, User* u){
    mstrcpy(poolDirFil[pool_cnt].name, name);
    mstrcpy(poolDirFil[pool_cnt].extend, extend);
    poolDirFil[pool_cnt].auth = auth;
    poolDirFil[pool_cnt].parent = poolDirFil[pool_cnt].child = poolDirFil[pool_cnt].sib_n = poolDirFil[pool_cnt].sib_p = 0;
    poolDirFil[pool_cnt].child_cnt = 0;
    poolDirFil[pool_cnt].prev = poolDirFil[pool_cnt].next = 0;
    poolDirFil[pool_cnt].group = g;
    poolDirFil[pool_cnt].user = u; 
    return &poolDirFil[pool_cnt++];
}

Dir_Fil* TABLE[MAX];
Dir_Fil* ROOT;

unsigned long hashing(char name[]){
    unsigned long h = 5381;
    int c;
    while(c = *name++){
        h = ((h << 5) + h + c) % MAX;
    }
    return h % MAX;
}
void addTable(Dir_Fil* target){
    unsigned long h = hashing(target -> name);
    Dir_Fil* curr = TABLE[h];
    if(curr){ // if alreadh existed
        curr -> next -> prev = target;
        target -> next = curr;
    }
    TABLE[h] = target;
}

Dir_Fil* getTable(char name[], char ext[]){
    unsigned long h = hashing(name);
    Dir_Fil* curr = TABLE[h];
    while(curr){
        if(mstrcmp(curr -> name, name) == 0 && mstrcmp(curr -> extend, ext) == 0) return curr;
        curr = curr -> next;
    }
    return 0;
}
void removeTalbe(Dir_Fil* target){
    if(target -> prev == 0 && target -> next == 0){
        unsigned long h = hashing(target -> name);
        TABLE[h] = 0;
    }
    else if(target -> prev){
        unsigned long h = hashing(target -> name);
        Dir_Fil* curr = TABLE[h];
        TABLE[h] = curr -> next;
    }
    else if(target -> next){
        target -> prev -> next = 0;
    }
    else{
        target -> next -> prev = target -> prev;
        target -> prev -> next = target -> next;
    }
}
/* ------main API ------------- */

void init(){
  // 초기화 작업 진행
  pool_cnt = 0;
  for(int i = 0; i < MAX_GROUP; i++)
      group[i].name[0] = '?';
  for(int i = 0; i < MAX_USER; i++)
      user[i].name[0] = '?';
  // admin 그룹 생성

  // admin 유저 생성

  // 루트 디렉토리 생성 , 유저권한은 2
}

void createUser(char userName[], char groupName[]){
    // 유저 Read or Creat

    // if null group creat and connect with user

    return;
}

Dir_Fil* moveDirectory(char path[], User* user){
    // if no permissionn, then return 0;
}
int createDirectory(char userName[], char path[], char directoryName[], int permission){
    // get User (at the sampe time, get Group)
    
    // move Directory using path[] & User* 
        // if return 0, return 0
    // make Directory 
    // set Hash Table

    // connect parent dir & newDir(parent, child, sib_p, sib_n)
    return 1;  
}


int createFile(char userName[], char path[], char fileName[], char fileExt[]){
    // similar with creatDirectory method
    return 1;
}

int BFS(Dir_Fil* target_d, User* user){
    
}
int find(char userName[], char pattern[]){
    // BFS 로 완전탐색이 필요한 작업

    // 초기 start directory 를 찾는다
    // 만일 권한이 없으면 return 0;
    
    // BFS를 실행한다

    // 리턴
    return 0;
}

// https://out.swexpertacademy.samsung.com/common/swea/solvingPractice/solveclub/solveclubProblemDetail.do?solveclubId=AXpWJc3ACZBqnWDU&solveclubPassword=&password=&attendYn=Y&contestProbId=AXA8s6JgVPlqnCxC&sortingType=