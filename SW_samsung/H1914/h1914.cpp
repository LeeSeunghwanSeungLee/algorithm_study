#define MAX_N 100
#define MAX_TOOL 50

#define MAX_STEPS 101
#define MAX_EVENTS 100001

typedef struct TOOL{
    int id;
    int pt;
    int step;
    int running;
    TOOL* next;
}_tool;

typedef struct STEP{
    int id;
    int remain;
    int tool_cnt;
    int tool_num;
    _tool* next;
}_step;

typedef struct EVENT{
    int id;
    int endtime;
    int tool;
}_event;

_step arr_step[MAX_STEPS];

_tool arr_tool[MAX_EVENTS];
int arr_tool_idx;

_event arr_event[MAX_EVENTS];
int arr_event_idx;

_event* heap[MAX_EVENTS];
int heapSize;

int step_num;
int done;



bool compare(int a, int b) {
    if (arr_event[a].endtime < arr_event[b].endtime 
        || (arr_event[a].endtime == arr_event[b].endtime && arr_tool[arr_event[a].tool].step > arr_tool[arr_event[b].tool].step) 
        || (arr_event[a].endtime == arr_event[b].endtime && arr_tool[arr_event[a].tool].step == arr_tool[arr_event[b].tool].step && arr_tool[arr_event[a].tool].pt < arr_tool[arr_event[b].tool].pt)){
        return true;
    }
    return false;
}





int heapPush(int value){
}

int heapPop(){
}

void init(int N){
    step_num = N;
    arr_event_idx = 0;
    arr_tool_idx = 0;
    done = 0;
    heapSize = 0;

    for(register int i = 0; i < step_num; i++){
        arr_step[i].id = -1;
        arr_step[i].next = 0;
        arr_step[i].remain = 0;
        arr_step[i].tool_cnt = 0;
        arr_step[i].tool_num = 0;
    }
}


void setupTool(int T, int stepNo[5000], int procTime[5000]){
    _tool* nT;
    _tool* cur;
    _tool* tmp;

    for(register int i = 0; i < T; i++){
        nT = &arr_tool[arr_tool_idx++];
        nT -> id = arr_tool_idx - 1;
        nT -> pt = procTime[i];
        nT -> running = false;
        nT -> step = stepNo[i];

        tmp = 0;

        for (cur = arr_step[stepNo[i]].next; cur; cur = cur -> next) {
            if(cur -> pt > nT -> pt) break;

            tmp = cur;
        }

        if(tmp == 0){
            nT -> next = arr_step[stepNo[i]].next;
            arr_step[stepNo[i]].next = nT;
        }
        else {
            nT -> next = cur;
            tmp -> next = nT;
        }

        if(arr_step[stepNo[i]].id == -1){
            arr_step[stepNo[i]].id = stepNo[i];
        }
        arr_step[stepNo[i]].tool_cnt++;
        arr_step[stepNo[i]].tool_num++;
    }
}
