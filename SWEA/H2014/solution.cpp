#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define ADD_ITEM                100
#define REMOVE_ITEM_BY_NAME     200
#define REMOVE_ITEM_BY_TAG      300
#define GET_ITEM                400
#define GET_AREA                500

void init(int R, int C);
int addItem(char name[], char tag[], int height, int width,
                   int mode, int r, int c);
int removeItemByName(char name[]);
int removeItemByTag(char tag[]);
int getItem(int r, int c, char name[], char tag[]);
int getArea(char tag[]);
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int run(int Result) {
    int N, R, C;

    scanf("%d %d %d", &N, &R, &C);

    init(R, C);

    for (int i = 0; i < N; ++i) {
        int cmd = 0;
        char name[11];
        char tag[11];
        char userName[11];
        char userTag[11];
        int height, width, mode, r, c;
        int ans, res;

        scanf("%d", &cmd);

        switch (cmd) {
        case ADD_ITEM:
            scanf("%s %s", name, tag);
            scanf("%d %d %d %d %d", &height, &width, &mode, &r, &c);

            res = addItem(name, tag, height, width, mode, r, c);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            break;

        case REMOVE_ITEM_BY_NAME:
            scanf("%s", name);

            res = removeItemByName(name);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            break;

        case REMOVE_ITEM_BY_TAG:
            scanf("%s", tag);

            res = removeItemByTag(tag);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            break;

        case GET_ITEM:
            scanf("%d %d", &r, &c);

            res = getItem(r, c, userName, userTag);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            if (ans == 1) {
                scanf("%s %s", name, tag);
                if (strcmp(name, userName) != 0) Result = 0;
                if (strcmp(tag, userTag) != 0) Result = 0;
            }
            break;

        case GET_AREA:
            scanf("%s", tag);

            res = getArea(tag);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            break;

        default:
            Result = 0;
            break;
        }
    }

    return Result;
}


int main() {
    setbuf(stdout, NULL);

	//freopen("sample_input.txt", "r", stdin);
	
    int T, Result;
    scanf("%d %d", &T, &Result);

    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run(Result));
    }

    return 0;
}

////
#define MAX_LEN 300
#define MAX_CHAR 10
#define MAX_TRI (MAX_LEN * MAX_CHAR + 10) //TODO : 범위를 늘려야 하는지 확인

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}


/////////////////////////////////////////////////////////////
struct node{
    int l_row, l_col, r_row, r_col;
    char name[MAX_CHAR];
    char tag[MAX_CHAR];
    node* next; // tag trie 
    node* prev;
}NODE[MAX_LEN * 2];
int nodeId(0);
node* alloc_n(const char name[], const char tag[], 
                const int l_r, const int l_c, const int r_r, const int r_c){
    mstrcpy(NODE[nodeId].name, name);
    mstrcpy(NODE[nodeId].tag, tag);
    NODE[nodeId].l_row = l_r;
    NODE[nodeId].l_col = l_c;
    NODE[nodeId].r_row = r_r;
    NODE[nodeId].r_col = r_c;
    NODE[nodeId].next = 0; // TODO : 지워도 되는지 확인하기
    NODE[nodeId].prev = 0;
    return &NODE[nodeId++];
}
/////////////////////////////////////////////////////////////
node* FIELD[MAX_LEN + 1][MAX_LEN + 1];
int WIDTH, HEIGHT;
bool check(int row, int col, int height, int width){
    for(int i = row; i < row + height; i++){
        for(int j = col; j < col + width; j++){
            if(FIELD[i][j] != 0) return false;
        }
    }
    return true;
}
/////////////////////////////////////////////////////////////
struct nameTrie{
    char c;
    nameTrie* next[26];
    node* end;
}NAME[MAX_TRI + 1];
int name_trieId(0);
nameTrie* rootName;
nameTrie* alloc_name(char c){
    NAME[name_trieId].c = c;
    NAME[name_trieId].end = 0;
    for(int i = 0; i < 26; i++) NAME[name_trieId].next[i] = 0;

    return &NAME[name_trieId++];
}

void pushName(char name[], node* newNode){
    nameTrie* curr = rootName;
    while(*name){
        int idx = *name - 'a';
        if(curr -> next[idx] == 0) {
            curr -> next[idx] = alloc_name(*name);
        }
        curr = curr -> next[idx];
        name++;
    }
    curr -> end = newNode;
}
node* removeName(char name[]){
    nameTrie* curr = rootName;
    while(*name){
        int idx = *name - 'a';
        if(curr -> next[idx] == 0) {
            return 0;
        }
        curr = curr -> next[idx];
        name++;
    }
    node* aTarget = curr -> end;
    if(aTarget == 0) return 0;
    curr -> end = 0;
    aTarget -> prev -> next = aTarget -> next;
    if(aTarget -> next != 0){
        aTarget -> next -> prev = aTarget -> prev;
    }
    return aTarget;
}


