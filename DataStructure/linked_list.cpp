typedef struct LinkedList{
    int data;
    node* prev;
    node* next;
}node;

node* head;

void deleteLinkedList(int val){
    node* walker = head;

    while(walker){
        if (walker->val == val) { // if delete node is head
            if (!walker->prev) { // if head node,
                head = head->next;
                if(head->next)
                    head->next->prev = NULL;
            }
            else { // if delete node is middle or last
                walker->prev->next = walker->next;
                if (walker->next) // if walker's next is NULL (Last node)
                    walker->next->prev = walker->prev;
            }
            return;
        }
        walker = walker->next;
    }
}

void insertLinkedList(int val){
    node* newNode = salloc();
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->val = val;

    if(!head){
        head = newNode;
        return;
    }
    else{
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        return;
    }
}