#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

#define no_of_trials 1000000
#define IU 4
#define IU_cycles 1
#define FPU 4
#define FPU_cycles 2

void convolution_double(int m, int n, int A[m], int B[n], int C[m + n - 1])
{
    for (int i = 0; i < m + n - 1; i++)
    {
        C[i] = 0;
    }

    double k = (double)FPU / (double)IU * (double)IU_cycles / (double)FPU_cycles;
    double index = m * k / (k + 1);
    int split_index = (int)index;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < split_index)
            {
                double prod = (double)A[i] * (double)B[j];
                C[i + j] = C[i + j] + (int)prod;
            }
            else
            {
                C[i + j] = C[i + j] + A[i] * B[j];
            }
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
    double average_time_double = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start_double, end_double;
        clock_gettime(CLOCK_MONOTONIC, &start_double);
        convolution_double(m, n, A, B, C);
        clock_gettime(CLOCK_MONOTONIC, &end_double);
        double elapsed = (end_double.tv_sec - start_double.tv_sec) + (end_double.tv_nsec - start_double.tv_nsec) / 1e9;
        average_time_double = average_time_double + elapsed;
    }
    average_time_double = average_time_double / no_of_trials;
    // print_vector(m, A);
    // print_vector(n, B);
    print_vector(m + n - 1, C);
    printf("Average elapsed time for double: %.9f seconds\n", average_time_double);
}