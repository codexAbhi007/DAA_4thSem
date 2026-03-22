#include <stdio.h>
#define N 4

int col[N];
int ld[2 * N - 1];
int rd[2 * N - 1];
int board[N];
int c = 0;

void placeQueen(int i);
void printBoard();

int main()
{

    for (int k = 0; k < N; k++)
    {
        col[k] = 0;
        board[k] = 0;
    }

    for (int k = 0; k < 2 * N - 1; k++)
    {
        ld[k] = 0;
        rd[k] = 0;
    }

    placeQueen(0);
    return 0;
}

void placeQueen(int i)
{
    int j;

    for (j = 0; j < N; j++)
    {

        int ldIndex = i - j + (N - 1);
        int rdIndex = i + j;

        if (col[j] == 0 && ld[ldIndex] == 0 && rd[rdIndex] == 0)
        {

            board[i] = j;
            col[j] = 1;
            ld[ldIndex] = 1;
            rd[rdIndex] = 1;

            if (i == N - 1)
            {
                c++;
                printf("Solution %d:\n", c);
                printBoard();
                printf("\n");
            }
            
            else placeQueen(i + 1);
            

            col[j] = 0;
            ld[ldIndex] = 0;
            rd[rdIndex] = 0;
        }
    }
}

void printBoard()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}