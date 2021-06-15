#define ALPHABET_SIZE 27 // * == 27
#define STR_LENGTH 7 // '/0' 포함
#define STAR_INDEX 26


#define CHAR_TO_INDEX(c) (c == '*' ? STAR_INDEX : c - 'a')
#define INDEX_TO_CHAR(i) (i == 27 ? '*' : i + 'a')

struct NODE {
    char c;
    NODE* alphabet[ALPHABET_SIZE];
    int leafCount;
};

NODE node[1000000];
int nodeCount;
NODE head;

NODE* alloc(char c) // 나랑 동일
{
    for (register int i = 0; i < ALPHABET_SIZE; ++i) {
        node[nodeCount].alphabet[i] = 0;
    }
    node[nodeCount].leafCount = 0;
    node[nodeCount].c = c;

    return &node[nodeCount++];
}

void init(void)
{
    for (register int i = 0; i < ALPHABET_SIZE; ++i) {
        head.alphabet[i] = 0;
    }
    nodeCount = 0;
}

void update(NODE* currNode, char str[], int star, int count)
{
    if (star) {
        if (currNode->alphabet[STAR_INDEX] == 0) {
            currNode->alphabet[STAR_INDEX] = alloc('*');
        }
        int i = -1;

        do {
            i++;
            update(currNode->alphabet[STAR_INDEX], str + i, 0, count);
        } while (*(str + i));
    }

    if (*str == 0) {
        currNode->leafCount += count;
        return;
    }

    int index = CHAR_TO_INDEX(*str);

    if (currNode->alphabet[index] == 0) {
        currNode->alphabet[index] = alloc(*str);
    }
    update(currNode->alphabet[index], str + 1, star, count);
}

void addWord(char str[])
{
    NODE* currNode = &head;

    update(currNode, str, 1, 1); // @params : (노드, 문자, star, count) 
}

char find_string[STR_LENGTH];
int str_index;

int remove(NODE* currNode, char str[])
{
    int count = 0;
    find_string[str_index] = 0;

    if (*str >= 'a' && *str <= 'z') {
        find_string[str_index] = 0;
        int index = CHAR_TO_INDEX(*str);
        if (currNode->alphabet[index]) {
            find_string[str_index++] = *str;
            count += remove(currNode->alphabet[index], str + 1);
            str_index--;
        }
    }
    else if (*str == 0) {
        find_string[str_index] = *str;
        count += currNode->leafCount;
        update(&head, find_string, 1, -count);
    }
    else if (*str == '*') {
        count += remove(currNode, str + 1);

        for (register int i = 0; i < 26; ++i) {
            if (currNode->alphabet[i]) {
                find_string[str_index++] = INDEX_TO_CHAR(i);
                count += remove(currNode->alphabet[i], str);
                str_index--;
            }
        }
    }

    return count;
}

int removeWord(char str[])
{
    NODE* currNode = &head;
    str_index = 0;

    return remove(currNode, str);
}

int get(NODE* currNode, char str[])
{
    int index = CHAR_TO_INDEX(*str);
    int count = 0;

    if (*str == 0) {
        return currNode->leafCount;
    }

    if (currNode->alphabet[index]) {
        count += get(currNode->alphabet[index], str + 1);
    }

    return count;
}

int searchWord(char str[])
{
    NODE* currNode = &head;
    return get(currNode, str);
}