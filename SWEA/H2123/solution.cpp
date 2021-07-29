#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static const int CMD_INIT = 100;
static const int CMD_ADDRAIL = 200;
static const int CMD_DELRAIL = 300;

void init(int);
void addRail(int, int);
int delRail(int, int);

static int run(void)
{
	int ret = 0;
	int query_cnt, cmd;
	int usr, ans;
	int N, mRow, mCol, mFront, mDirection;

	scanf("%d", &query_cnt);

	for (int q = 0; q < query_cnt; q++)
	{
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d", &N);
			init(N);
			ret = 1;
			break;
		case CMD_ADDRAIL:
			scanf("%d %d", &mFront, &mDirection);
			addRail(mFront, mDirection);
			break;
		case CMD_DELRAIL:
			scanf("%d %d", &mRow, &mCol);
			usr = delRail(mRow, mCol);
			scanf("%d", &ans);
            // printf("%d %d", usr, ans);
			if (usr != ans)
				ret = 0;
			break;
		default:
			ret = 0;
			break;
		}
	}

	return ret;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);
	int tc, MARK;

	scanf("%d %d", &tc, &MARK);

	for (int t = 1; t <= tc; t++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", t, score);
	}

	return 0;
}
/////////////////////====================
#define MAX_RAIL 5101
#define MAX_N 50007 // 45000 을 넘는 소수로 변경해야함
struct Node{
    int row, col, direction, root, mDirection;
    Node *cNext, *cPrev;
    Node *next, *prev;
}poolNode[MAX_N];
int nodeCnt;
Node* alloc_n(){
    poolNode[nodeCnt].cNext = poolNode[nodeCnt].cPrev = poolNode[nodeCnt].next = poolNode[nodeCnt].prev = 0;
    return &poolNode[nodeCnt++];
}
////////////////////////////////
Node HASH_TABLE[MAX_RAIL];
Node* getHash(int row, int col){
    // 10001 진수로 계산 해서 MAX_LAIL 로 나눈다
    int h = (row * 10001 + col) % MAX_RAIL;
    
    Node* curr = HASH_TABLE[h].next;
    // while 로 돌면서 row, col 이 같으면 바로 리턴
    while(curr){
        if(curr -> row == row && curr -> col == col) return curr;
        curr = curr -> next;
    }
    return 0;
}
Node* addHash(int row, int col, int direction, int root, int mDirection){    
    Node* newNode = alloc_n();
    newNode -> row = row;
    newNode -> col = col;
    newNode -> direction = direction;
    newNode -> root = root;
    newNode -> mDirection = mDirection;
    int h = (row * 10001 + col) % MAX_RAIL;
    Node* curr = &HASH_TABLE[h];

    newNode -> next = curr -> next;
    newNode -> prev = curr;
    if(curr -> next) curr -> next -> prev = newNode;
    curr -> next =newNode;
    return newNode;
}
////////////////////////////////
bool isConnect;
int ROW[4] = {-1, 0, 1, 0};
int COL[4] = {0, 1, 0, -1};
int DIRECTION[3] = {3, 0, 1};
Node* FRONT;
Node* REAR;
int N;

////////////////////////////////
void init(int N){
    nodeCnt = 0;
    isConnect = false;
    FRONT = 0;
    REAR = 0;
    ::N = N;
    for(int i = 0; i < MAX_RAIL; i++) HASH_TABLE->next = 0;

}

void addRail(int mFront, int mDirection){
    //노드를 선언한다
    Node* newNode;
    if(mFront == 0){ // 후방
        //만일 리어가 비어있으면
            // N, N - 1 에 addHash
            // 값 입력
            // 해시 테이블에 추가
            // 리어에 매달기
            // 리어의 넥스트와 프리프는 그대로 영이어야 함
            // root = 0;
        if(REAR == 0){
            newNode = addHash(N, N - 1, (3 + DIRECTION[mDirection]) % 4, mFront, 1);
            REAR = newNode;
        }
        else{// 리어가 존재하면
            //리어에 접근
            //리어의 좌표와 방향을 바탕으로 다음 좌표 계산 => addHash 해서 위에서 선언한 노드에 추가
            // 다음 방향 계산
            // 노드 값 갱신
            // 리어의 넥스트에 노드 
            // 노드의 프리브에 리어 추가
            // root = 1;
            // 리어는 노드로 갱신
            // addHash
            // 다음좌표를 계산햇는데 만약 그게 FRONT이고 방향이 서로 일치하면?
                // 서로 연결하고 isConnect 를 true
            Node* curr = REAR;
            int n_row, n_col, n_dir;
            n_row = curr -> row + ROW[curr -> direction];
            n_col = curr -> col + COL[curr -> direction];
            n_dir = (curr -> direction + DIRECTION[mDirection]) % 4;
            newNode = addHash(n_row, n_col, n_dir, mFront, REAR -> direction);
            // printf("%d %d %d\n",n_row, n_col, n_dir);
            newNode -> cPrev = curr;
            curr -> cNext = newNode;
            REAR = newNode;
            if(FRONT == 0) return;

            n_row = REAR -> row + ROW[REAR -> direction];
            n_col = REAR -> col + COL[REAR -> direction];

            if(FRONT -> row == n_row && FRONT -> col == n_col && ((REAR -> direction - FRONT -> direction) == 2 || (REAR -> direction - FRONT -> direction) == -2)){
                isConnect = true;
            }
        }
        
    }
    else{ // 전방, 위에꺼를 반대로 하면됨
        if(FRONT == 0){
            newNode = addHash(N, N + 1, (1 + DIRECTION[mDirection]) % 4, mFront, 1);
            FRONT = newNode;
        }
        else{
            Node* curr = FRONT;
            int n_row, n_col, n_dir;
            n_row = curr -> row + ROW[curr -> direction];
            n_col = curr -> col + COL[curr -> direction];
            n_dir = (curr -> direction + DIRECTION[mDirection]) % 4;
            newNode = addHash(n_row, n_col, n_dir, mFront, FRONT -> direction);
            newNode -> cPrev = curr;
            curr -> cNext = newNode;
            FRONT = newNode;
            if(REAR == 0) return;
            // printf("%d %d %d\n", n_row, n_col, FRONT -> direction);
            n_row = FRONT -> row + ROW[FRONT -> direction];
            n_col = FRONT -> col + COL[FRONT -> direction];
            // printf("%d %d\n", n_row, n_col);
            if(REAR -> row == n_row && REAR -> col == n_col && ((REAR -> direction - FRONT -> direction == 2) || (REAR -> direction - FRONT -> direction == -2))) {
                isConnect = true;
            }
        }
    }
}

