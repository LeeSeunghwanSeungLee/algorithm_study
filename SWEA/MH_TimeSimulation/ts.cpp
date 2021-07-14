#define MAX_BUS 100000
 
class Bus
{
public: 
    int atime;
    int ttime;
    int num;
    int id;
};

Bus bus[MAX_BUS+10];
Bus* stack[MAX_BUS + 10];
int nActive = 0;
int nBus = 0;
 
void init() { // flag 를 사용
    nActive = 0;
    nBus = 0;
}
 
void start(int time, int idx, int traveltime, int num) 
{
    bus[nBus].id = idx;
    bus[nBus].atime = time;
    bus[nBus].ttime = time + traveltime;
    bus[nBus].num = num;
    stack[nActive++] = &bus[nBus++];
}
 
int getSum(int time) 
{
     
    register int i, sum;    
    sum = 0;
    for (i = 0; i < nActive; ) {
        if (time >= stack[i]->ttime) {
            stack[i] = stack[--nActive];
        }
        else {
            sum += stack[i]->num;
            i++;
        }
    }
    return sum;
}
 
int getLast(int time) 
{
    register int i, last;
    register Bus* p = 0;
    last = 0;
    for (i = 0; i < nActive; ) {
        if (time >= stack[i]->ttime) stack[i] = stack[--nActive];
        else {
            if (last < stack[i]->ttime) {
                p = stack[i];
                last = p->ttime;
            }
            else if (last == stack[i]->ttime) {
                if (p->id > stack[i]->id) p = stack[i];
            }
            i++;
        }
    }
    return p->id;
}
 
int getMax(int time) 
{   
    register int i, max;
    register Bus* p = 0;
    max = 0;
    for (i = 0; i < nActive;) {
        if (time >= stack[i]->ttime) stack[i] = stack[--nActive]; 
        else {
            if (max < stack[i]->num) {
                p = stack[i];
                max = p->num;
            }
            else if (max == stack[i]->num) {
                if (p->id > stack[i]->id) p = stack[i];
            }
            i++;
        }
    }
    return p->id;
}
