#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define n 130

int matrixA[n][n], matrixB[n][n];

int resultantMatrix[n][n];


void multiplyInt(){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            int sum1 = 0;
            for(int k = 0; k<n; k++){
                sum1 += (matrixA[i][k]*matrixB[k][j]);
            }
            resultantMatrix[i][j] = sum1;
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

    double time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time taken: %lf\n",time);
}