
void mstrcpy(char dst[], const char src[]) {
 int c = 0;
 while ((dst[c] = src[c]) != 0) ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
 int c = 0;
 while (str1[c] != 0 && str1[c] == str2[c]) ++c;
 return str1[c] - str2[c];
}

void init(int N, char mName[50][20], char mPrice[50][100], int mDuration[50]){

}

void priceChange(char mName[20], char mPrice[100]){

}

int daySurvivable(char mMoney[100])
{
    return 0;
}