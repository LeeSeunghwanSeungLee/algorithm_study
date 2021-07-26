#define MAXN 100
#define MAXL 8
#define MAX_PQ 20000
#define MAX_USER 10000
#define MAX_BICYCLE 20000
#define MAX_TABLE 16383


/////// 에라토스테네스의 체
#include <iostream>
#include <cmath>
using namespace std;

int boundary = 11000;
int arr[11001];

int main(void){

    for(int i = 0; i < boundary; i++) arr[i] = i;

    for(int i = 2; i <= sqrt(boundary); i++){

        if(arr[i] == -1) continue;

        for(int j = i * i; j < boundary; j += i){
            arr[j] = -1;
        }
    }
    for(int i = 2; i < boundary; i++){
        if(arr[i] == -1)  continue;
        cout << arr[i] << '\n';
    }
    return 0;
}



void mstrcpy(char dst[], const char src[]){
    while(*dst++ = *src++);
}
int mstrcmp(const char str1[], const char str2[]){
    int c = 0;
    while(str1[c] != 0 && str1[c] == str2[c]) c++;
    return str1[c] - str2[c];
}

unsigned long getHash(const char str[]){ // djb2
    unsigned long h = 5381;
    int c;
    while(c = *str++){
        h = ((h << 5) + h + c) % MAX_TABLE;
    }
    return h % MAX_TABLE;
}

int user_cnt;
struct BICYCLE{
    int start_time;
    int ride_time;
};
int alloc_idx;
BICYCLE alloc_node[3 * (MAX_BICYCLE) + 5];
BICYCLE* myalloc_node(int start_time){
    BICYCLE* pnode = &alloc_node[alloc_idx++];
    pnode -> start_time = start_time;
    pnode -> ride_time = 0;
    return pnode;
}

void init_bicycle(){
    alloc_idx = 0;
}

struct PQ{
    BICYCLE* bicycle;
};
int max_durableTime;

struct STATION{
    int deliveryTimes;
    int bicycleNum;
    PQ pq[MAX_PQ + 1];
    int lastnode;
    PQ pq2[MAX_PQ + 1];
    int lasNode2;
}station[MAXN + 5];

int PQ_COMPARE(BICYCLE* b1, BICYCLE* b2){
    return b1 -> ride_time - b2 -> ride_time;
}
int PQ2_COMPARE(BICYCLE* b1, BICYCLE* b2){
    return b1 -> start_time - b2 -> start_time;
}

void PQ_PUSH(basic_ifstrea)