#include <stdio.h>

typedef struct {
    float p;     
    float w;     
    float pw;    // (p/w)
} Item;

void insertionSort(Item a[], int n);
float fknpsk(Item a[], int n, float m);

int main() {
    int n;
    float m;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item a[n];
    int i;
    for (i = 0; i < n; ++i) {
        printf("Enter profit and weight of item %d: ", i + 1);
        scanf("%f %f", &a[i].p, &a[i].w);
        a[i].pw = a[i].p / a[i].w;  
    }

    printf("Enter max capacity: ");
    scanf("%f", &m);

    float maxProfit = fknpsk(a, n, m);

    printf("Maximum Profit: %.4f\n", maxProfit);

    return 0;
}

void insertionSort(Item a[], int n) {
    int i, j;
    Item key;

    for (i = 1; i < n; ++i) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j].pw < key.pw) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

float fknpsk(Item a[], int n, float m) {
    float res = 0.0;
    insertionSort(a, n);
    int i;
    for (i = 0; i < n; ++i) {
        if (m >= a[i].w) {
            res += a[i].p;
            m -= a[i].w;
        } else {
            res += a[i].pw * m;  
            break;
        }
    }

    return res;
}
