#define NULL 0
#define MAX_USER 2001
#define MAX_LEN 11
#define MAX_WORD 4013

struct Word{
    char str[MAX_LEN];
    unsigned int correction[6];
    int correct_size;
    int currect_uid[6][4];
};
int N;
int last_timestamp[MAX_USER];
char last_word[MAX_USER][MAX_LEN];
Word wordtable[MAX_WORD];
 
int mstrcmp(const char* a, const char* b)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return a[i] - b[i];
}
 
int mstrlen(const char* a)
{
    int len = 0;
 
    while (a[len] != '\0')
        len++;
 
    return len;
}
 
void mstrcpy(char* dest, const char* src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

void init(int n){
    N = n;
    for(register int i = 0; i < N; i++){
        last_timestamp[i] = 0;
        last_word[i][0] = '\0';
    }

    for(register int i = 0; i < MAX_WORD; i++){
        wordtable[i].str[0] = '\0';
        for(register int j = 0; j < 5; j++){
            wordtable[i].correction[j] = -1;
            wordtable[i].currect_uid[j][0] = -1;
            wordtable[i].currect_uid[j][1] = -1;
            wordtable[i].currect_uid[j][2] = -1;
        }
        wordtable[i].correct_size = 1;
    }
}

unsigned long hash(const char* str){
    unsigned long h = 5381;
    int c;
    while(c = *str++){
        h = ((h << 5) + h + c) % MAX_WORD;
    }
    return h % MAX_WORD;
}
int getHashIndex(char * key){
    unsigned long h = hash(key);
    while(wordtable[h].str[0] != 0){
        if(mstrcmp(wordtable[h].str, key) == 0) return h;
        h = (h + 1) % MAX_WORD;
    }
    mstrcpy(wordtable[h].str, key);
    return h;
}

bool check(const char w[MAX_LEN], const char c[MAX_LEN]){
    int addedCnt = 0, deletedCnt = 0, changedCnt = 0;
    int wlen = mstrlen(w);
    int clen = mstrlen(c);

    register int i, j;
    if(wlen == clen + 1){
        addedCnt= 1;
        for(i = 0; i < wlen; i++){
            if(w[i] != c[i]) break;
        }
        for(j = i; j < clen; j++){
            if(w[j + 1] != c[j]){
                addedCnt = 0;
                break;
            }
        }
    }
    else if(wlen == clen - 1){
        deletedCnt = 1;
        for(i = 0; i < wlen; i++){
            if(w[i] != c[i]) break;
        }
        for(j = i; j < clen; j++){
            if(w[j] != c[j + 1]){
                deletedCnt = 0;
                break;
            }
        }
    }

    else{
        int ci = 0, count = 0;
        while (1) {
            if (w[ci] == '\0' || c[ci] == '\0') {
                if (w[ci] == '\0' && c[ci] == '\0' && count == 1) {
                    changedCnt = 1;
                }
                break;
            }
            if (w[ci] != c[ci]) {
                count++;
            }
            ci++;
        }
    }
    return addedCnt + deletedCnt + changedCnt == 1 ? true : false;
}
void addUser(int mId, int wrongIdx, int correctStrIdx){
    for(register int i = 0; i < 3; i++){
        if(wordtable[wrongIdx].currect_uid[correctStrIdx][i] == mId){
            break;
        }
        if(wordtable[wrongIdx].currect_uid[correctStrIdx][i] == -1){
            wordtable[wrongIdx].currect_uid[correctStrIdx][i] = mId;
            break;
        }
    }
}
void addCorrectWord(int mId, int wrongIdx, char correctWord[11]){
    int correctIdx = getHashIndex(correctWord);
    for (register int i = 0; i < wordtable[wrongIdx].correct_size; i++) {
        if (wordtable[wrongIdx].correction[i] == correctIdx) {
            addUser(mId, wrongIdx, i);
            return;
        }
        if (wordtable[wrongIdx].correction[i] == -1) {
            wordtable[wrongIdx].correction[i] = correctIdx;
            wordtable[wrongIdx].correct_size++;
            addUser(mId, wrongIdx, i);
            return;
        }
    }
}
int getCorrectWord(int idx, char correctWord[5][11]){
    int answer = 0;
    for (register int i = 0; i < wordtable[idx].correct_size; i++) {
        if (wordtable[idx].currect_uid[i][2] != -1) {
            mstrcpy(correctWord[answer], wordtable[wordtable[idx].correction[i]].str);
            answer++;
        }
    }
    return answer;
}
int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]) {
    if (searchTimestamp - last_timestamp[mId] <= 10) {
        if (check(last_word[mId], searchWord)) {
            int wrongidx = getHashIndex(last_word[mId]);
            addCorrectWord(mId, wrongidx, searchWord);
        }
    }
 
    last_timestamp[mId] = searchTimestamp;
    mstrcpy(last_word[mId], searchWord);
 
    int index = getHashIndex(searchWord);
    return getCorrectWord(index, correctWord);
}