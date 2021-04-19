#define MAX_SIZE 10002

int table[MAX_SIZE];
int s = MAX_SIZE - 1;

void init(){
    while(s >= 1){
        table[s--] = 0;
    }
}

void insert(int name, int parent){
    table[name] = parent;
    s++;
}

void remove(int name){
    table[name] = 0;

   /*for(register int i = 1; i <= s; i++){ // 시간낭비 포인트
        if(table[i] == name) remove(i);
    }*/
}

int findAnce(int name , int ance[]){ 
    int anc_cnt = 0;
    while(table[name] != 0){
        ance[anc_cnt++] = table[name];
        name = table[name];
    }
    return anc_cnt;
}
int findDesc(int name , int target){
    if(table[target] == name) return 1;
    if(table[target] == 0) return 0;
    findDesc(name, table[target]);
}

// 단순한 배열을 이용햇음
// 재귀 <<< 넘사벽 <<< 반복문이며
// 만일 굳이 플래그를 수정하지 않아도 되는부분은 건드리지 않는게 좋을 때도 있다 -> 절반감소