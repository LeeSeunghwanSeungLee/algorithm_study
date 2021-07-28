#define MAXL    5
#define MAXF    10
#define MAX_USER 10001
#define MAX_NODE 1000000
  
struct Node {
    int id;
    int idx;
    bool deleted;
    Node* next;
};
Node node[MAX_NODE];
int node_count;
Node* user[MAX_USER];
  
int userN;
  
void init(int N) {
    userN = N;
    node_count = 0;
    for (register int i = 0;i < MAX_USER; i++) {
        user[i] = 0;
    }
}
  
void Make_NewNode(int id1, int id2) {
    Node& newNode = node[node_count++];
    newNode.id = id1;
    newNode.deleted = false;
    newNode.idx = node_count - 1;
    newNode.next = user[id2];
    user[id2] = &newNode;
}
  
void add(int id, int F, int ids[MAXF]) {
      
    for (register int i = 0;i < F;i++) {
        Make_NewNode(id, ids[i]);
        Make_NewNode(ids[i], id);
    }
}
  
void del(int id1, int id2) {
  
    Node *  cur = user[id1];
    while (cur) {
        if (cur->id == id2) {
            node[cur->idx].deleted = true;
            break;
        }
        cur = cur->next;
    }
    cur = user[id2];
    while (cur) {
        if (cur->id == id1) {
            node[cur->idx].deleted = true;
            break;
        }
        cur = cur->next;
    }
}
  
int recommend(int id, int list[MAXL]) {
    int Alluser[MAX_USER];
    for (register int i = 0; i < MAX_USER; i++) {
        Alluser[i] = 0;
    }
      
    Alluser[id] = -1;
    int max = 0;
    Node * curfriend = user[id];
    while (curfriend) {
        if (curfriend->deleted) {
            curfriend = curfriend->next;
            continue;
        }
        Alluser[curfriend->id] = -1;
          
        Node* recfriend = user[curfriend->id];
        while (recfriend) {
            if (recfriend->deleted || Alluser[recfriend->id] == -1) {
                recfriend = recfriend->next;
                continue;
            }
            Alluser[recfriend->id]++;
            if (max < Alluser[recfriend->id]) max = Alluser[recfriend->id];
            recfriend = recfriend->next;
        }
        curfriend = curfriend->next;
    }
  
    int cnt = 0;
    while (cnt<5 && max > 0) {
        for (register int i = 1; i <= userN;i++) {
            if (Alluser[i] == max) {
                list[cnt++] = i;
                if (cnt == 5) break;
            }
        }
        max--;
    }
      
    return cnt;
}