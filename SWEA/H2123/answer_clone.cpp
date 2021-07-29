#define MAXRAIL 100001
#define swap(a, b) {int c=a; a=b; b=c;}
 
struct RAIL {
    RAIL* prev, * next;
    int x, y;
    int dir;
    int dirPrev;
}rail[MAXRAIL];
int rIdx = 0;
RAIL platform;
 
RAIL* front;
RAIL* rear;
 
// 0 오른쪽 1 아래 2 왼쪽 3 위
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
int nextDir[4][3] = { {3,0,1}, {0,1,2}, {1,2,3}, {2,3,0} };
 
int n;
 
void init(int N) {
    n = N;
    rIdx = 0;
    platform.x = platform.y = n;
    platform.next = platform.prev = 0;
    platform.dir = 0;
    platform.dirPrev = 2;
    front = rear = &platform;
}
 
// ~50,000
void addRail(int mFront, int mDirection) {
    if (mFront == 1) {
        int x = front->x;
        int y = front->y;
        int dir = front->dir;
        rail[rIdx] = { 0, 0, x + dx[dir], y + dy[dir], nextDir[dir][mDirection], (dir + 2) % 4 };
        RAIL* p = &rail[rIdx++];
        front->next = p;
        p->prev = front;
        front = p;
    }
    else {
        int x = rear->x;
        int y = rear->y;
        int dir = rear->dir;
        if (rear == &platform) {
            dir = 2;
        }
        rail[rIdx] = { 0, 0, x + dx[dir], y + dy[dir], nextDir[dir][mDirection], (dir + 2) % 4 };
        RAIL* p = &rail[rIdx++];
        rear->prev = p;
        p->next = rear;
        rear = p;
    }
}
 
bool isCircle() {
    bool flag = false;
    int nx = front->x + dx[front->dir];
    int ny = front->y + dy[front->dir];
    int dir = rear->dir;
    if (rear == &platform) {
        dir = 2;
    }
    if (nx == rear->x && ny == rear->y && front->dir == ((dir + 2) % 4)) {
        front->next = rear;
        rear->prev = front;
        flag = true;
    }
    return flag;
}
 
// ~5,000
int delRail(int mRow, int mCol) {
    // front 부터 찾기
    bool isFront = true;
    bool find = false;
    RAIL* cur = front;
    while (cur != &platform) {
        if (cur->x == mRow && cur->y == mCol) {
            find = true;
            break;
        }
        cur = cur->prev;
    }
    // rear 찾기
    if (!find) {
        isFront = false;
        cur = rear;
        while (cur != &platform) {
            if (cur->x == mRow && cur->y == mCol) {
                find = true;
                break;
            }
            cur = cur->next;
        }
    }
    if (!find) {
        return 0;
    }
 
    // mRow, mCol인 레일 찾았음.
 
    // 순환인 경우
    if (isCircle()) {
        if (isFront) {
            while (front != cur) {
                swap(front->dir, front->dirPrev);
                front = front->prev;
            }
        }
        else {
            while (rear != cur) {
                swap(rear->dir, rear->dirPrev);
                rear = rear->next;
            }
        }
        front = cur->prev;
        rear = cur->next;
        front->next = 0;
        rear->prev = 0;
        return 1;
    }
 
    // 순환이 아니면 front/rear 중 하나 지우기
    int cnt = 0;
    if (isFront) {
        front = cur->prev;
        for (; cur != 0; cur = cur->next) {
            cnt++;
        }
        front->next = 0;
    }
    else {
        rear = cur->next;
        for (; cur != 0; cur = cur->prev) {
            cnt++;
        }
        rear->prev = 0;
    }
    return cnt;
}