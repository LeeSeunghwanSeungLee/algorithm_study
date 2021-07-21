#define MAX_LEN 10007

struct Node {
	int id;
	int fileSize;
	int fileNum;
	int originFileSize;
	bool isFile;
	bool isInfected;
	int folderSize;
	Node* next, * prev, * parent, * child;
}poolNode[MAX_LEN];
Node* root;
Node* addHash(int id) {
	int h = id % MAX_LEN;
	while (poolNode[h].id != -1) {
		if (poolNode[h].id == id) return 0;
		h = (h + 1) % MAX_LEN;
	}
	poolNode[h].id = id;
	return &poolNode[h];
}
Node* getHash(int id) {
	int h = id % MAX_LEN;
	int curr = MAX_LEN;
	while (poolNode[h].id != -1 && curr--) {
		if (poolNode[h].id == id) return &poolNode[h];
		h = (h + 1) % MAX_LEN;
	}
	return 0;
}
void init() {
	for (int i = 0; i < MAX_LEN; i++) {
		poolNode[i].id = -1;
	}
	root = addHash(10000); // Add Root & initialize
	root->parent = root->child = root->prev = root->next = 0;
	root->fileSize = 0;
	root->fileNum = 0;
	root->originFileSize = 0;
	root->isFile = false;
	root->isInfected = 0;
	root->folderSize = 0;
}
int cmdAdd(int newID, int pID, int fileSize) {
	Node* nNode = addHash(newID); // 신규 노드를 추가한다.
	nNode->parent = nNode->child = nNode->prev = nNode->next = 0;
	nNode->fileNum = 0;
	nNode->isInfected = 0;
	nNode->folderSize = 0;
	if (fileSize == 0) {
        nNode->isFile = false;
        nNode -> fileSize = 0;
        nNode -> originFileSize = 0;
    }
	else {
        nNode->isFile = true;
        nNode->fileSize = fileSize;
        nNode->originFileSize = fileSize;
    }

	Node* pNode = getHash(pID); // 부모 노드를 가져온다.

	// 서로 연결한다. => 형제 노드와 연결시켜줘야함 (좌측에 배치한다. 단 다음 형제가 있는지 없는지를 확인해야 되는 코너 케이스가 존재한다.) => root 까지 파일 수와 폴드 수를 추가해줘야함.
	nNode->parent = pNode;
	nNode->next = pNode->child;
	if (pNode->child) pNode->child->prev = nNode;
	pNode->child = nNode;
	// 부모노드의 파일 크기의 합을 반환한다.
	if (fileSize == 0) return pNode->folderSize;

	Node* curr = pNode;
	while (curr) {
		curr->fileNum++;
		curr->folderSize += fileSize;
		curr = curr->parent;
	}
	
	return pNode->folderSize;
}
int cmdMove(int tID, int pID) {
	// 타겟 노드 와 현재 부모노드를 가져온다.
	Node* tNode = getHash(tID);
	Node* preParent = tNode->parent;

	// 타겟노드의 형제 노드를 제거한다 ( 좌측, 우측, 중간 순으로 비교해야함 )
	if (tNode->prev == 0) {
		preParent->child = tNode->next;
	}
	else if (tNode->next == 0) {
		tNode-> prev -> next = 0;
	}
	else {
		tNode->next->prev = tNode->prev;
		tNode->prev->next = tNode->next;
	}
	tNode->prev = tNode->next = 0;
	
	// 부모노드의 파일 수와 폴드 수에서 타겟 노드만큼 제외한다 ( root 까지 제거해야함 )
	Node* curr = preParent;
	int num = (tNode->isFile) ? 1 : tNode->fileNum;
	int size = (tNode->isFile) ? tNode->fileSize : tNode->folderSize;
	while (curr) {
		curr->folderSize -= size;
		curr->fileNum -= num;
		curr = curr->parent;
	}
	// 이동 타겟 노드와 연결한다 => 형제 노드와 연결시켜줘야함 => root 까지 파일 수와 폴드 수를 추가해준다. // cmdAdd를 응용해서 사용하면 됨.
	Node* afterParent = getHash(pID);
	// 서로 연결한다. => 형제 노드와 연결시켜줘야함 (좌측에 배치한다. 단 다음 형제가 있는지 없는지를 확인해야 되는 코너 케이스가 존재한다.) => root 까지 파일 수와 폴드 수를 추가해줘야함.
	tNode->parent = afterParent;
	tNode->next = afterParent->child;
	if (afterParent->child) afterParent->child->prev = tNode;
	afterParent->child = tNode;
	
	curr = afterParent;
	while (curr) {
		curr->fileNum += num;
		curr->folderSize += size;
		curr = curr->parent;
	}
	return afterParent->folderSize;
}

