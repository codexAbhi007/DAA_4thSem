#include <stdio.h>

typedef struct {
    int id;     
    int deadline; 
    int profit;  
} Job;

void insertionSort(Job a[], int n);
void jobScheduling(Job a[], int n);

int main() {
    int n;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job a[n];
    int i;
    for (i = 0; i < n; ++i) {
        printf("Enter id, deadline and profit of job %d: ", i + 1);
        scanf("%d %d %d", &a[i].id, &a[i].deadline, &a[i].profit);
    }

    jobScheduling(a, n);

    return 0;
}

void insertionSort(Job a[], int n) {
    int i, j;
    Job key;

    for (i = 1; i < n; ++i) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j].profit < key.profit) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void jobScheduling(Job a[], int n) {
    insertionSort(a, n);
    int result[n]; 
    int slot[n];   
    int i;

    for (i = 0; i < n; ++i)
        slot[i] = 0;

    for (i = 0; i < n; ++i) {
        int j;
        for (j = a[i].deadline - 1; j >= 0; --j) {
            if (slot[j] == 0) {
                result[j] = a[i].id;
                slot[j] = 1;
                break;
            }
        }
    }

    printf("Scheduled Jobs: ");
    for (i = 0; i < n; ++i) {
        if (slot[i])
            printf("%d ", result[i]);
    }
    printf("\n");
}