#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

#define no_of_trials 1000000

void convolution_int(int m, int n, int A[m], int B[n], int C[m + n - 1])
{
    for (int i = 0; i < m + n - 1; i++)
    {
        C[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i + j] = C[i + j] + A[i] * B[j];
        }
    }
}

void print_vector(int size, int C[size])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", C[i]);
    }
    printf("\n");
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int A[m], B[n], C[m + n - 1];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &B[i]);
    }
    double average_time_int = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start_int, end_int;
        clock_gettime(CLOCK_MONOTONIC, &start_int);
        convolution_int(m, n, A, B, C);
        clock_gettime(CLOCK_MONOTONIC, &end_int);
        double elapsed = (end_int.tv_sec - start_int.tv_sec) + (end_int.tv_nsec - start_int.tv_nsec) / 1e9;
        average_time_int = average_time_int + elapsed;
    }
    average_time_int = average_time_int / no_of_trials;
    // print_vector(m, A);
    // print_vector(n, B);
    print_vector(m + n - 1, C);
    printf("Average elapsed time for int: %.9f seconds\n", average_time_int);
}