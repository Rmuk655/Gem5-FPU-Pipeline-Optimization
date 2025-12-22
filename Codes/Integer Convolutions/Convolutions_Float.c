#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

#define no_of_trials 1000000
#define IU 4
#define IU_cycles 1
#define FPU 4
#define FPU_cycles 2

void convolution_float(int m, int n, int A[m], int B[n], int C[m + n - 1])
{
    for (int i = 0; i < m + n - 1; i++)
    {
        C[i] = 0;
    }

    float k = (float)FPU / (float)IU * (float)IU_cycles / (float)FPU_cycles;
    float index = m * k / (k + 1);
    int split_index = (int)index;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < split_index)
            {
                float prod = (float)A[i] * (float)B[j];
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
    double average_time_float = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start_float, end_float;
        clock_gettime(CLOCK_MONOTONIC, &start_float);
        convolution_float(m, n, A, B, C);
        clock_gettime(CLOCK_MONOTONIC, &end_float);
        double elapsed = (end_float.tv_sec - start_float.tv_sec) + (end_float.tv_nsec - start_float.tv_nsec) / 1e9;
        average_time_float = average_time_float + elapsed;
    }
    average_time_float = average_time_float / no_of_trials;
    // print_vector(m, A);
    // print_vector(n, B);
    print_vector(m + n - 1, C);
    printf("Average elapsed time for float: %.9f seconds\n", average_time_float);
}