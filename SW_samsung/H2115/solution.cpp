#define MAX_LEN 100010
#define MAX_WORD 25010
#define MAX_CHAR 500001

//////// 기본 제공 함수
void mstrcpy(char dst[], const char src[]) // str 복사
{
	int c = 0;
	while ((dst[c] = src[c]) != 0)
		++c;
}

int mstrlen(const char str[]) // str 길이 
{
	int ret = 0;
	while (str[ret])
		++ret;
	return ret;
}

int mstrcmp(const char str1[], const char str2[]) // str 비교
{
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c])
		++c;
	return str1[c] - str2[c];
}

///////// 구조체
struct character{
    char c;
    bool useYn;
    int end_cnt;
    int order; // 최근인지 아닌지 판별하기 위함
    character* next[26];
}poolCharacter[MAX_CHAR];
int cId;
character* alloc_c(char c){
    poolCharacter[cId].c = c;
    poolCharacter[cId].useYn = true;
    poolCharacter[cId].end_cnt = 0;
    for(register int i = 0; i < 26; i++) poolCharacter[cId].next[i] = 0;
    return &poolCharacter[cId++];
}
character root;
char aTemp[20];

void pushTrie(char name[]){
    character* curr = &root;
    while(*name != 0){
        int c = *name - 'a';
        if(curr -> next[c] == 0) curr -> next[c] = alloc_c(*name);
        curr = curr -> next[c];
        name++;
    }
    if(curr -> useYn == false) {
        curr -> end_cnt = 0;
        return;
    }
    curr -> end_cnt++;
    curr -> order = cId;
    return;
}

void banTrie(char name[]){
    character* curr = &root;
    while(*name != 0){
        int c = *name - 'a';
        if(curr -> next[c] == 0) curr -> next[c] = alloc_c(*name);
        curr = curr -> next[c];
        name++;
    }
    curr -> useYn = false;
    return;
}

character* findTrie(char name[]){
    character* curr = &root;
    while(*name != 0){
        int c = *name - 'a';
        if(curr -> next[c] == 0) return 0;
        curr = curr -> next[c];
        name++;
    }
    return curr;
}


struct word{
    char word[20];
    int num; // 몇번 추가 되었는지 확인하기 위함임
    int order; // 최근인지 아닌지 확인하기 위함임
}WORD[MAX_WORD];
int wId(0);
word* alloc_w(char word[], int num, int order){
    mstrcpy(WORD[wId].word, word);
    WORD[wId].num = num;
    WORD[wId].order = order;
    return &WORD[wId++];
}
word* heap[MAX_WORD];
int hId = 0;

bool cmpWord(word* a, word* b){ // a가 더 크면 ture
    if(a -> num > b -> num) return true;
    else if(a -> num == b -> num && a -> order > b -> order) return true;
    return false;
}
void pushHeap(word* newWord){
    heap[hId] = newWord;
    int curr = hId;
    while(curr != 0){
        if(cmpWord(heap[(curr - 1) / 2], heap[curr])) break;

        word* temp = heap[curr];
        heap[curr] = heap[(curr - 1) / 2];
        heap[(curr - 1) / 2] = temp;
        curr = (curr - 1) / 2;
    }
    hId++;
    return;
}
word* topHeap(){
    return heap[0];
}

void dfs(character* curr, int depth){
    if(curr -> useYn == true && curr -> end_cnt > 0){ // 마지막이면
        aTemp[depth] = '\0';
        word* newWord = alloc_w(aTemp, curr -> end_cnt, curr ->order);
        pushHeap(newWord);
    }
    for(register int i = 0; i < 26; i++){
        if(curr -> next[i] == 0) continue;
        aTemp[depth] = curr -> next[i] -> c;
        dfs(curr -> next[i], depth + 1);
        aTemp[depth] = '\0';
    }
    return;
}


// /////////// 메인 함수
void init(){
    cId = 0;
    for(register int i = 0; i < 26; i++) root.next[i] = 0;
    wId = 0;
    hId = 0;
}

void inputWord(char mWord[20]){
    pushTrie(mWord);
    return;
}

int recommend(char mUser[20], char mAnswer[20]){ // 정답이 0 일때도 꼭 확인하기(boundary)
    character* nowChar = findTrie(mUser);
    if(nowChar == 0){
        mstrcpy(mAnswer, mUser);
        return mstrlen(mUser);
    }
    int depth = mstrlen(mUser);

    mstrcpy(aTemp, mUser);

    dfs(nowChar, depth);

    if(wId == 0) {
         mstrcpy(mAnswer, mUser);
         return mstrlen(mUser);
     }

    word* res = topHeap();
    mstrcpy(mAnswer, res -> word);

    hId = 0;
	return mstrlen(res -> word);
}

void banWord(char mWord[20]){
    banTrie(mWord);
    return;
}