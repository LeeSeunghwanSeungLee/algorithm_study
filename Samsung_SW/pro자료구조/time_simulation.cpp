#define MAX_BUS_NUM 70001
#define MAX_TIME 400001
#define NULL 0

typedef struct BUS{
    int idx;
    int end_time;
    int num;
    BUS* next;
}bus;

bus ALLOC[MAX_BUS_NUM];
int alloc_id = 0;

bus* TIME_LINE[MAX_TIME];

bus* bus_alloc(){
    return &ALLOC[alloc_id++];
}

void init(){
    alloc_id = 0;
    for(register int i = 0; i < MAX_TIME ; i++){
        TIME_LINE[i] = NULL;
    }
}

void start(int time, int idx , int traveltime, int num){
    bus* n_bus = bus_alloc();

    register int start = time;
    int end = start + traveltime;

    n_bus->idx = idx;
    n_bus->end_time = end;
    n_bus->num = num;
    n_bus->next = NULL;

    for (start; start < end; start++){
        if(TIME_LINE[start] == NULL){ //만일 처음이면
            TIME_LINE[start] = n_bus;
        }
        else{ // 처음이 아니면
            bus* now_bus = TIME_LINE[start];
            while(now_bus->next != NULL){
                now_bus = now_bus -> next;
            }
            now_bus->next = n_bus;
        }
    }
}

int getSum(int time){
    int tot = 0;
    bus* now_bus = TIME_LINE[time];
    if(now_bus == NULL) return tot;

    while(now_bus->next != NULL){
        tot += now_bus -> num;
        now_bus = now_bus -> next;
    }

    tot += now_bus -> num;
    return tot;
}

int getLast(int time){
    bus* now_bus = TIME_LINE[time];
    int end = now_bus -> end_time;
    while(now_bus->next != NULL){
        now_bus = now_bus -> next;
        if(end < now_bus -> end_time) end = now_bus -> end_time;
    }
    if(end > now_bus -> end_time) end = now_bus -> end_time;
    return end;
}

int getMax(int time){
    bus* now_bus = TIME_LINE[time];
    int num = now_bus -> num;
    while(now_bus->next != NULL){
        now_bus = now_bus -> next;
        if(num < now_bus -> num) num = now_bus -> num;
    }
    if(num < now_bus -> num) num = now_bus -> num;
    return num;
}


// 1st try => time error!



