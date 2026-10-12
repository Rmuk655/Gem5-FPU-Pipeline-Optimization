#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 130

int matrixA[n][n], matrixB[n][n];
int resultantMatrix[n][n];

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

    printf("%d\n",matrixA[n-1][n-1]+matrixB[n/2][n-1] + resultantMatrix[n-1][0]);
}