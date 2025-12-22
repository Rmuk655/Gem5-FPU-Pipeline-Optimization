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
// The fact_int and fact_float values match upto n = 20 only.

unsigned long long int fact_float(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1, fact_int = 1;
    float k = (float)FPU / (float)IU * (float)IU_cycles / (float)FPU_cycles;
    float index = n * k / (k + 1);
    int lower = (int) index;
    for (int i = n; i > lower; i--)
    {
        fact_int = fact_int * (unsigned long long int)i;
    }
    float fact_float = 1.0;
    for (int i = 1; i <= lower; i++)
    {
        fact_float = fact_float * (float)i;
    }
    fact = fact_int * (unsigned long long int)fact_float;
    return fact;
}

int max_valid_n_float()
{
    int i = 0;
    while (fact_float(i) != 0)
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
        fact_float(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time = average_time + elapsed;
    }
    average_time = average_time / no_of_trials;
    // start = clock();
    // fact_float(n);
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The factorial of %d is %llu\n", n, fact_float(n));
    printf("The maximum valid value of n in fact_float(n) is %d\n", max_valid_n_float());
    printf("Elapsed time: %.9f seconds\n", average_time);
    // printf("The time taken by the program is %lf seconds.", cpu_time_used);
}