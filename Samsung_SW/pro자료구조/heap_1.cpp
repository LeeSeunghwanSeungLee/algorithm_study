#define MAX_SIZE 100002

typedef struct _NODE{
    char* name;
    int idx;
    _NODE* left;
    _NODE* right;
}NODE;

NODE* Head; 
NODE* Tail;
NODE ALOC_LIST[MAX_SIZE];
int size = 0;

NODE* myalloc(){
    return &ALOC_LIST[size++];
}

void init(){
    //Head 초기화
    //Tail 초기화
    //size 초기화
}

void push(int idx, char* name){
    // idx와 name이 주어지는 Data를 저장한다.

    // name은 3에서 10자리의 영어 소문자 문자열이다.

    // idx와 name은 중복이 있을 수 있다.

    // Parameters

    // idx : 추가되는 번호 (1 <= idx <= 1000000)

    // name : 추가되는 이름
}

int pop(){
    // 1. name이 사전 순으로 큰 Data

    // 2. name이 같은 경우 idx가 작은 Data를 삭제하고 idx를 반환한다. 

    // Returns

    // idx : 삭제한 Data의 idx
}

int top(){
    // 1. name이 사전 순으로 큰 Data

    // 2. name이 같은 경우 idx가 작은 Data의 idx를 반환한다. 

 

    // Returns

    // idx : 반환하는 Data의 idx
}



// 전략
// 1. 링크드리스트로 맥스힘을 구현한다
// 2. push와 pop 이 대부분이므로 nlogn 이내에서 끝낼 수 있음