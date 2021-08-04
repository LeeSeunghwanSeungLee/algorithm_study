#define MAX_RAIL 100001
#define HASH_RAIL 5003
#define swap(a, b) { int c = a; a = b; b = c;} // reference 로 변경되나봄

struct Rail{
    bool use;
    int r_idx, h_idx;
    Rail *prev, *next;
    int row, col;
    int front_dir;
    int prev_dir;
    int root;
}RAIL[MAX_RAIL];
int railCnt;
Rail* alloc_rail(){
    RAIL[railCnt].r_idx = railCnt;
    RAIL[railCnt].prev = RAIL[railCnt].next = 0;
    return &RAIL[railCnt++];
}

Rail CENTER;
Rail* FRONT;
Rail* REAR;

int TABLE[HASH_RAIL];
int ROW[4] = {-1, 0, 1, 0}; 
int COL[4] = {0, 1, 0, -1};
int NEXT_DIR[4][3] = { {3,0,1}, {0,1,2}, {1,2,3}, {2,3,0} };

int N;

void addHashing(Rail* newRail){
    unsigned long long h = (newRail -> row * 10001 + newRail -> col) % HASH_RAIL;
    while(TABLE[h] != -1){
        if(RAIL[TABLE[h]].row == newRail -> row && RAIL[TABLE[h]].col == newRail -> col) return;
        h = (h + 1) % HASH_RAIL;
    }
     newRail -> h_idx = h;
     TABLE[h] = newRail -> r_idx;
}

Rail* getHashing(int row, int col){
    unsigned long long h = (row * 10001 + col) % HASH_RAIL;
    int cnt = HASH_RAIL;
    while(TABLE[h] != -1 && cnt--){
        if(RAIL[TABLE[h]].row == row && RAIL[TABLE[h]].col ==  col) return &RAIL[TABLE[h]];
    }
    return 0;
}
void init(int N){
    ::N = N;
    railCnt = 0;
    CENTER.row = CENTER.col = N;
    CENTER.next = CENTER.prev = 0;
    CENTER.front_dir = 1;
    CENTER.prev_dir = 3;
    FRONT = REAR = &CENTER;
    for(register int i = 0; i < HASH_RAIL; i++){
        TABLE[i] = -1;
    }
}

void addRail(int mFront, int mDirection){
    if(mFront == 1){ // Front
        int row = FRONT -> row;
        int col = FRONT -> col;
        int dir = FRONT -> front_dir;
        Rail * newRail = alloc_rail();
        newRail -> row = row + ROW[dir];
        newRail -> col = col + COL[dir];
        newRail -> front_dir = NEXT_DIR[dir][mDirection];
        newRail -> prev_dir = (dir + 2) % 4;
        newRail -> root = 1;

        addHashing(newRail);

        FRONT -> next = newRail;
        newRail -> prev = FRONT;
        FRONT = newRail;
    }
    else{
       int row = REAR -> row;
        int col = REAR -> col;
        int dir = REAR -> front_dir;
        Rail * newRail = alloc_rail();
        newRail -> row = row + ROW[dir];
        newRail -> col = col + COL[dir];
        newRail -> front_dir = NEXT_DIR[dir][mDirection];
        newRail -> prev_dir = (dir + 2) % 4;
        newRail -> root = 0;

        addHashing(newRail);
        
        REAR -> prev = newRail;
        newRail -> next = REAR;
        REAR = newRail;
    }
}

bool isCircle(){
    bool flag = false;
    int n_row = FRONT -> row + ROW[FRONT -> front_dir];
    int n_col = FRONT -> col + COL[FRONT -> front_dir];
    int dir = REAR -> front_dir;
    if(REAR == &CENTER){
        dir = 3;
    }
    if(n_row == REAR -> row && n_col == REAR -> col && FRONT -> front_dir == ((dir + 2) % 4)){
        FRONT -> next = REAR;
        REAR -> prev = FRONT;
        flag = true;
    }
    return flag;
}

int delRail(int mRow, int mCol){
    bool isFront = true;
    bool find = false;

    Rail* curr = getHashing(mRow, mCol);
    if(curr == 0) return 0;

    if(isCircle()){ // 순환인 경우
        if(curr -> root == 1){
            while(FRONT != curr){
                swap(FRONT ->front_dir, FRONT -> prev_dir);
                FRONT -> root = 0;
                FRONT = FRONT -> prev;
            }
        }
        else{
            while(REAR != curr){
                swap(REAR -> front_dir, REAR -> prev_dir);
                REAR -> root = 1;
                REAR = REAR -> next;
            }
        }

        FRONT = curr -> prev;
        REAR = curr -> next;


    }
}

// 문제점 

// 1. 오픈 어드레싱을 활용하면 나중에 삭제되었을때 문제가 생길 수 있다. 따라서 그냥 chaining + boolean 연산자를 활용하는게 나을 수도 있음
