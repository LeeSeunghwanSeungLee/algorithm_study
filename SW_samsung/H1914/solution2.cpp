#define MAX_N 100
#define MAX_TOOL 5000
#define MAX_SIZE 50
#define MAX_EVENT 100000
 
struct Tool
{
    int tool_id;
    int step_no;
    int pt;
} tool[MAX_TOOL];
 
struct Event
{
    int tool_id;
    int step_no;
    int end_time;
    int pt;
} e[MAX_EVENT];
 
struct Step
{
    int working_lot;
    int waiting_lot;
} step[MAX_N];
 
int total_step = 0;
int remain_lot = 0;
int ship_lot = 0;
 
int heap[MAX_N][MAX_SIZE];
int heapSize[MAX_N];
 
bool comp(int idx1, int idx2)
{
    if (tool[idx1].pt < tool[idx2].pt)
        return true;
    return false;
}
 
bool comp_w(int idx1, int idx2)
{
    if (e[idx1].end_time < e[idx2].end_time)
        return true;
    else if (e[idx1].end_time == e[idx2].end_time)
    {
        if (e[idx1].step_no > e[idx2].step_no)
            return true;
        else if (e[idx1].step_no == e[idx2].step_no)
        {
            if (e[idx1].pt < e[idx2].pt)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
 
int heapPush(int s, int value)
{
    heap[s][heapSize[s]] = value;
 
    int current = heapSize[s];
    while (current > 0 && comp(heap[s][current], heap[s][(current - 1) / 2]))
    {
        int temp = heap[s][(current - 1) / 2];
        heap[s][(current - 1) / 2] = heap[s][current];
        heap[s][current] = temp;
        current = (current - 1) / 2;
    }
 
    heapSize[s] = heapSize[s] + 1;
 
    return 1;
}
 
int heapPop(int s, int* value)
{
    *value = heap[s][0];
    heapSize[s] = heapSize[s] - 1;
 
    heap[s][0] = heap[s][heapSize[s]];
 
    int current = 0;
    while (current * 2 + 1 < heapSize[s])
    {
        int child;
        if (current * 2 + 2 == heapSize[s])
        {
            child = current * 2 + 1;
        }
        else
        {
            child = comp(heap[s][current * 2 + 1], heap[s][current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (comp(heap[s][current], heap[s][child]))
        {
            break;
        }
 
        int temp = heap[s][current];
        heap[s][current] = heap[s][child];
        heap[s][child] = temp;
 
        current = child;
    }
    return 1;
}
 
int heap_w[MAX_EVENT];
int heapSize_w = 0;
int eventIdx = 0;
 
int heapPush_w(int value)
{
    heap_w[heapSize_w] = value;
 
    int current = heapSize_w;
    while (current > 0 && comp_w(heap_w[current], heap_w[(current - 1) / 2]))
    {
        int temp = heap_w[(current - 1) / 2];
        heap_w[(current - 1) / 2] = heap_w[current];
        heap_w[current] = temp;
        current = (current - 1) / 2;
    }
 
    heapSize_w = heapSize_w + 1;
 
    return 1;
}
 
int heapPop_w(int* value)
{
    *value = heap_w[0];
    heapSize_w = heapSize_w - 1;
 
    heap_w[0] = heap_w[heapSize_w];
 
    int current = 0;
    while (current * 2 + 1 < heapSize_w)
    {
        int child;
        if (current * 2 + 2 == heapSize_w)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = comp_w(heap_w[current * 2 + 1], heap_w[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (comp_w(heap_w[current], heap_w[child]))
        {
            break;
        }
 
        int temp = heap_w[current];
        heap_w[current] = heap_w[child];
        heap_w[child] = temp;
 
        current = child;
    }
    return 1;
}
 
void init(int N) {
    total_step = N; eventIdx = 0;
    heapSize_w = 0; ship_lot = 0; remain_lot = 0; 
 
    for (register int i = 0; i < MAX_N; i++)
    {
        heapSize[i] = 0;
        step[i].waiting_lot = 0;
        step[i].working_lot = 0;
    }
}
 
void setupTool(int T, int stepNo[5000], int procTime[5000]) {
    for (register int i = 0; i < T; i++)
    {
        tool[i].step_no = stepNo[i];
        tool[i].pt = procTime[i];
        tool[i].tool_id = i;
        heapPush(stepNo[i], i);      // 공정 단계별 대기 힙에 설비 push 
    }
}
 
void update(int time)
{
    int cur_idx = 0, next_idx = 0, cur_step = 0, cur_tool = 0, end_time = 0;
 
    // 공정 워킹 힙에 들어있는 작업 중인 설비들의 end 시간이
    // update 로 들어온 time 시간에 도달할때까지 pop 을 시킨 뒤 다음 단계로 이동시킴
 
    while (time >= e[heap_w[0]].end_time)
    {
        end_time = e[heap_w[0]].end_time;
        heapPop_w(&cur_idx);
 
        cur_tool = e[cur_idx].tool_id;
        cur_step = e[cur_idx].step_no;
        step[cur_step].working_lot--;
 
        if (cur_step != total_step - 1)
        {
            if (heapSize[cur_step + 1] > 0)
            {
                // 현재 공정이 마지막 공정이 아니고, 다음 공정의 대기 힙이 있으면 다음 공정에 투입
                heapPop(cur_step + 1, &next_idx);
 
                e[eventIdx].end_time = end_time + tool[next_idx].pt;
                e[eventIdx].step_no = tool[next_idx].step_no;
                e[eventIdx].pt = tool[next_idx].pt;
                e[eventIdx].tool_id = tool[next_idx].tool_id;
                heapPush_w(eventIdx);
                eventIdx++;
                step[cur_step + 1].working_lot++;
            }
            else
            {
                // 다음 공정의 가용 설비가 없으면 대기한다
                step[cur_step + 1].waiting_lot++;
            }
        }
        else
        {
            ship_lot++;
        }
 
        // 현재 공정에 대기 중인 lot 이 있으면 투입 시킨다
        if (step[cur_step].waiting_lot > 0)
        {
            e[eventIdx].end_time = end_time + tool[cur_tool].pt;
            e[eventIdx].step_no = tool[cur_tool].step_no;
            e[eventIdx].pt = tool[cur_tool].pt;
            e[eventIdx].tool_id = tool[cur_tool].tool_id;
            heapPush_w(eventIdx++);
 
            step[cur_step].working_lot++;
            step[cur_step].waiting_lot--;
        }
        else
        {
            // 대기 중인 lot 이 없으면 해당 공정의 대기힙에 push 해서 대기 시킨다
            heapPush(cur_step, cur_tool);
        }
    }
}
 
void addLot(int time, int number) {
    int idx = 0;
    if (time > 0) update(time);
     
    step[0].waiting_lot += number;
 
    while (step[0].waiting_lot > 0 && heapSize[0] > 0)
    {
        heapPop(0, &idx);
         
        e[eventIdx].end_time = time + tool[idx].pt;
        e[eventIdx].step_no = tool[idx].step_no;
        e[eventIdx].pt = tool[idx].pt;
        e[eventIdx].tool_id = tool[idx].tool_id;
        heapPush_w(eventIdx++);
        step[0].working_lot++;
        step[0].waiting_lot--;
    }
}
 
int simulate(int time, int wip[MAX_N]) {
    update(time);
    for (register int i = 0; i < total_step; i++)
    {
        wip[i] = step[i].waiting_lot + step[i].working_lot;
    }
    return ship_lot;
}