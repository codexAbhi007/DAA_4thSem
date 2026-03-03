#include <stdio.h>
void sum_of_subsets(int arr[], int n, int m, int x[], int k, int current_sum, int rem_sum);
int main()
{
    int arr[6] = {5, 10, 12, 13, 15, 18};
    int n = 6;
    int m = 30;
    int x[6] = {0, 0, 0, 0, 0, 0};
    int current_sum = 0;
    int rem_sum = 0;
    for (int i = 0; i < 6; ++i)
    {
        rem_sum = rem_sum + arr[i];
    }
    int k = 0;
    sum_of_subsets(arr, n, m, x, k, current_sum, rem_sum);

    return 0;
}

void sum_of_subsets(int arr[], int n, int m, int x[], int k, int current_sum, int rem_sum)
{
   
    if (current_sum == m)
    {
        for (int i = 0; i < n; ++i)
        {
            printf("%d ", x[i]);
        }
        printf("\n");
        return;
    }
     if (k >= n || current_sum + rem_sum < m)
        return;

    if (current_sum + arr[k] <= m)
    {
        x[k] = 1;
        sum_of_subsets(arr, n, m, x, k + 1, current_sum + arr[k], rem_sum - arr[k]);
    }
    x[k] = 0;
    sum_of_subsets(arr, n, m, x, k + 1, current_sum, rem_sum - arr[k]);
}