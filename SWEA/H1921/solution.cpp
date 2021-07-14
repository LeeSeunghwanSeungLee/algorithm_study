#define MAX_USER 1001
#define MAX_AREA 11
#define HASH 100001

// 구조체

struct Package {
	int id;
	int area;
	int price;
	int userId;
	Package* next;
};
Package* PACKAGE[HASH]; // 메모리를 아끼기 위함
int pId[HASH];

Package* heap[MAX_USER][MAX_AREA][1000000];
int heapId[MAX_USER][MAX_AREA];


struct User {
	int id;
	User* friends;
	Package* reserve; 
};
User USER[MAX_USER];
int uId(0);



void push(int user_id, int area, Package* n_p) {

}
void pop(int package_id) { // 중간 노드가 사라질수 있음을 명심

}

// 본 함수

void init(int N, int M)
{
	uId = N;
	for (register int i = 1; i <= N; i++) {
		USER[i].id = i;
		USER[i].friends = 0;
		USER[i].reserve = 0;
		for (register int j = 0; j < MAX_AREA; j++) {
			heapId[i][j] = 0;
		}
	}

	for (register int i = 1; i <= HASH; i++)
		pId[i] = 0;
	
	return;
}

void befriend(int uid1, int uid2)
{
	// USER[uid1].friends에 USER[uid2] 추가
	// USER[uid2].friends에 USER[uid1] 추가

	// USER[uid1].package_id 가 존재시 => 해당 패키지를 찾아가서 Area 와 해당 패키지 주소를 준비한다
		// heap[uid2][Area].push(&패키지주소);
		// heap[uid2][Area]++;

	// USER[uid2].package_id 가 존재시 => 해당 패키지를 찾아가서 Area와 해당 패키지 주소를 준비한다
		// heap[uid2][Area].push(&패키지주소);
		// heap[uid2][Area].push(&패키지주소); => push 함수를 이용한다
	return;
}

void add(int pid, int area, int price)
{
	Package n_pack;
	n_pack.id = pid;
	n_pack.area = area;
	n_pack.price = price;
	n_pack.userId = 0;

	int row = pid % HASH;
	int boundary = pId[row];
	Package* curr = PACKAGE[row];
	Package* tmp;
	if (boundary == 0) {
		PACKAGE[row] = &n_pack;
	}
	else {
		for (register int i = 0; i < boundary; i++) {
			if (curr->id > n_pack.id) break;
			tmp = curr;
			curr = curr->next;
		}
	}
	tmp->next = &n_pack;
	n_pack.next = curr;
	pId[row]++;
	return;
}

void reserve(int uid, int pid)
{

}

int recommend(int uid)
{
	return 0;
}



// 고려사항