int delRail(int mRow, int mCol){
    Node* target = getHash(mRow, mCol);
    int res = 0;
    if(target == 0) return res;

    if(isConnect){
        if(target -> root == 0){
            if(target == REAR){
                if(target -> cPrev == 0){
                    REAR = 0;
                    target -> prev -> next = target -> next;
                    if(target -> next) target -> next -> prev = target -> prev;

                    
                }
                else{
                    REAR = target -> cPrev;
                    REAR -> cNext = 0;

                    target -> prev -> next = target -> next;
                    if(target -> next) target -> next -> prev = target -> prev;

                    
                }
            }
            else if(target -> cPrev == 0){
                target -> prev -> next = target -> next;
                if(target -> next) target -> next -> prev = target -> prev;

                
                Node* curr = target -> cNext;
                curr -> cPrev = 0;
                while(curr){
                    Node* tmp = curr -> cPrev;
                    curr -> cPrev = curr -> cNext;
                    curr -> cNext = tmp;

                    int aTmp = curr -> direction;
                    curr -> direction = curr -> mDirection;
                    curr -> mDirection = aTmp;

                    curr -> root = FRONT -> root;
                    curr = curr -> cPrev;
                }
                FRONT -> cNext = REAR;
                REAR -> cPrev = FRONT;
                
                FRONT = target -> cNext;
                REAR = 0;
            }
            else{
                target -> prev -> next = target -> next;
                if(target -> next) target -> next -> prev = target -> prev;

                
                Node* curr = target -> cNext;
                while(curr){
                    Node* tmp = curr -> cPrev;
                    curr -> cPrev = curr -> cNext;
                    curr -> cNext = tmp;

                    int aTmp = curr -> direction;
                    curr -> direction = curr -> mDirection;
                    curr -> mDirection = aTmp;

                    curr -> root = FRONT -> root;

                    curr = curr -> cPrev;
                }
                FRONT -> cNext = REAR;
                REAR -> cPrev = FRONT;
                
                FRONT = target -> cNext;
                REAR = target -> cPrev;

                REAR -> cNext = 0;
            }
        }
        else{
            if(target == FRONT){
                if(target -> cPrev == 0){
                    FRONT = 0;
                    target -> prev -> next = target -> next;
                    if(target -> next) target -> next -> prev = target -> prev;

                    
                }
                else{
                    FRONT = target -> cPrev;
                    FRONT -> cNext = 0;

                    target -> prev -> next = target -> next;
                    if(target -> next) target -> next -> prev = target -> prev;

                    
                }
            }
            else if(target -> cPrev == 0){
                target -> prev -> next = target -> next;
                if(target -> next) target -> next -> prev = target -> prev;

            
                Node* curr = target -> cNext;
                while(curr){
                    Node* tmp = curr -> cPrev;
                    curr -> cPrev = curr -> cNext;
                    curr -> cNext = tmp;

                    int aTmp = curr -> direction;
                    curr -> direction = curr -> mDirection;
                    curr -> mDirection = aTmp;

                    curr -> root = REAR -> root;

                    curr = curr -> cPrev;
                }
                REAR -> cNext = FRONT;
                FRONT -> cPrev = REAR;
                
                REAR = target -> cNext;
                FRONT = 0;
            }
            else{
                target -> prev -> next = target -> next;
                if(target -> next) target -> next -> prev = target -> prev;

                
                Node* curr = target -> cNext;
                while(curr){
                    Node* tmp = curr -> cPrev;
                    curr -> cPrev = curr -> cNext;
                    curr -> cNext = tmp;

                    int aTmp = curr -> direction;
                    curr -> direction = curr -> mDirection;
                    curr -> mDirection = aTmp;

                    curr -> root = REAR -> root;

                    curr = curr -> cPrev;
                }
                REAR -> cNext = FRONT;
                FRONT -> cPrev = REAR;
                
                REAR = target -> cNext;
                FRONT = target -> cPrev;

                FRONT -> cNext = 0;
            }
        }
        res = 1;
        isConnect = false;
    }



    else{
        if(target -> root == 1){
            FRONT = target -> cPrev;
            Node* curr = target;
            while(curr){
                res++;
                curr -> prev -> next = curr -> next;
                if(curr -> next) curr -> next -> prev = curr -> prev;
                curr = curr -> cNext;  
            }
        }
        else{
            REAR = target -> cPrev;
            Node* curr = target;
            while(curr){
                res++;
                curr -> prev -> next = curr -> next;
                if(curr -> next) curr -> next -> prev = curr -> prev;

                curr = curr -> cNext;
            }
        }
    }
	return res;
}