void update(Node* target, Node* base, int addSize) {
	// 자손이 존재한다면 먼저 변경, base 는 cmdInfect 에서 tID에 해당할 것임
	target->isInfected = true;
	if (target->child != 0) update(target->child, base, addSize);
	// 자기 자신 변경
		// 이미 감염되어있는지 확인 그렇다면 fileSize 를 추가로 더하고 아니면 org_fileSize를 이용해야한다.
	int size = 0;
	if (target->isFile) {
		target->fileSize += addSize;
		size = addSize;
	}
	// 형제가 존재한다면 변경 base 는 cmdInfect 에서 tID에 해당할 것임
	if (target->next) update(target->next, base, addSize);
	// base 까지 업데이트한다.
	Node* curr = target->parent;
	while (size != 0 && curr != base->parent) {
		curr->folderSize += size;
		curr = curr->parent;
	}
}
void downDate(Node* target, Node* base, int *changeSize) {
	
    if (target->child) downDate(target->child, base, changeSize);
	// 형재가 존재하면 변경시킨다.
	if (target->next) downDate(target->next, base, changeSize);

    if(target -> isInfected = false || target -> isFile == false) return;
    // 자기 자신을 isInfeced = false; 로 변경한다
	target->isInfected = false;
	// 자기 자신의 fileSize = org_fileSize 를 반환한다.
	int size = 0;
	
    *changeSize += target->fileSize - target->originFileSize;
    size = target->fileSize - target->originFileSize;
    target->fileSize = target->originFileSize;
	
	// 자손이 존재하면 변경시킨다.
	

	Node* curr = target -> parent;
	if (size != 0 && curr != base->parent) {
		curr->folderSize -= size;
		curr = curr->parent;
	}
}
int cmdInfect(int tID) {
    if (root->fileNum == 0) return 0;

    // 루트에 접근해서 증가하는 파일 크기를 계산한다.
	int addSize = root->folderSize / root->fileNum;
	// 타겟 노드를 가져온다.
	Node* tNode = getHash(tID);
	// 업데이트 함수 실행
	int size;
	if (tNode->isFile) { // 파일 인경우
		tNode->isInfected = true;
		tNode->fileSize += addSize;
		size = addSize;
	}
	else if (tNode->child != 0) {// 폴더인 경우
		update(tNode->child, tNode, addSize);
		size = addSize * tNode->fileNum;
	}
	else { // 폴더인데 자식이 없는 경우
		return 0;
	}
	Node* curr = tNode->parent;
	while (curr) { // 타겟에서 자신이 변한 파일개수와 파일 용량을 계산해서 root까지 전달
		curr->folderSize += size;
		curr = curr->parent;
	}
	
	return (tNode -> isFile)? tNode -> fileSize : tNode -> folderSize;
}
int cmdRecover(int tID) {
	// 타겟 노드를 가져온다.
	Node* tNode = getHash(tID);
	// downDate(Node* target) 실행
	int size = 0;
	// 현재 노드의 사이즈를 original로 변경한다. 
	if (tNode->isFile) {
		tNode->isInfected = false;
		size = tNode->fileSize - tNode->originFileSize;
		tNode->fileSize = tNode->originFileSize;
	}
	else if (tNode->child != 0) {
		downDate(tNode->child, tNode, &size);
	}
	else {
		return 0;
	}
	// root까지 전달한다.
	Node* curr = tNode->parent;
	while (curr) {
		curr->folderSize -= size;
		curr = curr->parent;
	}
	// 타겟 노드의 파일 크기를 반환한다.
	return (tNode->isFile) ? tNode->fileSize : tNode->folderSize;
}
int cmdRemove(int tID) {
	// 타겟 노드를 가져온다.
	Node* tNode = getHash(tID);
    if (tNode == root) {
		int res;
		res = root->folderSize;
		root->parent = root->child = root->prev = root->next = 0;
		root->fileSize = 0;
		root->fileNum = 0;
		root->originFileSize = 0;
		root->isFile = false;
		root->isInfected = 0;
		root->folderSize = 0;
		return res;
	}
	// 부모와 연결을 끊는다.
	Node* pNode = tNode->parent;
	tNode->parent = 0;

	// 형제가 있다면 형제와 노드도 끊는다.
	if (tNode->prev == 0) {
		pNode->child = tNode->next;
	}
	else if (tNode->next == 0) {
		tNode->prev->next = 0;
	}
	else {
		tNode->next->prev = tNode->prev;
		tNode->prev->next = tNode->next;
	}
	
	// 현재 부모부터 root까지 파일 크기와 갯수를 수정한다.
	Node* curr = pNode;
	int num = (tNode->isFile) ? 1 : tNode->fileNum;
	int size = (tNode->isFile) ? tNode->fileSize : tNode->folderSize;
	while (curr) {
		curr->fileNum -= num;
		curr->folderSize -= size;
		curr = curr->parent;
	}
	// ret : 삭제되는 개체의 크기를 반환
	return size;
}