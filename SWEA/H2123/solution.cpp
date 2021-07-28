#define MAX_LAIL 5101
#define MAX_N 50007 // 45000 을 넘는 소수로 변경해야함
struct Node{
    int row, col, direction, root;
    Node *cNext, *cPrev;
    Node *next, *prev;
}poolNode[MAX_N];
int nodeCnt;
Node* alloc_n(){
    poolNode[nodeCnt].cNext = poolNode[nodeCnt].cPrev = poolNode[nodeCnt].next = poolNode[nodeCnt].prev = 0;
    return &poolNode[nodeCnt++];
}
////////////////////////////////
Node HASH_TABLE[MAX_LAIL];
Node* getHash(int row, int col){
    // 10001 진수로 계산 해서 MAX_LAIL 로 나눈다
    // curr 은 HASH_TABLE[h].next; 부터시장
    // while 로 돌면서 row, col 이 같으면 바로 리턴

    // 없으면 0 리턴
}
Node* addHash(int row, int col, Node* newNode){
    // 행과 열을 할당시킨다

    // h = 10001 진수로 계산 해서 MAX_LAIL 로 나눈다
    // 신규 노드의 이전은 테이블이고 다음은 테이블의 넥스트임
    // 테이블의 넥스트가 존재하면, 넥스트의 프리브는 새로운 노드임

    // 신규 노드 리턴
}
////////////////////////////////
bool isConnect;
int ROW[4] = {-1, 0, 1, 0};
int COL[4] = {0, 1, 0, -1};
int DIRECTION[4] = {3, 0, 1};
Node* FRONT;
Node* REAR;
int N;

////////////////////////////////
void init(int N){
    nodeCnt = 0;
    isConnect = false;
    FRONT = 0;
    REAR = 0;
    for(int i = 0; i < MAX_LAIL; i++) HASH_TABLE->next = 0;

}

void addRail(int mFront, int mDirection){
    //노드를 선언한다
  
    if(mFront == 0){ // 후방
        //만일 리어가 비어있으면
            // N, N - 1 에 addHash
            // 값 입력
            // 해시 테이블에 추가
            // 리어에 매달기
            // 리어의 넥스트와 프리프는 그대로 영이어야 함
            // root = 0;

        // 리어가 존재하면
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
    }
    else{ // 전방, 위에꺼를 반대로 하면됨

    }
}

int delRail(int mRow, int mCol){
    //연결되어있다면?
        //해당 노드를 가져온다
        // 루트가 0 이면
            //cPrev 를 Rear 로 선언하고 해당 노드를 지운다
            // isConnect 를 false 로 변경한다
            // FRONT -> cNext를  curr 로 선언
            // curr 가 해당 노드가 아닐때까지(while)
                // root 변경
                // prev, next 변경
            // FRONT 는 해당노드의 넥스트로 선언
        // 루트가 1이면 위에꺼를 반대로 적용


    // 연결되어 있지 않다면?
        // N, N - 1 이라면?
            //REAR = 0
            //CURR 선언
            //while(CURR)
                //테이블에서 지운다
                //넥스트로 넘어간다
        // N, N + 1 이라면?
            //FRONT = 0
            //CURR 선언
            //while(CURR)
                //테이블에서 지운다
                //넥스트로 넘어간다

        // 그 외라면?
            // getHash 로 값을 가져온다
            // 만일 0 이면
                // 한단계 전을 REAR
                // //CURR 선언
                //while(CURR)
                    //테이블에서 지운다
                    //넥스트로 넘어간다
            // 만일 1 이면
                // 한단계 전을 FRONT
                // //CURR 선언
                //while(CURR)
                    //테이블에서 지운다
                    //넥스트로 넘어간다
	return 0;
}
