#include <iostream>

using namespace std;


template<typename T>
struct Node{
    T value;
    Node<T>* next = nullptr;
};

template <typename T> 
class Stack 
{ 
private: 
    Node<T>* head; 
    Node<T>* tail; 
public: Stack() :head(nullptr), tail(nullptr) {} 
~Stack() { } 
void Push(T value); 
T Pop(); 
bool isEmpty(); 
T Top(); 
};

