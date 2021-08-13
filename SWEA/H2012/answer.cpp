#define WAIT 0
#define CONFLICT 1
#define EDIT 2
 
int online[1001][10001];
int onlineCnt[1001];
 
int Width;
 
struct User {
    int state;
    int row;
    int colstart;
    int colend;
    int editLength;
} user[10001];
 
int lineWidth[10001];
 
void Init(int width, int length, char str[])
{
    Width = width;
    for (int i = 0; i <= 10000; i++) {
        user[i].state = WAIT;
    }
    for (int i = 0; i <= 1000; i++) {
        lineWidth[i] = 0;
        onlineCnt[i] = 0;
    }
    int nowRow = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            nowRow++;
            continue;
        }
        lineWidth[nowRow]++;
    }
}
 
void Edit(int id, int row, int col)
{
    user[id].editLength = 0;
    int realRow = 0, realCol = 0;
    user[id].state = EDIT;
 
    for (int i = 0; i < row; i++) {
        if (lineWidth[realRow] <= realCol + Width) {
            realRow++;
            realCol = 0;
        }
        else {
            realCol += Width;
        }
    }
 
    realCol += col;
 
    user[id].row = realRow;
    user[id].colstart = realCol;
    user[id].colend = realCol;
 
    online[realRow][onlineCnt[realRow]] = id;
    onlineCnt[realRow]++;
}
 
void Add(int id, int length, char str[]) {
    user[id].colend = user[id].colstart;
    user[id].editLength = length;
}
void Delete(int id, int length) {
    user[id].colend = user[id].colstart + length - 1;
    user[id].editLength = -length;
}
void Substitute(int id, int length, char str[]) {
    user[id].colend = user[id].colstart + length - 1;
    user[id].editLength = 0;
}
 
int EditDone(int id)
{
    if (user[id].state != EDIT) {
        user[id].state = WAIT;
        return 0;
    }
 
    int row = user[id].row;
 
    int newOnline[10001];
    int newOnlineCnt = 0;
 
    for (int i = 0; i < onlineCnt[row]; i++) {
        int otherUser = online[row][i];
        if (otherUser == id) continue;
        if (user[otherUser].state == CONFLICT) continue;
 
        if (user[otherUser].colend < user[id].colstart) {
 
            newOnline[newOnlineCnt] = otherUser;
            newOnlineCnt++;
 
        }
        else if (user[id].colend < user[otherUser].colstart) {
 
            newOnline[newOnlineCnt] = otherUser;
            newOnlineCnt++;
 
            user[otherUser].colstart += user[id].editLength;
            user[otherUser].colend += user[id].editLength;
        }
        else {
            user[otherUser].state = CONFLICT;
        }
    }
 
    lineWidth[row] += user[id].editLength;
    user[id].state = WAIT;
 
    for (int i = 0; i < newOnlineCnt; i++) {
        online[row][i] = newOnline[i];
    }
    onlineCnt[row] = newOnlineCnt;
 
    return 1;
}