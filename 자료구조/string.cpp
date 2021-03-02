#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

#define MAX_STR_SIZE 1000000
#define MAX_STR_LEN 30

char stl_data1[MAX_STR_SIZE][MAX_STR_LEN];
char my_data1[MAX_STR_SIZE][MAX_STR_LEN];

char stl_data2[MAX_STR_SIZE][MAX_STR_LEN];
char my_data2[MAX_STR_SIZE][MAX_STR_LEN];

char stl_data3[MAX_STR_SIZE][MAX_STR_LEN];
char my_data3[MAX_STR_SIZE][MAX_STR_LEN];


int _strlen(char* str){ // simple string length function
    int len = 0;
    while(*(str++)) len++; // '\0' 이 나올때까지!!
    return len;
}

void _strcpy(char* temp, char* str){
    while(*(str)) *(temp++) = *(str++);
    *(temp) = '\n';
    return;
}

int _strcmp(char* str_1, char* str_2){ // str_1 이 크면 1, 같으면 0, str_2가 크면 -1
    while(*(str_1)){
        if(*(str_1) != *(str_2)){
            return *(str_1) > *(str_2)? 1: -1;
        }
        str_1++, str_2++;
    }

    return *(str_2) == '\0' ? 0 : -1;
}



char mc() { // make char
    return 'A' + (rand() % 24 + 1);
}

void MakeData(char(*str1)[30], char(*str2)[30]) { // Make Data (length : 24)
    char data[MAX_STR_LEN] = { 0 };
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        sprintf(data, "%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c %c%c%c%c%c%c%c",
            mc(), mc(), mc(), mc(), mc(), mc(), mc(), mc(), mc()
            , mc(), mc(), mc(), mc(), mc(), mc()
            , mc(), mc(), mc(), mc(), mc(), mc(), mc());
        strcpy(str1[i], data);
        strcpy(str2[i], data);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    time_t st, ed;

    /* STEP 1 STRCPY TEST*/
    MakeData(stl_data1, my_data1);
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strcpy(stl_data2[i], stl_data1[i]);
    }
    ed = clock();
    cout << "(stl)strcpy > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strcpy(my_data2[i], my_data1[i]);
    }
    ed = clock();
    cout << "(my)strcpy > " << (double)(ed - st) / CLOCKS_PER_SEC << endl << endl;


    /* STEP 2 STRCMP TEST*/
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strcmp(stl_data2[i], stl_data1[i]);
    }
    ed = clock();
    cout << "(stl)strcmp > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strcmp(my_data2[i], my_data1[i]);
    }
    ed = clock();
    cout << "(my)strcmp > " << (double)(ed - st) / CLOCKS_PER_SEC << endl << endl;

    /* STEP 3 STRLEN TEST*/
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strlen(stl_data2[i]);
    }
    ed = clock();
    cout << "(stl)strlen > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strlen(my_data2[i]);
    }
    ed = clock();
    cout << "(my)strlen > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    return 0;
}

