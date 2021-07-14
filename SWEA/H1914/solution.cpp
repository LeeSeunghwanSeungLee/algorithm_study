#define MAX_N    100
#define MAX_TOOL 50
 
#define MAX_STEPS 101
#define MAX_EVENTS 100001
 
typedef struct TOOL {
    int id;
    int pt;
    int step;
    bool running;
    TOOL* next;
}_tool;
 
typedef struct STEP {
    int id;
    int remain;
    int tool_cnt;
    int tool_num;
    _tool* next;
}_step;
 
typedef struct EVENT {
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
 
int heapPush(int value)
{
    heap[heapSize] = &arr_event[value];
 
    int current = heapSize;
    while (current > 0 && compare(heap[current]->id, heap[(current - 1) / 2]->id))
    {
        _event* temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
 
    heapSize = heapSize + 1;
 
    return 1;
}
 
int heapPop()
{
    heapSize = heapSize - 1;
 
    heap[0] = heap[heapSize];
 
    int current = 0;
    while (current * 2 + 1 < heapSize)
    {
        int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = compare(heap[current * 2 + 1]->id, heap[current * 2 + 2]->id) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (compare(heap[current]->id, heap[child]->id))
        {
            break;
        }
 
        _event* temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
 
        current = child;
    }
    return 1;
}
 
void init(int N) {
    step_num = N;
    arr_event_idx = 0;
    arr_tool_idx = 0;
    done = 0;
    heapSize = 0;
 
    for (int i = 0; i < step_num; i++) {
        arr_step[i].id = -1;
        arr_step[i].next = 0;
        arr_step[i].remain = 0;
        arr_step[i].tool_cnt = 0;
        arr_step[i].tool_num = 0;
    }
}
 
void setupTool(int T, int stepNo[5000], int procTime[5000]) {
    _tool* nT;
    _tool* cur;
    _tool* tmp;
 
    for (int i = 0; i < T; i++) {
        nT = &arr_tool[arr_tool_idx++];
        nT->id = arr_tool_idx - 1;
        nT->pt = procTime[i];
        nT->running = false;
        nT->step = stepNo[i];
 
        tmp = 0;
 
        for (cur = arr_step[stepNo[i]].next; cur; cur = cur->next) {
            if (cur->pt > nT->pt) {
                break;
            }
            tmp = cur;
        }
 
        if (tmp == 0) {
            nT->next = arr_step[stepNo[i]].next;
            arr_step[stepNo[i]].next = nT;
        }
        else {
            nT->next = cur;
            tmp->next = nT;
        }
 
        if (arr_step[stepNo[i]].id == -1) {
            arr_step[stepNo[i]].id = stepNo[i];
        }
 
        arr_step[stepNo[i]].tool_cnt++;
        arr_step[stepNo[i]].tool_num++;
    }
}
 
void update(int time) {
    _event* tmp = 0;
    _event* nE;
    _tool* cur;
 
    while (heapSize != 0 && heap[0]->endtime <= time) {
        tmp = heap[0];
        arr_tool[tmp->tool].running = false;
        arr_step[arr_tool[tmp->tool].step].tool_cnt++;
         
        heapPop();
 
        if (arr_tool[tmp->tool].step < step_num - 1) {
            if (arr_step[arr_tool[tmp->tool].step + 1].tool_cnt != 0) {
                for (cur = arr_step[arr_tool[tmp->tool].step + 1].next; cur; cur = cur->next) {
                    if (cur->running == false) {
                        break;
                    }
                }
 
                cur->running = true;
                nE = &arr_event[arr_event_idx++];
                nE->endtime = tmp->endtime + cur->pt;
                nE->tool = cur->id;
                nE->id = arr_event_idx - 1;
                arr_step[arr_tool[tmp->tool].step + 1].tool_cnt--;
 
                heapPush(arr_event_idx - 1);
            }
            else {
                arr_step[arr_tool[tmp->tool].step + 1].remain++;
            }
        }
        else {
            done++;
        }
 
        if (arr_step[arr_tool[tmp->tool].step].remain != 0) {
            arr_tool[tmp->tool].running = true;
 
            nE = &arr_event[arr_event_idx++];
            nE->tool = tmp->tool;
            nE->endtime = tmp->endtime + arr_tool[tmp->tool].pt;
            nE->id = arr_event_idx - 1;
            arr_step[arr_tool[tmp->tool].step].tool_cnt--;
            arr_step[arr_tool[tmp->tool].step].remain--;
 
            heapPush(arr_event_idx - 1);
        }
    }
}
 
void addLot(int time, int number) {
    _tool* cur;
    _event* nE;
    int lots = number;
 
    update(time);
 
    if (arr_step[0].tool_cnt != 0) {
        while (arr_step[0].tool_cnt != 0 && lots != 0) {
            for (cur = arr_step[0].next; cur; cur = cur->next) {
                if (cur->running == false) {
                    nE = &arr_event[arr_event_idx++];
                    nE->tool = cur->id;
                    nE->endtime = time + arr_tool[cur->id].pt;
                    nE->id = arr_event_idx - 1;
                    cur->running = true;
 
                    heapPush(arr_event_idx - 1);
 
                    arr_step[0].tool_cnt--;
                    lots--;
                    break;
                }
            }
        }
 
        if (lots != 0) {
            arr_step[0].remain += lots;
        }
    }
    else {
        arr_step[0].remain += number;
    }
}
 
int simulate(int time, int wip[MAX_N]) {
    update(time);
 
    for (int i = 0; i < step_num; i++) {
        wip[i] += arr_step[i].remain;
        wip[i] += (arr_step[i].tool_num - arr_step[i].tool_cnt);
    }
 
    return done;
}