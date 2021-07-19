#define MAX_LEN 10007
////////////////////////////////////////////////////////
struct fileSystem{
    int id;
    int fileSize;
    int infectedSize;
    fileSystem *next, *prev;
    int parentHashID;
}poolFile[MAX_LEN];
int fileID;
fileSystem* alloc_file(){
    poolFile[fileID].next = poolFile[fileID].prev = 0;
    return &poolFile[fileID++];
}
////////////////////////////////////////////////////////
struct folderSystem{
    int id;
    int totalSize;
    folderSystem *next, *prev, *parent, *childFolder;
    bool isInfected;
    fileSystem* childFile;
}poolFolder[MAX_LEN + 1];
int folderID;
folderSystem* alloc_folder(){
    poolFolder[folderID].next = poolFolder[folderID].prev = poolFolder[folderID].parent = poolFolder[folderID].childFolder = 0;
    poolFolder[folderID].childFile = 0;
    return &poolFolder[folderID++]; 
}
folderSystem* root;
////////////////////////////////////////////////////////
struct hashTbl{
    int define; //0 : folder, 1 : file;
    int id;
}HASHTABLE[MAX_LEN];

int addHash(int id){
    int h = id % MAX_LEN;
    while(HASHTABLE[h].define != -1){
        h = (h + 1) % MAX_LEN;
    }
    return h;
}
int getHash(int id){
    int h = id % MAX_LEN;
    int curr = MAX_LEN;
    while(HASHTABLE[h].define != -1 && curr != 0){
        if(HASHTABLE[h].define == 0 && poolFolder[HASHTABLE[h].id].id == id) return h;
        else if(HASHTABLE[h].define == 1 && poolFile[HASHTABLE[h].id].id == id) return h;
        h = (h + 1) % MAX_LEN;
    }
    return -1; // 없다는 뜻
}
////////////////////////////////////////////////////////
void init() {
    fileID = 0;
    folderID = 0;
    for(register int i = 0; i < MAX_LEN; i++) HASHTABLE[i].define = -1;

    root = alloc_folder();
    root -> id = 10000;
    root -> totalSize = 0;
    root -> isInfected = 0;
    int h = addHash(root -> id);
    HASHTABLE[h].define = 0;
    HASHTABLE[h].id = folderID - 1;
}

int cmdAdd(int newID, int pID, int fileSize) {
    int res = 0;
    if(fileSize == 0){
        folderSystem* newFold = alloc_folder();
        newFold -> id = newID;
        newFold -> totalSize = 0;
        newFold -> isInfected = 0;
        int h = addHash(newFold -> id);
        HASHTABLE[h].define = 0;
        HASHTABLE[h].id = folderID - 1;

        int tmpH = getHash(pID);
        int idx = HASHTABLE[tmpH].id;
        folderSystem* parentFold = &poolFolder[idx];
        res = parentFold -> totalSize;

        newFold -> next = parentFold -> childFolder;
        //newFold -> prev = 0;
        if(parentFold -> childFolder != 0){
            parentFold -> childFolder -> prev = newFold;
        }
        parentFold -> childFolder = newFold;
    }
    else{
        fileSystem* newFile = alloc_file();
        newFile -> id = newID;
        newFile -> fileSize = fileSize;
        newFile -> infectedSize = 0;

        int h = addHash(newFile -> id);
        HASHTABLE[h].define = 1;
        HASHTABLE[h].id = fileID - 1;

        int ph = getHash(pID);
        int idx = HASHTABLE[ph].id;
        newFile -> parentHashID = idx;

        folderSystem* parentFold = &poolFolder[idx];

        newFile -> next = parentFold -> childFile;
        // newFile -> prev = 0;
        if(parentFold -> childFile != 0){
            parentFold -> childFile -> prev = newFile;
        }
        parentFold -> childFile = newFile;
        parentFold -> totalSize += fileSize;

        res = parentFold -> totalSize;
    }
	return res;
}

int cmdMove(int tID, int pID) {
    int h = getHash(pID);
    int idx = HASHTABLE[h].id;
    folderSystem* parent = &poolFolder[idx];

    int th = getHash(tID);
    if(poolFile[th].id == tID){ // 파일
        
    }
    else{

    }
	return -1;
}

int cmdInfect(int tID) {
	return -1;
}

int cmdRecover(int tID) {
	return -1;
}

int cmdRemove(int tID) {
	return -1;
}

