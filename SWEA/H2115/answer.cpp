#define MAXNUM 25000
 
char lookUp[MAXNUM][20] = { 0 };
int lookUpCnt[MAXNUM] = { 0 };
int lookUpTime[MAXNUM] = { 0 };
int Time;
 
void mstrcpy(char dst[], const char src[])
{
    int c = 0;
    while ((dst[c] = src[c]) != 0)
        ++c;
}
 
int mstrlen(const char str[])
{
    int ret = 0;
    while (str[ret])
        ++ret;
    return ret;
}
 
int mstrcmp(const char str1[], const char str2[])
{
    int c = 0;
    while (str1[c] != 0 && str1[c] == str2[c])
        ++c;
    return str1[c] - str2[c];
}
 
 
int getMax(int a, int b) {
    if (lookUpCnt[a] != lookUpCnt[b])
        return lookUpCnt[a] > lookUpCnt[b] ? a : b;
    else
        return lookUpTime[a] > lookUpTime[b] ? a : b;
}
 
struct _trie {
    //int num;//입력된 순서
    int hashNum;
    int max;
    int next[26];
 
    static int cnt;
    static int idx;
    static _trie Trie[MAXNUM * 10];
 
    int insert(const char* s) {
        //문자열의 제일 마지막에 도착했으면
        if (*s == 0) {
            //ban된 문자열이면 return -1;
            if (hashNum == -1)
                return -1;
 
            //1.새로운단어
            if (hashNum == 0)
                hashNum = ++cnt;
 
            //lookup table 채워주고
            lookUpCnt[hashNum]++;
            lookUpTime[hashNum] = Time;
 
            //hashNum과 max가 다르면 비교해서 연산 max==0 / max!=0 이어도 성립
            if (lookUpCnt[max] <= lookUpCnt[hashNum])
                max = hashNum;
            //}
            return hashNum;
        }
 
        //문자열의 중간이면
        //한번도 입력된적이 없으면
        if (next[*s - 'a'] == 0) {
            //idx값을 넣어주고 
            next[*s - 'a'] = ++idx;
 
            //초기화
            for (int i = 0; i < 26; i++) {
                Trie[idx].next[i] = 0;
            }
            Trie[idx].max = 0;
            Trie[idx].hashNum = 0;
        }
        //다음 문자열로 진입
        int insertHashNum = Trie[next[*s - 'a']].insert(s + 1);
 
        //max값 초기화하기 
 
        if (insertHashNum == -1)return -1;
 
        if (lookUpCnt[max] <= lookUpCnt[insertHashNum]) {
            max = insertHashNum;
        }
        return insertHashNum;
    }
 
    int get(const char* s) {
        //입력값의 끝
        if (*s == 0) {
            //해당지점에 max가 있으면 max return
            if (max)return max;
            return 0;
        }
        return Trie[next[*s - 'a']].get(s + 1);
    }
 
    int ban(const char* s) {
        //입력값의 끝
        int banNum = 0;
 
        if (*s == 0) {
            banNum = hashNum;
            lookUpCnt[hashNum] = 0;
            hashNum = -1;
            max = 0;
 
            for (int i = 0; i < 26; i++) {
 
                if (next[i] != 0) {
                    max = getMax(max, Trie[next[i]].max);
                }
 
            }
            return banNum;
        }
 
        banNum = Trie[next[*s - 'a']].ban(s + 1);
 
        if (max == banNum) {
            //num = 0;
            max = 0;
            for (int i = 0; i < 26; i++) {
 
                if (next[i] != 0) {
                    max = getMax(max, Trie[next[i]].max);
                }
            }
        }
        return banNum;
    }
 
};
 
_trie trie;
_trie _trie::Trie[MAXNUM * 10];
int _trie::idx = 0;
int _trie::cnt = 0;
 
void init(){
    for (register int j = 0; j < 26; j++)
        trie.next[j] = 0;
 
    for (register int i = 0; i <= _trie::cnt; i++)
        lookUpTime[i] = lookUpCnt[i] = 0;
 
    Time = 0;
    trie.idx = 0;
    trie.cnt = 0;
     
}
 
void inputWord(char mWord[20]){
    Time++;
    int temp = trie.insert(mWord);
    if (temp > 0) {
        mstrcpy(lookUp[temp], mWord);
    }
 
    return;
}
 
int recommend(char mUser[20], char mAnswer[20]){
    int answer = trie.get(mUser);
    if (answer == 0) {
        mstrcpy(mAnswer, mUser);
    }
    else {
        mstrcpy(mAnswer, lookUp[answer]);
    }
 
    return mstrlen(mAnswer);
}
 
void banWord(char mWord[20]){
    int temp = trie.insert(mWord);
    if (temp > 0) {
        mstrcpy(lookUp[temp], mWord);
    }
    int banNum = trie.ban(mWord);
 
    return;
}