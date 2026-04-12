#include <stdio.h>
#include <math.h>

#define PI 3.14

typedef struct
{
    double r;
    double i;
} Complex;

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
    c.r = a.r - b.r;
    c.i = a.i - b.i;
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

    Complex X[N / 2], Y[N / 2];
    Complex B[N / 2], C[N / 2];

    for (int i = 0; i < N / 2; i++)
    {
        X[i] = S[2 * i];
        Y[i] = S[2 * i + 1];
    }

    fft(X, N / 2, B);
    fft(Y, N / 2, C);

    for (int r = 0; r < N / 2; r++)
    {
        Complex w;

        w.r = cos(-2 * PI * r / N);
        w.i = sin(-2 * PI * r / N);

        Complex term = mul(w, C[r]);

        A[r] = add(B[r], term);
        A[r + N / 2] = sub(B[r], term);
    }
}

void ifft(Complex A[], int N, Complex S[])
{
    if (N == 1)
    {
        S[0] = A[0];
        return;
    }

    Complex X[N / 2], Y[N / 2];
    Complex B[N / 2], C[N / 2];

    for (int i = 0; i < N / 2; i++)
    {
        X[i] = A[2 * i];
        Y[i] = A[2 * i + 1];
    }

    ifft(X, N / 2, B);
    ifft(Y, N / 2, C);

    for (int r = 0; r < N / 2; r++)
    {
        Complex w;

        w.r = cos(2 * PI * r / N);
        w.i = sin(2 * PI * r / N);

        Complex term = mul(w, C[r]);

        S[r] = add(B[r], term);
        S[r + N / 2] = sub(B[r], term);
    }
}

int main()
{
    int n, m;

    printf("Enter highest degree of first poly: ");
    scanf("%d", &n);

    printf("Enter highest degree of second poly: ");
    scanf("%d", &m);

    int size = 1;

    while (size <= n + m)
        size *= 2; // for padding

    Complex P[size];   // coeff of poly 1
    Complex Q[size];   // coeff of poly 2
    Complex FP[size];  // FFT of poly 1
    Complex FQ[size];  // FFT of poly 2
    Complex FR[size];  // resultant
    Complex res[size]; // final ans after ifft

    for (int i = 0; i < size; i++)
    {
        P[i].r = P[i].i = 0;
        Q[i].r = Q[i].i = 0;
    }

    printf("Enter coefficients of first poly:\n");

    for (int i = 0; i <= n; i++)
        scanf("%lf", &P[i].r);

    printf("Enter coefficients of second poly:\n");

    for (int i = 0; i <= m; i++)
        scanf("%lf", &Q[i].r);

    fft(P, size, FP);
    fft(Q, size, FQ);

    for (int i = 0; i < size; i++)
        FR[i] = mul(FP[i], FQ[i]);

    ifft(FR, size, res);

    for (int i = 0; i < size; i++)
    {
        res[i].r /= size;
        res[i].i /= size;
    }

    printf("\nResultant poly coeffs:\n");

    for (int i = 0; i <= n + m; i++)
        printf("%.0lf ", res[i].r);

    printf("\n");

    return 0;
}