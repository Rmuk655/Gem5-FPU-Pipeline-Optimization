#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define n 130

int matrixA[n][n], matrixB[n][n];

int resultantMatrix[n][n];

void multiplyIntegrated(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           float sum1 = 0.0f;
           for(int k=0; k<n; k++){
            sum1 += ((float)matrixA[i][k]*(float)matrixB[k][j]);
           }
           resultantMatrix[i][j] = (int)sum1;
        }
    }
}

int main(){

    srand(100);

    //Initialization

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            matrixA[i][j] = rand();
        }
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            matrixB[i][j] = rand();
        }
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            resultantMatrix[i][j] = 0;
        }
    }

    clock_t start, end;

    start = clock();
    multiplyIntegrated();
    end = clock();

    double exeTime = (double)(end-start)/(CLOCKS_PER_SEC);

    printf("Time taken: %lf\n",exeTime);
}