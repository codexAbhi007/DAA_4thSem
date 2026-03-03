#include <stdio.h>

int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

int knpsckDP(int p[], int w[], int m, int n, int x[])
{
    int V[n + 1][m + 1];

    int i, j;

    
    for (i = 0; i <= n; ++i)
        V[i][0] = 0;
    for (j = 0; j <= m; ++j)
        V[0][j] = 0;

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= m; ++j)
        {
            if (w[i - 1] <= j)
                V[i][j] = max(V[i - 1][j], V[i - 1][j - w[i - 1]] + p[i - 1]);
            else
                V[i][j] = V[i - 1][j];
        }
    }

    for (i = 0; i <= n; ++i)
    {
        for (j = 0; j <= m; ++j)
        {
            printf("%d ", V[i][j]);
        }
        printf("\n");
    }

    // Backtrack
    for (i = 0; i < n; ++i)
        x[i] = 0;
    i = n;
    j = m;

    while (i >= 0 && j <= m)
    {
        if (V[i - 1][j] != V[i][j])
        {
            x[i - 1] = 1;
            j = j - w[i - 1];
        }
        --i;
    }

    return V[n][m];
}

int main()
{
    int n;
    int m;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the max capacity of bag: ");
    scanf("%d", &m);

    int weights[n], profits[n];
    int x[n];

    int i;
    for (i = 0; i < n; ++i)
    {
        printf("Enter profit and weight of item %d: ", i + 1);
        scanf("%d %d", &profits[i], &weights[i]);
    }

    int max_profit = knpsckDP(profits, weights, m, n, x);

    printf("Max profit is: %d\n", max_profit);

    printf("Selected items: ");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", x[i]);
    }

    return 0;
}