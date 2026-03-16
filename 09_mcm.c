#include <stdio.h>
#include <limits.h>
#define MAX 100

int m[MAX][MAX];
int split[MAX][MAX];

void mcm(int p[], int n)
{
    for (int i = 1; i <= n; ++i){
        for (int j = i; j <= n; ++j) {
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = INT_MAX;
        }
    }

    for (int l = 2; l <= n; ++l){
        for (int i = 1; i <= n+1 - l; ++i){
            int j = l-1 + i;

            for (int k = i; k < j; ++k){
                int cost = m[i][k] + m[k + 1][j]+p[i - 1]* p[k] * p[j];
                if (cost< m[i][j]){
                    m[i][j]= cost;
                    split[i][j]=k;
                }
            }
        }
    }
}

void printParenthesis(int l, int r){
    if(l == r){
        printf("%d",l);
        return;
    }

    printf("(");
    printParenthesis(l, split[l][r]);
    printParenthesis(split[l][r] + 1, r);
    printf(")");

}

int main()
{
    int p[] = {4, 2, 3, 5, 2};
    int n = 4;
    mcm(p, n);

    printf("Min cost:%d", m[1][n]);
    printf("\n");
    printParenthesis(1,n);

    return 0;
}