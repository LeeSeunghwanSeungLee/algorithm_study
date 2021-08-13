#define WAIT 0
#define CONFLICT 1
#define EDIT 2

int onlineUser[1001][10001];
int onlineUserCnt[1001];

int Width;

struct User{
    int state;
    int row, colstart, colend, editLength;
}user[10001];

int lineWidth[10001];

void Init(int width, int length, char str[]){
    Width = width;
    for(register int i = 0; i <= 10000; i++) user[i].state = WAIT;

    for(register int i = 0; i <= 1000; i++){
        lineWidth[i] = 0;
        onlineUserCnt[i] = 0;

    }
    int nowRow = 0;
    for(register int i = 0; i < length; i++){
        if(str[i] == '\n'){
            nowRow++;
            continue;
        }
        lineWidth[nowRow]++;
    }
}

void Edit(int id, int row, int col){
    user[id].editLength = 0;
    int realRow =0, realCol = 0;
    user[id].state = EDIT;

    // setting real position from table
    for(register int i = 0; i < row; i++){
        if(lineWidth[realRow] <= realCol + Width){
            realRow++;
            realCol = 0;
        }
        else{
            realCol += Width;
        }
    }

    realCol += col;

    user[id].row = realRow;
    user[id].colstart = realCol;
    user[id].colend = realCol;

    onlineUser[realRow][onlineUserCnt[realRow]] = id;
    onlineUserCnt[realRow]++;
}

void Add(int id, int length, char str[]){
    user[id].colend = user[id].colstart;
    user[id].editLength = length;
}
void Delete(int id, int length){
    user[id].colend = user[id].colstart + length - 1;
    user[id].editLength = -length;
}
void Substitute(int id, int length, char str[]){
    user[id].colend = user[id].colstart + length - 1;
    user[id].editLength = 0;
}

int EditDone(int id){
    if(user[id].state != EDIT){
        user[id].state = WAIT;
        return 0;
    }

    int row = user[id].row;
    
    int newOnLine[10001];
    int newOnlineCnt = 0;

    for(register int i = 0; i < onlineUserCnt[row]; i++){
        int other = onlineUser[row][i];
        if(other == id) continue;
        if(user[other].state == CONFLICT) continue;

        if(user[other].colend < user[id].colstart)
            newOnLine[newOnlineCnt++] = other;

        else if(user[other].colstart > user[id].colend){
            newOnLine[newOnlineCnt++] = other;

            user[other].colstart += user[id].editLength;
            user[other].colend += user[id].editLength;
        }

        else user[other].state = CONFLICT;        
    }

    lineWidth[row] += user[id].editLength;
    user[id].state = WAIT;

    for(register int i = 0; i < newOnlineCnt; i++){
        onlineUser[row][i] = newOnLine[i];
    }
    onlineUserCnt[row] = newOnlineCnt;

    return 1;
}