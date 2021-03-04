

//push 
void push(int new_val){
    if(size == MAX_HEAP){ // 만일 가득 차있으면
        return;
    }

    int current = ++size;
    while(current != 1 && HEAP[current >> 1] < new_val){ // max heap
        HEAP[current] = HEAP[current >> 1];
        current >>= 1;
    }
    HEAP[current] = new_val;
    return;
}

//pop

void pop(){
    if(size == 0){
        return;
    }

    int end = HEAP[size--];
    int current = 1, change = 2;
    while(change <= size){
        if(change + 1 <= size && HEAP[change] < HEAP[change + 1]) change++;
        if (HEAP[change] <= end) break;
	    HEAP[current] = HEAP[change];
	    current = change; change *= 2;
    }
    HEAP[current] = end;
    return;
}