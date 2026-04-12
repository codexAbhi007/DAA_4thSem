#include <stdio.h>
#include <math.h>
#define PI 3.14
typedef struct
{
    double r;
    double i;
} Complex;

Complex add(Complex a, Complex b);
Complex sub(Complex a, Complex b);
Complex mul(Complex a, Complex b);
void fft(Complex S[], int N, Complex A[]);
void printFFT(Complex A[], int N);

int main()
{
    int N;
    printf("Enter no of sampels: ");
    scanf("%d", &N);

    Complex S[N], A[N];

    printf("Enter real and imag parts:\n");

    for (int i = 0; i < N; i++)
    {
        printf("S[%d]= ", i);
        scanf("%lf %lf",&S[i].r,&S[i].i);
    }
    fft(S, N, A);
    printf("\nFFT Coeffs output:\n");
    printFFT(A, N);
    return 0;
}

Complex add(Complex a, Complex b)
{
    Complex c;
    c.r = a.r + b.r;
    c.i = a.i + b.i;
    return c;
}

Complex sub(Complex a, Complex b)
{
    Complex c;
    c.r = a.r -b.r;
    c.i = a.i -b.i;
    return c;
}

Complex mul(Complex a, Complex b)
{
    Complex c;
    c.r = a.r * b.r - a.i * b.i;
    c.i = a.r * b.i + a.i * b.r;
    return c;
}

void fft(Complex S[], int N, Complex A[])
{
    if (N == 1)
    {
        A[0] = S[0];
        return;
    }

    Complex X[N/ 2], Y[N /2];
    Complex B[N/2], C[N/ 2];

    for (int i=0; i < N/ 2; i++)
    {
        X[i] = S[2*i];
        Y[i] = S[2*i+ 1];
    }

    fft(X, N/2, B);
    fft(Y, N/2, C);

    for (int r = 0; r < N / 2; r++)
    {
        Complex w;
        w.r = cos(-2*PI * r/ N);
        w.i = sin(-2 *PI * r /N);
        Complex term = mul(w, C[r]);
        A[r]= add(B[r], term);
        A[r + N/2]= sub(B[r], term);
    }
}

void printFFT(Complex A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        if (A[i].i >= 0) printf("A[%d] = %.2lf + %.2lf i\n", i, A[i].r, A[i].i);
        else printf("A[%d] = %.2lf - %.2lf i\n", i, A[i].r,-A[i].i);    
    }
}