/////////////////////////////////////////////////////////////
struct tagTrie{
    char c;
    tagTrie* next[26];
    node* end;
}TAG[MAX_TRI + 1];
int tag_trieId(0);
tagTrie* rootTag;
tagTrie* alloc_tag(char c){
    TAG[tag_trieId].c = c;
    TAG[tag_trieId].end = 0;
    for(int i = 0; i < 26; i++) TAG[tag_trieId].next[i] = 0;

    return &TAG[tag_trieId++];
}

void pushTag(char tag[], node* newNode){
    tagTrie* curr = rootTag;
    while(*tag){
        int idx = *tag - 'a';
        if(curr -> next[idx] == 0) {
            curr -> next[idx] = alloc_tag(*tag);
        }
        curr = curr -> next[idx];
        tag++;
    }
    if(curr -> end == 0) {
        curr -> end = alloc_n("t", "t", 0, 0, 0, 0);
        curr -> end -> next = newNode;
        newNode -> prev = curr -> end;

    }
    else{
        newNode -> next = curr -> end -> next;
        newNode -> prev = curr -> end;
        curr -> end -> next -> prev = newNode;
        curr -> end -> next = newNode;
    }
}
node* getTag(char tag[]){
    tagTrie* curr = rootTag;
    while(*tag){
        int idx = *tag - 'a';
        if(curr -> next[idx] == 0) return 0;
        curr = curr -> next[idx];
        tag++;
    }
    if(curr -> end == 0|| curr -> end -> next == 0) return 0;
    return curr -> end -> next;
}
node* removeTag(char tag[]){
    tagTrie* curr = rootTag;
    while(*tag){
        int idx = *tag - 'a';
        if(curr -> next[idx] == 0) return 0;
        curr = curr -> next[idx];
        tag++;
    }
    if(curr -> end == 0 || curr -> end -> next == 0) return 0;
    node* aTarget = curr -> end -> next;
    curr -> end = 0;
    return aTarget;
}

/////////////////////////////////////////////////////////////

void init(int R, int C) {
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            FIELD[i][j] = 0;
        }
    }
    HEIGHT = R;
    WIDTH = C;
    nodeId = 0;

    name_trieId = 0;
    rootName = alloc_name('r');

    tag_trieId = 0;
    rootTag = alloc_tag('r');
}

int addItem(char name[], char tag[], int height, int width,
	int mode, int r, int c) {
    // 자동모드인경우
    if(mode == 1){
        bool flag = false;
        for(int col = 1; col <= WIDTH - width + 1; col++){
            for(int row = 1; row <= HEIGHT - height + 1; row++){
                if(check(row, col, height, width)) {
                    r = row;
                    c = col;
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        if(!flag) return 0;
    }

    //위에서 계산한 r, c로 노드생성
    node* newNode = alloc_n(name, tag, r, c, r + height - 1, c + width - 1);
    // 필드에 표시
    for(int i = r; i <= r + height - 1; i++){
        for(int j = c; j <= c + width - 1; j++){
            FIELD[i][j] = newNode;
        }
    }

    pushName(name, newNode);
    pushTag(tag, newNode);
	return 1;
}

int removeItemByName(char name[]) {
    node* aTarget = removeName(name);
    if(aTarget == 0) return 0;

    for(int i = aTarget -> l_row; i <= aTarget -> r_row; i++){
        for(int j = aTarget -> l_col; j <= aTarget -> r_col; j++){
            FIELD[i][j] = 0;
        }
    }
	return 1;
}

int removeItemByTag(char tag[]) {
    int num = 0;
    node* aTarget = removeTag(tag);
    if(aTarget == 0) return num;

    while(aTarget){
        for(int i = aTarget -> l_row; i <= aTarget -> r_row; i++){
            for(int j = aTarget -> l_col; j <= aTarget -> r_col; j++){
                FIELD[i][j] = 0;
            }
        }
        aTarget = aTarget -> next;
        num++;
    }
	return num;
}

int getItem(int r, int c, char name[], char tag[]) {
    node* aTarget = FIELD[r][c];
    if(aTarget == 0) return 0;
    mstrcpy(name, aTarget -> name);
    mstrcpy(tag, aTarget -> tag);
	return 1;
}

int getArea(char tag[]) {
    int res = 0;
    node* curr = getTag(tag);
    while(curr != 0){
        res += (curr -> r_row - curr -> l_row + 1) * (curr -> r_col - curr -> l_col + 1);
        curr = curr -> next;
    }
	return res;
}

