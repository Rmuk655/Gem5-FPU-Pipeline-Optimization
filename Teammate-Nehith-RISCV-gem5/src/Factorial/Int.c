#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#define no_of_trials 100000


// Max value of n for which we can find the factorial of n is 20.
unsigned long long int fact_int(int n){
    if (n == 0){
        return 1;
    }
    unsigned long long int fact = 1;
    for (int i = 2; i<=n; i++){
        fact = fact * (unsigned long long int)i;
    }
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
        factorial = fact_int(n);
        end = clock();
        avgTime += (double)(end-start)/CLOCKS_PER_SEC/(i);
    }

    printf("Factorial(Int): %lld\n",factorial);
    printf("Time taken(Int): %lf\n",avgTime);

}