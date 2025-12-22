#include <stdio.h>
#include <time.h>

#define no_of_trials 100000
#define IU 4
#define IU_cycles 1
#define FPU 2
#define FPU_cycles 3

void multiply_int(int m, int n, int p, int matrix_1[m][n], int matrix_2[n][p], int product[m][p])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            product[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                product[i][j] = product[i][j] + matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
}

void multiply_float(int m, int n, int p, int matrix_1[m][n], int matrix_2[n][p], int product[m][p])
{
    float k = (float)FPU / (float)IU * (float)IU_cycles / (float)FPU_cycles;
    float index = n * k / (k + 1.0f);
    int lower = (int)index;
    if (lower > n - 1)
    {
        lower = n - 1;
    }
    if (lower < 0)
    {
        lower = 0;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            product[i][j] = 0;
            int int_part = 0;
            float float_part = 0.0f;
            for (int l = n - 1; l > lower; l--)
            {
                int_part = int_part + matrix_1[i][l] * matrix_2[l][j];
            }
            for (int l = 0; l <= lower; l++)
            {
                float_part = float_part + (float)matrix_1[i][l] * (float)matrix_2[l][j];
            }
            product[i][j] = (int)float_part + int_part;
        }
    }
    // float A[m], B[n];
    // for (int i = 0; i < m; i++)
    // {
    //     for (int k = 0; k < n; k++)
    //     {
    //         A[k] = (float)matrix_1[i][k];
    //     }

    //     for (int j = 0; j < p; j++)
    //     {
    //         for (int k = 0; k < n; k++)
    //         {
    //             B[k] = (float)matrix_2[k][j];
    //         }
    //         float sum = 0.0f;

    //         for (int k = 0; k < n; k++)
    //         {
    //             sum = sum + A[k] * B[k];
    //         }
    //         product[i][j] = (int)sum;
    //     }
    // }
}

void print_matrix(int m, int n, int matrix[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m, n, p;
    scanf("%d %d %d", &m, &n, &p);
    int matrix_1[m][n], matrix_2[n][p], product_int[m][p], product_float[m][p];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix_1[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            scanf("%d", &matrix_2[i][j]);
        }
    }
    // print_matrix(m, n, matrix_1);
    // print_matrix(n, p, matrix_2);
    double average_time_int = 0;
    // double total_time = 0;
    struct timespec start_1, end_1;
    clock_gettime(CLOCK_MONOTONIC, &start_1);
    for (int i = 0; i < no_of_trials; i++)
    {
        multiply_int(m, n, p, matrix_1, matrix_2, product_int);
        // double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        // average_time_int = average_time_int + elapsed;
        // total_time = total_time + elapsed;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_1);
    average_time_int = (end_1.tv_sec - start_1.tv_sec) + (end_1.tv_nsec - start_1.tv_nsec) / 1e9;
    // average_time = total_time / no_of_trials;
    average_time_int = average_time_int / no_of_trials;
    print_matrix(m, p, product_int);
    printf("Average elapsed time for integer: %.9f seconds\n", average_time_int);

    double average_time_float = 0;
    // double total_time = 0;
    struct timespec start_2, end_2;
    clock_gettime(CLOCK_MONOTONIC, &start_2);
    for (int i = 0; i < no_of_trials; i++)
    {
        multiply_float(m, n, p, matrix_1, matrix_2, product_float);
        // double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        // average_time_float = average_time_float + elapsed;
        // total_time = total_time + elapsed;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_2);
    average_time_float = (end_2.tv_sec - start_2.tv_sec) + (end_2.tv_nsec - start_2.tv_nsec) / 1e9;
    // average_time = total_time / no_of_trials;
    average_time_float = average_time_float / no_of_trials;
    // print_matrix(m, n, matrix_1);
    // print_matrix(n, p, matrix_2);
    print_matrix(m, p, product_float);
    printf("Average elapsed time for float: %.9f seconds\n", average_time_float);
    // printf("Total elapsed time: %.9f seconds\n", total_time);
}