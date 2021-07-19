#define MAX_NODE 10009
#define r register
 
struct Node {
    int id;
    int is_file;
    int file_count;
    int total_size;
    int size;
    int original_size;
    Node* parent;
    Node* child;
    Node* prev;
    Node* next;
}node[MAX_NODE];
 
 
Node* findNode(int id) { // get HASH
    int h = id % MAX_NODE;
    int cnt = MAX_NODE;
    while (node[h].id != 0 && cnt--) {
        if (node[h].id == id) return &node[h];
        h = (h + 1) % MAX_NODE;
    }
    return 0;
}
 
Node* getNode(int id) { // addHash
    int h = id % MAX_NODE;
 
    while (node[h].id != 0) {
        if (node[h].id == id) return &node[h];
 
        h = (h + 1) % MAX_NODE;
    }
    node[h].id = id;
    return &node[h];
}
 
Node* root;
int total_decrease;
int recovered;
 
void init() {
    for (r int i = 0; i < MAX_NODE; ++i) {
        node[i].id = 0;
    }
    root = getNode(10000);
    root->child = 0;
    root->parent = 0;
    root->file_count = 0;
    root->total_size = 0;
}
 
int cmdAdd(int newID, int pID, int fileSize) {
 
    Node* newNode = getNode(newID);
 
    newNode->child = 0;
    newNode->parent = 0;
    newNode->prev = 0;
    newNode->next = 0;
    newNode->is_file = 0;
    newNode->file_count = 0;
    newNode->total_size = 0;
    newNode->size = fileSize;
    newNode->original_size = fileSize;
    if (fileSize > 0) {
        newNode->is_file = 1;
    }
 
    Node* pNode = findNode(pID);
 
    newNode->parent = pNode;
 
    if (!pNode->child) pNode->child = newNode;
    else {
        pNode->child->prev = newNode;
        newNode->next = pNode->child;
        pNode->child = newNode;
    }
 
    if (newNode->is_file) {
        Node* curr = newNode;
        while (curr) {
            curr->file_count++;
            curr->total_size += fileSize;
            curr = curr->parent;
        }
    }
 
    return pNode->total_size;
}
 
int cmdMove(int tID, int pID) {
    Node* tNode = findNode(tID);
 
    if (!tNode->prev) {
        tNode->parent->child = tNode->next;
    }
    else {
        tNode->prev->next = tNode->next;
    }
 
    if (tNode->next) tNode->next->prev = tNode->prev;
 
 
    r Node* curr;
    if (tNode->file_count) {
        curr = tNode;
        while (curr->parent) {
            curr->parent->file_count -= tNode->file_count;
            curr->parent->total_size -= tNode->total_size;
            curr = curr->parent;
        }
    }
 
    Node* pNode = findNode(pID);
 
    tNode->parent = pNode;
    tNode->prev = 0;
    tNode->next = 0;
 
    if (!pNode->child) pNode->child = tNode;
    else {
        pNode->child->prev = tNode;
        tNode->next = pNode->child;
        pNode->child = tNode;
    }
 
    if (tNode->file_count) {
        curr = tNode;
        while (curr->parent) {
            curr->parent->file_count += tNode->file_count;
            curr->parent->total_size += tNode->total_size;
            curr = curr->parent;
        }
    }
 
    return pNode->total_size;
}
 
 
void update(r Node* curr, int increase_size) {
    while (curr) {
        if (curr->is_file) curr->size += increase_size;
        curr->total_size += curr->file_count * increase_size;
        if (curr->child) update(curr->child, increase_size);
        curr = curr->next;
    }
}
 
void recover(r Node* curr, Node* base) {
    while (curr) {
        if (curr->is_file) {
            int decrease = curr->size - curr->original_size;
            total_decrease += decrease;
            curr->size = curr->original_size;
            curr->total_size -= decrease;
            recovered += curr->original_size;
            Node* rev = curr;
            while (rev->parent) {
                if (rev == base) break;
                rev->parent->total_size -= decrease;
                rev = rev->parent;
            }
        }
        if (curr->child) recover(curr->child, base);
        curr = curr->next;
    }
}
 
 
int cmdInfect(int tID) {
    if (root->file_count == 0) return 0;
 
    int increase_size = root->total_size / root->file_count;
    int total_increase = 0;
    Node* tNode = findNode(tID);
 
    if (tNode->is_file) tNode->size += increase_size;
    total_increase = tNode->file_count * increase_size;
    tNode->total_size += total_increase;
 
    r Node* curr = tNode;
 
    while (curr->parent) {
        curr->parent->total_size += total_increase;
        curr = curr->parent;
    }
 
    update(tNode->child, increase_size);
 
    return tNode->total_size;
}
 
int cmdRecover(int tID) {
    total_decrease = 0;
    recovered = 0;
 
    Node* tNode = findNode(tID);
    if (tNode->is_file) {
        total_decrease += tNode->size - tNode->original_size;
        tNode->size = tNode->original_size;
        tNode->total_size -= total_decrease;
        recovered += tNode->original_size;
    }
 
    recover(tNode->child, tNode);
 
    r Node* curr = tNode;
    while (curr->parent) {
        curr->parent->total_size -= total_decrease;
        curr = curr->parent;
    }
 
    return recovered;
}
 
int cmdRemove(int tID) {
    Node* tNode = findNode(tID);
    total_decrease = 0;
 
    if (tNode == root) {
        total_decrease = root->total_size;
        root->child = 0;
        root->file_count = 0;
        root->total_size = 0;
    }
    else {
        total_decrease = tNode->total_size;
        Node* curr = tNode;
        while (curr->parent) {
            curr->parent->total_size -= tNode->total_size;
            curr->parent->file_count -= tNode->file_count;
            curr = curr->parent;
        }
 
        if (!tNode->prev) {
            tNode->parent->child = tNode->next;
        }
        else {
            tNode->prev->next = tNode->next;
        }
        if (tNode->next) tNode->next->prev = tNode->prev;
    }
 
    return total_decrease;
}