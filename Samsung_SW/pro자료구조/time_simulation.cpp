#define MAX_BUS 71000
 
typedef struct Bus {
    int endtime;
    int idx;
    int num;
}Bus;
 
Bus busbusbusbus[MAX_BUS];
int cnt;
 

void init() {
    cnt = 0;
}
 
void start(int time, int idx, int traveltime, int num) {
    busbusbusbus[cnt++] = { time + traveltime, idx, num }; 
}
 
int getSum(int time) {
    register int sum = 0;
    for(register int i =0; i<cnt;)
    {
        if (busbusbusbus[i].endtime <= time) busbusbusbus[i] = busbusbusbus[--cnt];
        else
        {
            sum += busbusbusbus[i].num;
            i++;
        }
 
    }
    return sum;
}
 
int getLast(int time) {
    register int idx = 0, last = 0;
    for (register int i = 0; i < cnt;)
    {
        if (busbusbusbus[i].endtime <= time) busbusbusbus[i] = busbusbusbus[--cnt];
        else
        {
            if(last < busbusbusbus[i].endtime)               
            {
                last = busbusbusbus[i].endtime;
                idx = busbusbusbus[i].idx;
            }
            else if ((last == busbusbusbus[i].endtime) && (idx > busbusbusbus[i].idx)) idx = busbusbusbus[i].idx;
 
            i++;
        }
 
    }
    return idx;
}
 
int getMax(int time) {
    register int idx = 0, max = 0;
    for (register int i = 0; i < cnt;)
    {
        if (busbusbusbus[i].endtime <= time) busbusbusbus[i] = busbusbusbus[--cnt];
        else
        {
            if (max < busbusbusbus[i].num)
            {
                max = busbusbusbus[i].num;
                idx = busbusbusbus[i].idx;
 
            }
            else if((max == busbusbusbus[i].num) && (idx > busbusbusbus[i].idx)) idx = busbusbusbus[i].idx;
 
            i++;
        }
 
    }
    return idx;
}