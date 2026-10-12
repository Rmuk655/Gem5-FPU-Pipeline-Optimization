#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>


#define no_of_trials 100000
#define IU 4
#define IU_cycles 1
#define FPU 2
#define FPU_cycles 3

// Max value of n for which we can find the factorial of n is 20.
unsigned long long int fact_double(int n){
    unsigned long long int fact = 1;
    double factdouble = 1.0f;
    double k = pow((double)FPU / (double)IU, 1) * pow((double)IU_cycles / (double)FPU_cycles, 0.1);
    double index = n * k / (k + 1);
    int lower = (int)index;
    for (int i = n; i > lower; i--){
        fact = fact * (unsigned long long int)i;
    }
    for (int i = 2; i <= lower; i++)
    {
        factdouble = factdouble * (double)i;
    }
    fact = fact * (unsigned long long int)factdouble;
    return fact;
}

int main()
{
    int n;
    n = 20;
    unsigned long long int factorial;
    clock_t start, end;
    double avgTime = 0;

    for(int i = 1; i<=no_of_trials; i++){
        start = clock();
        factorial = fact_double(n);
        end = clock();
        avgTime += (double)(end-start)/CLOCKS_PER_SEC/(i);
    }

    printf("Factorial(Int): %lld\n",factorial);
    printf("Time taken(Int): %lf\n",avgTime);

}