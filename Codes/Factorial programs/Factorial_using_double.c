#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

#define no_of_trials 1000000
#define IU 4
#define IU_cycles 1
#define FPU 4
#define FPU_cycles 2

// Max value for which we can find the factorial of n using fact_int is 20.
// Max value for which we can find the factorial of n using fact_float is 20.
// The factorial of 20 is 2432902008176640000 (integer code).
// The factorial of 20 is 2432902008176640000 (floating point code).
// The factorial of 20 is 2432902008176640000 (double code).
// The fact_int and fact_float values match upto n = 20.

unsigned long long int fact_double(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1, fact_int = 1;
    double k = (double)FPU / (double)IU * (double)IU_cycles / (double)FPU_cycles;
    double index = n * k / (k + 1);
    int lower = (int) index;
    // Ratio of work done by CPU/FPU = 1/k.
    for (int i = n; i > lower; i--)
    {
        fact_int = fact_int * (unsigned long long int)i;
    }
    double fact_float = 1.0;
    for (int i = 1; i <= lower; i++)
    {
        fact_float = fact_float * (double)i;
    }
    fact = fact_int * (unsigned long long int)fact_float;
    return fact;
}

int max_valid_n_double()
{
    int i = 0;
    while (fact_double(i) != 0)
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
        fact_double(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time = average_time + elapsed;
    }
    average_time = average_time / no_of_trials;
    // start = clock();
    // fact_double(n);
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The factorial of %d is %llu\n", n, fact_double(n));
    printf("The maximum valid value of n in fact_double(n) is %d\n", max_valid_n_double());
    printf("Average elapsed time: %.9f seconds\n", average_time);
    // printf("The time taken by the program is %lf seconds.", cpu_time_used);
}