#include <cstdio>
int main() {
    int n, l, ans = 0, i, j, c;
    short a[200][100];
    scanf("%d %d", &n, &l);
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            scanf("%hd", &a[i][j]);
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            a[i + n][j] = a[j][i];
    for (i=0; i<n * 2; i++) {
        c = 1;
        for (j=0; j<n - 1; j++) {
            if (a[i][j] == a[i][j + 1]) c++;
            else if (a[i][j] + 1 == a[i][j + 1] && c >= l) c = 1;
            else if (a[i][j] - 1 == a[i][j + 1] && c >= 0) c = -l + 1;
            else break;
        }
        if (j == n - 1 && c >= 0) ans++;
    }
    printf("%d", ans);
    return 0;
}