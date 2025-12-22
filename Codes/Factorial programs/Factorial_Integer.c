#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include "Factorial_Integer.h"

#define no_of_trials 1000000

// Max value for which we can find the factorial of n is 20.
// The factorial of 20 is 2432902008176640000
unsigned long long int fact_int(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        fact = fact * (unsigned long long int)i;
    }
    return fact;
}

int max_valid_n_int()
{
    int i = 0;
    while (fact_int(i) != 0)
    {
        i++;
    }
    i--;
    return i;
}

int main()
{
    // clock_t start, end;
    // double cpu_time_used;
    int n;
    scanf("%d", &n);
    double average_time = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        fact_int(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time = average_time + elapsed;
    }
    average_time = average_time / no_of_trials;
    // start = clock();
    // fact_int(n);
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The factorial of %d is %llu\n", n, fact_int(n));
    printf("The maximum valid value of n in fact_int(n) is %d\n", max_valid_n_int());
    printf("Average elapsed time: %.9f seconds\n", average_time);
    // printf("The time taken by the program is %lf seconds.", cpu_time_used);
}