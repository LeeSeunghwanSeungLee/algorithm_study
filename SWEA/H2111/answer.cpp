// #include <stdbool.h>
// #include <stdio.h>
 
#define MAXU 100001
#define MAXN 50001
#define MAXG 10
 
typedef struct node {
    int id;
    int sec;
    int cnt;
    int idx;
} NODE;
NODE node[MAXN];
 
NODE* heap[MAXG][MAXN];
int size[MAXG];
 
int user[MAXU];
 
// void show(void) {
//     for (int i = 0; i < MAXG; i++) {
//         if (size[i] == 0) {
//             continue;
//         }
//         printf("  [sec %d] ", i);
//         for (int j = 1; j <= size[i]; j++) {
//             printf("(%d, %d, %d) ", heap[i][j]->id, heap[i][j]->cnt, heap[i][j]->idx);
//         }
//         printf("\n");
//     }
//     printf("\n");
 
//     for (int i = 0; i < MAXU; i++) {
//         if (user[i] == -1) {
//             continue;
//         }
//         printf("  [user %d] %d\n", i, user[i]);
//     }
 
//     printf("\n");
// }
 
void down(int sec, int st) {
    int idx = st;
    int maxsize = size[sec];
    int left, right, child;
 
    while (idx < maxsize) {
        left = idx * 2;
        right = idx * 2 + 1;
 
        if (left > maxsize) {
            break;
        }
 
        if (right > maxsize) {
            child = left;
        } else if (heap[sec][left]->cnt > heap[sec][right]->cnt ||
                   (heap[sec][left]->cnt == heap[sec][right]->cnt && heap[sec][left]->id > heap[sec][right]->id)) {
            child = left;
        } else {
            child = right;
        }
 
        if (heap[sec][idx]->cnt < heap[sec][child]->cnt ||
            (heap[sec][idx]->cnt == heap[sec][child]->cnt && heap[sec][idx]->id < heap[sec][child]->id)) {
            NODE* tmp;
            tmp = heap[sec][idx];
            heap[sec][idx]->idx = child;
            heap[sec][child]->idx = idx;
            heap[sec][idx] = heap[sec][child];
            heap[sec][child] = tmp;
            idx = child;
        } else {
            break;
        }
    }
}
 
void up(int sec, int idx) {
    int par;
 
    while (idx > 1) {
        par = idx / 2;
 
        if (heap[sec][idx]->cnt > heap[sec][par]->cnt ||
            (heap[sec][idx]->cnt == heap[sec][par]->cnt && heap[sec][idx]->id > heap[sec][par]->id)) {
            NODE* tmp;
            tmp = heap[sec][idx];
            heap[sec][idx]->idx = par;
            heap[sec][par]->idx = idx;
            heap[sec][idx] = heap[sec][par];
            heap[sec][par] = tmp;
            idx = par;
        } else {
            break;
        }
    }
}
 
void init() {
    for (int i = 0; i < MAXU; i++) {
        user[i] = -1;
    }
 
    for (int i = 0; i < MAXG; i++) {
        size[i] = 0;
    }
}
 
void addNews(int mSection, int mNewsId) {
    // printf("#%s sec %d, news %d\n", __func__, mSection, mNewsId);
 
    node[mNewsId].id = mNewsId;
    node[mNewsId].sec = mSection;
    node[mNewsId].cnt = 0;
 
    size[mSection]++;
    node[mNewsId].idx = size[mSection];
    heap[mSection][size[mSection]] = &node[mNewsId];
 
    up(mSection, size[mSection]);
 
    // show();
}
 
void eraseNews(int mNewsId) {
    // printf("#%s news %d\n", __func__, mNewsId);
 
    int sec, eidx, midx;
 
    sec = node[mNewsId].sec;
    eidx = node[mNewsId].idx;
    midx = size[sec];
 
    heap[sec][midx]->idx = eidx;
    heap[sec][eidx] = heap[sec][midx];
    size[sec]--;
    up(sec, eidx);
    down(sec, eidx);
 
    // show();
}
 
void readNews(int mUserId, int mNewsId) {
    // printf("#%s user %d, news %d\n", __func__, mUserId, mNewsId);
 
    int idx, sec;
 
    sec = node[mNewsId].sec;
    idx = node[mNewsId].idx;
    user[mUserId] = sec;
 
    node[mNewsId].cnt++;
    up(sec, idx);
 
    // show();
}
 
void changeSection(int mNewsId, int mSection) {
    // printf("#%s sec %d -> %d, news %d\n", __func__, node[mNewsId].sec, mSection, mNewsId);
 
    // printf("  @splice\n");
    eraseNews(mNewsId);
 
    node[mNewsId].sec = mSection;
    size[mSection]++;
    heap[mSection][size[mSection]] = &node[mNewsId];
    node[mNewsId].idx = size[mSection];
    up(mSection, size[mSection]);
 
    // printf("  @paste\n");
    // show();
}
 
int getList(int mUserId, int mList[]) {
    // printf("#%s user %d\n", __func__, mUserId);
 
    int sel, res;
    int tmp[2] = {0};
    int max[2];
    res = 0;
 
    bool flag = false;
 
    for (int i = 0; i < 10; i++) {
        max[0] = -1;
        max[1] = 0;
        flag = false;
 
        for (int j = 0; j < MAXG; j++) {
            if (size[j] == 0) {
                continue;
            }
            flag = true;
            tmp[0] = heap[j][1]->cnt;
            tmp[1] = heap[j][1]->id;
 
            if (j == user[mUserId]) {
                tmp[0] += 10;
            }
 
            if (max[0] < tmp[0] || (max[0] == tmp[0]) && max[1] < tmp[1]) {
                max[0] = tmp[0];
                max[1] = tmp[1];
                sel = j;
            }
        }
 
        if (!flag) {
            break;
        }
 
        mList[i] = heap[sel][1]->id;
        heap[sel][1] = heap[sel][size[sel]];
        size[sel]--;
        down(sel, 1);
        // printf("i: %d List: %d\n", i, mList[i]);
        // show();
        res++;
    }
 
    // printf("  @res: %d [ ", res);
    // for(int i = 0 ; i < res ; i++){
    //     printf("%d ", mList[i]);
    // }
    // printf("]\n");
 
    for (int i = 0; i < res; i++) {
        size[node[mList[i]].sec]++;
        heap[node[mList[i]].sec][size[node[mList[i]].sec]] = &node[mList[i]];
        node[mList[i]].idx = size[node[mList[i]].sec];
        up(node[mList[i]].sec, size[node[mList[i]].sec]);
    }
 
    // show();
 
    return res;
}