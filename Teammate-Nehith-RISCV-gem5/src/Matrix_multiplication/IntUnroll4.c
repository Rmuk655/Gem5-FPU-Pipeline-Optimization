#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define n 130

int matrixA[n][n], matrixB[n][n];

int resultantMatrix[n][n];

void multiplyInt(){
    for(int i=0; i<n; i++){
        for(int j = 0; j<n; j++){
            int sum1 = 0;
            int sum2 = 0;
            int sum3 = 0;
            int sum4 = 0;
            int k = 0;
            for(; k<n-3; k+=4){
                sum1+=(matrixA[i][k]*matrixB[k][j]);
                sum2+=(matrixA[i][k+1]*matrixB[k+1][j]);
                sum3 += (matrixA[i][k+2]*matrixB[k+2][j]);
                sum4 += (matrixA[i][k+3]*matrixB[k+3][j]); 
            }
            for(;k<n; k++){
                sum1 += (matrixA[i][k]*matrixB[k][j]);
            }
            resultantMatrix[i][j] = sum1 + sum2 + sum3 + sum4 ;
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
    multiplyInt();
    end = clock();

    double exeTime = (double)(end-start)/(CLOCKS_PER_SEC);
    printf("Time taken: %lf\n",exeTime);
    
}