#include <iostream>

using namespace std;

typedef struct Stack{
    int data[110];
    int len = 0;
    int capacity = 0;

    void create(int x){
        capacity = x;
    }

    void push(int x){
        if(len >= capacity) cout << "overflow" <<'\n';

        else{
            data[len++] = x; // 현재 위치에 넣고, len++ 실행
        }
    }

    void pop(){
        if(len <= 0) cout << "underflow" << '\n';
        else {
            data[len--] = 0;
        }
    }

    int top(){
        if(len <= 0) cout << "null" << '\n';
        else{
            return data[len--];
        }
    }

} stack;
