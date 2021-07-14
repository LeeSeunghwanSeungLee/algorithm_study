// single linked list 구현
//https://xtar.tistory.com/33

template<typename T>
struct Node{
public:
    T value;
    struct Node<T>* next = nullptr;
};

template<typename T>
class SingleLinkedList{
    private: 
        Note<T>* head;
        Node<T>* tail;
        int size = 0;
    public:
        SingleLinkedList() : head(nullptr), tail(nullptr) {} // 생성자
        ~SingleLinkedList() {} // 소멸자

        void AddNode(T val){
            Node<T>* new_node = new Node<T>;

            this->size++;
            new_node->value = val;
            new_node->next = nullptr;

            if(head == nullptr){
                this->head = new_node;
                this->tail = new_node;
            }
            else{
                tail->next = new_node;
                tail = new_node;
            }
        }

        void RemoveNode(T val){
            Node<T>* now = head;
            Node<T> *tmp = now;

            while(now != nullptr){
                if(now->value == val){
                    break;
                }
                else{
                    tmp = now; // 목표의 전 노드 수정을 위함
                    now = now->next;
                }
            }
            if(now == nullptr){
                cout << "찾을 수 없는 노드입니다"<<"\n";
            }
            else{
                size--;
                cout << "삭제된 노드의 값 : " << now -> value << '\n';
                tmp->next = now->next;
                delete now;
            }
        }

        void show(){
            Node<T>* now = head;
            while(now != nullptr){
                cout << now->value << '->';
                now = now->next;
            }
            cout << '\n';
        }

        void DeleteList(){
            Node<T>* now = head;
            while(now != nullptr){
                head = now->next;
                delete now;
                now = head;
            }
            delete head; //nullptr 조차 삭제해버려야한다...
            size = 0;
            cout << "리스트가 삭제되었습니다" << '\n';
        }

        void RemoveHead(){

        }

        void AddPosition(){

        }

        void SearchValue(){

        }

        int size(){
            return this->size;
        }
};