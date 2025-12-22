#include <stdio.h>
#include <time.h>

#define no_of_trials 1000000

void multiply(int m, int n, int p, int matrix_1[m][n], int matrix_2[n][p], int product[m][p])
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
    int matrix_1[m][n], matrix_2[n][p], product[m][p];
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
    print_matrix(m, n, matrix_1);
    print_matrix(n, p, matrix_2);
    double average_time = 0;
    // double total_time = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        multiply(m, n, p, matrix_1, matrix_2, product);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time = average_time + elapsed;
        // total_time = total_time + elapsed;
    }
    // average_time = total_time / no_of_trials;
    average_time = average_time / no_of_trials;
    print_matrix(m, p, product);
    printf("Average elapsed time: %.9f seconds\n", average_time);
    // printf("Total elapsed time: %.9f seconds\n", total_time);
}