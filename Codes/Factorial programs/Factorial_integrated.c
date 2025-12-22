#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#define no_of_trials 1000000
#define IU 4
#define IU_cycles 1
#define FPU 2
#define FPU_cycles 3

// Max value for which we can find the factorial of n using fact_int is 20.
// Max value for which we can find the factorial of n using fact_float is 20.
// The fact_int and fact_float values match upto n = 20 only.
unsigned long long int fact_int(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        if (fact > ULLONG_MAX / (unsigned long long int)i)
        {
            printf("Overflow!");
            return fact;
        }
        fact = fact * (unsigned long long int)i;
    }
    return fact;
}

unsigned long long int fact_float(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1, fact_int = 1;
    float k = pow((float)FPU / (float)IU, 1) * pow((float)IU_cycles / (float)FPU_cycles, 0.1);
    float index = n * k / (k + 1);
    int lower = (int)index;
    for (int i = n; i > lower; i--)
    {
        if (fact_int > ULLONG_MAX / (unsigned long long int)i)
        {
            printf("Overflow!");
            return fact;
        }
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

unsigned long long int fact_double(int n)
{
    if (n == 0)
    {
        return 1;
    }
    unsigned long long int fact = 1, fact_int = 1;
    double k = (double)FPU / (double)IU * (double)IU_cycles / (double)FPU_cycles;
    double index = n * k / (k + 1);
    int lower = (int)index;
    for (int i = n; i > lower; i--)
    {
        if (fact_int > ULLONG_MAX / (unsigned long long int)i)
        {
            printf("Overflow!");
            return fact;
        }
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

int max_valid_n_float()
{
    int i = 0;
    while (fact_float(i) != 0 && i <= 20)
    {
        i++;
    }
    i--;
    return i;
}

int max_valid_n_double()
{
    int i = 0;
    while (fact_double(i) != 0 && i <= 20)
    {
        i++;
    }
    i--;
    return i;
}

int max_valid_n_with_float()
{
    int i = 0;
    while (fact_float(i) != 0 && fact_int(i) == fact_float(i) && i <= 20)
    {
        i++;
    }
    i--;
    return i;
}

int max_valid_n_with_double()
{
    int i = 0;
    while (fact_double(i) != 0 && fact_int(i) == fact_double(i) && i <= 20)
    {
        i++;
    }
    i--;
    return i;
}

int main()
{
    int n;
    scanf("%d", &n);
    double average_time_int = 0, average_time_float = 0, average_time_double = 0;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        fact_int(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time_int = average_time_int + elapsed;
    }
    average_time_int = average_time_int / no_of_trials;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        fact_float(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time_float = average_time_float + elapsed;
    }
    average_time_float = average_time_float / no_of_trials;
    for (int i = 0; i < no_of_trials; i++)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        fact_double(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        average_time_double = average_time_double + elapsed;
    }
    average_time_double = average_time_double / no_of_trials;
    printf("The factorial of %d is %llu\n", n, fact_int(n));
    printf("The factorial of %d is %llu\n", n, fact_float(n));
    printf("The factorial of %d is %llu\n", n, fact_double(n));
    printf("The maximum valid value of n in fact_float(n) is %d\n", max_valid_n_float());
    printf("The maximum valid value of n in fact_double(n) is %d\n", max_valid_n_double());
    printf("The maximum valid value of n for which fact_int(n) and fact_float(n) values match is %d\n", max_valid_n_with_float());
    printf("The maximum valid value of n for which fact_int(n) and fact_double(n) values match is %d\n", max_valid_n_with_double());
    printf("Average elapsed time for fact_int(): %.9f seconds\n", average_time_int);
    printf("Average elapsed time for fact_float(): %.9f seconds\n", average_time_float);
    printf("Average elapsed time for fact_double(): %.9f seconds\n", average_time_double);
}