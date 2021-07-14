#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


#define MAX_LEN 100001
#define GROUP 6
//////////////////////////////////////////
struct Soldier{
    int sID;
    int gID;
    int score;
}poolSoldier[MAX_LEN];
//////////////////////////////////////////

bool cmp(int a, int b){
    if(poolSoldier[a].score > poolSoldier[b].score) return true; 
    else if(poolSoldier[a].score == poolSoldier[b].score && poolSoldier[a].sID > poolSoldier[b].sID) return true;
    return false;
}
list<int> sortedArr[GROUP];

//////////////////////////////////////////
void init(){
    for(int i = 1; i <= 5; i++) sortedArr->clear();
}

void hire(int mID, int mTeam, int mScore){
    poolSoldier[mID].sID = mID;
    poolSoldier[mID].gID = mTeam;
    poolSoldier[mID].score = mScore;
    sortedArr[mTeam].push_back(mID);
}

void fire(int mID){
    Soldier* aTarget = &poolSoldier[mID];
    int arr_val = aTarget -> sID;
    int group = aTarget -> gID;
    sortedArr[group].remove(arr_val);
}

void updateSoldier(int mID, int mScore){
    Soldier* aTarget = &poolSoldier[mID];
    aTarget -> score = mScore;
}

void updateTeam(int mTeam, int mChangeScore){
    auto it = sortedArr[mTeam].begin();
    for(; it != sortedArr[mTeam].end(); it++){
        int sId = *it;
        poolSoldier[sId].score += mChangeScore;
        if(poolSoldier[sId].score > 5) poolSoldier[sId].score = 5;
        else if(poolSoldier[sId].score < 1) poolSoldier[sId].score = 1;
    }
}

int bestSoldier(int mTeam){
    sortedArr[mTeam].sort(cmp);
    return sortedArr[mTeam].front();   
}