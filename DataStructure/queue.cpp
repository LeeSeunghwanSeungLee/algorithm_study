#include <iostream>

using namespace std;


typedef struct Queue{
    int data[100];
    int head = 0;
    int tail = 0;
    int capacity = 0;

    void creat(int x){
        capacity = x;
    }

    void push(int x){
        if(tail - head >= capacity) cout << "overflow"<<'\n';
        else{
            data[tail++] = x;
        }
    }

    void pop(){
        if(tail - head <= 0) cout << "underflow" << '\n';
        else{
            data[head] = 0;
            head++;
        }
    }

    int front(){
        if(tail - head <= 0) return -1;
        else return data[head]; 
    }

    int size(){
        return (tail - head);
    }


}queue;