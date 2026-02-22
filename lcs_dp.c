#include <stdio.h>
#include <string.h>

// function to get max of two numbers
int max(int a, int b) {
    return (a >= b) ? a : b;
}

// LCS function
void LCS(char X[], char Y[]) {
    int n = strlen(X);
    int m = strlen(Y);

    // DP table
    int L[n + 1][m + 1];

    int i, j;

    // Initialization (base case)
    for (i = 0; i <= n; i++)
        L[i][0] = 0;
    for (j = 0; j <= m; j++)
        L[0][j] = 0;

    // Fill DP table
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) {
                // Match → diagonal + 1
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                // Mismatch → max of top or left
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // Print DP Table (for understanding)
    printf("\nDP Table:\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= m; j++) {
            printf("%d ", L[i][j]);
        }
        printf("\n");
    }

    // Length of LCS
    int length = L[n][m];
    printf("\nLength of LCS = %d\n", length);

    // Backtracking to find LCS string
    char lcs[length + 1];
    lcs[length] = '\0';  // null terminate

    i = n;
    j = m;
    int index = length - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            // Character is part of LCS
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1]) {
            // Move up
            i--;
        }
        else {
            // Move left
            j--;
        }
    }

    printf("LCS String = %s\n", lcs);
}

int main() {
    char X[100], Y[100];

    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    LCS(X, Y);

    return 0;
}