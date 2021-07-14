#define MAX_NUM 100000
#define MAX_TEAM 5
#define MAX_SCORE 5
 
struct sol_t
{
    int id;
    int team;
    sol_t* next;
    sol_t* prev;
};
sol_t soldier[MAX_NUM + 1];
 
struct team_t
{
    sol_t head;
    sol_t tail;
};
 
team_t team[MAX_TEAM + 1][MAX_SCORE + 1];
 
void initList(sol_t* prev, sol_t* next)
{
    prev->next = next;
    next->prev = prev;
}
 
void linkList(sol_t* prev, sol_t* next)
{
    prev->next = next;
    next->prev = prev;
}
 
void insertList(sol_t* tail, sol_t* node)
{
    linkList(tail->prev, node);
    linkList(node, tail);
}
 
void deleteList(sol_t* node)
{
    linkList(node->prev, node->next);
}
void init()
{
    for (register int i = 1; i <= MAX_TEAM; i++)
        for (register int j = 1; j <= MAX_SCORE; j++)
            initList(&team[i][j].head, &team[i][j].tail);
}
 
void hire(int mID, int mTeam, int mScore)
{
    soldier[mID] = { mID, mTeam, 0, 0 };
    insertList(&team[mTeam][mScore].tail, &soldier[mID]);
}
 
void fire(int mID)
{
    sol_t* cur = &soldier[mID];
    deleteList(cur);
}
 
void updateSoldier(int mID, int mScore)
{
    sol_t* cur = &soldier[mID];
    deleteList(cur);
    insertList(&team[cur->team][mScore].tail, cur);
}
 
void moveList(team_t* from, team_t* to)
{
    linkList(to->tail.prev, from->head.next);
    linkList(from->tail.prev, &to->tail);
    linkList(&from->head, &from->tail);
}
 
void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {
        for (register int i = 4; i > 0; i--)
        {
            if (team[mTeam][i].head.next == &team[mTeam][i].tail) continue;
            int s = (i + mChangeScore) > 5 ? 5 : (i + mChangeScore);
            moveList(&team[mTeam][i], &team[mTeam][s]);
        }
    }
    else if (mChangeScore < 0)
    {
        for (register int i = 2; i <= MAX_TEAM; i++)
        {
            if (team[mTeam][i].head.next == &team[mTeam][i].tail) continue;
            int s = (i + mChangeScore) < 1 ? 1 : (i + mChangeScore);
            moveList(&team[mTeam][i], &team[mTeam][s]);
        }
    }
}
 
int bestSoldier(int mTeam)
{
    register int i = 0;
    for (i = MAX_TEAM; i > 0; i--)
        if (team[mTeam][i].head.next != &team[mTeam][i].tail) break;;
 
    int id = 0;
    for (register sol_t* cur = team[mTeam][i].head.next; cur != &team[mTeam][i].tail; cur = cur->next)
        if (cur->id > id) id = cur->id;
    return id;
}