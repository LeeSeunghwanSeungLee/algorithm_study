#define COUPLE 0
#define PARENT 1
#define CHILD 2

#define MAX_M 200
#define MAX_HASH 507
#define ULL unsigned long long
#define rint register int

struct NODE{
    int uid;
    ULL val;
    int sex;
    NODE* couple;
    NODE* parent;
    NODE* next;
}npool[MAX_M], *hash[MAX_HASH];
int np;

int dist[MAX_M][MAX_M];
int count[MAX_M][MAX_M];

ULL get_val(char* str){
    register ULL val = 0;
    for(rint i = 0; str[i]; i++){
        val = (val << 5) + str[i] - 'a' + 1;
    }
    return val;
}

NODE* add_node(char* name, int sex){
    register ULL val = get_val(name);
    npool[np] = {np, val, sex, 0, 0, 0};
    register NODE* node = &npool[np++];
    node -> next = hash[val % MAX_HASH];
    hash[val % MAX_HASH] = node;
    return node;
}

NODE* find_node(char* name){
    register ULL val = get_val(name);
    for(register NODE* p = hash[val % MAX_HASH]; p; p = p -> next){
        if(p -> val == val){
            return p;
        }
    }
    return 0;
}

void update_dist(int uid1, int uid2, int add_dist){ // 기존 멤버 , 신규멤버, 추가거리
   for(rint i = 0; i < np - 1; i++){
       dist[uid2][i] = dist[i][uid2] = dist[uid1][i] + add_dist;
       count[uid2][dist[uid2][i]]++;
       count[i][dist[uid2][i]]++;
   }
}

void init(char initialMemberName[], int initialMemberSex){
    np = 0;
    for(rint i = 0; i < MAX_HASH; i++){
        hash[i] = 0;
    }

    for(rint i = 0; i < MAX_M; i++){
        for(rint j = 0; j < MAX_M; j++){
            dist[i][j] = count[i][j] = 0;
        }
    }
    add_node(initialMemberName, initialMemberSex);
}


bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
    register NODE* node = find_node(existingMemberName);
    
    if(relationship == COUPLE && (node -> couple || node -> sex == newMemberSex)) return false;

    if(relationship == PARENT && node-> parent && (node -> parent -> couple || node -> parent -> sex == newMemberSex)) return false;

    register NODE* new_node = add_node(newMemberName, newMemberSex);

    rint uid = node -> uid;
    rint add_dist = 0;

    if(relationship == COUPLE){
        node -> couple = new_node;
        new_node -> couple = node;
    }
    else if(relationship == PARENT){
        if(node -> parent){
            node -> parent -> couple = new_node;
            new_node -> couple = node -> parent;
            uid = node -> parent -> uid;
        }
        else{
            node -> parent = new_node;
            add_dist = 1;
        }
    }
    else{ // children
        new_node -> parent = node;
        add_dist = 1;
    }
    update_dist(uid, new_node -> uid, add_dist);
	return false;
}

int getDistance(char nameA[], char nameB[])
{
    register NODE* nodeA = find_node(nameA);
    register NODE* nodeB = find_node(nameB);
	return dist[nodeA -> uid][nodeB -> uid];
}

int countMember(char name[], int dist)
{
	register NODE* node = find_node(name);
    return count[node->uid][dist];
}

