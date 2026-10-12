#include <stdio.h>
#include <time.h>
#include<stdlib.h>

#define m 500
#define n 500

int A[m], B[n], C[m+n-1];

void convolution_int(){
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            C[i+j] += (A[i]*B[j]);
        }
    }
}


int main()
{

    srand(100);

    for(int i = 0; i<m; i++){
        A[i] = rand();
    }
    for(int i = 0; i<n; i++){
        B[i] = rand();
    }

    for(int i = 0; i<(n+m-1); i++){
        C[i] = 0;
    }

    clock_t start, end;
    start = clock();
    convolution_int();
    end = clock();

    double exeTime = (double)(end-start)/(CLOCKS_PER_SEC);
    printf("Time taken: %lf\n",exeTime);

}