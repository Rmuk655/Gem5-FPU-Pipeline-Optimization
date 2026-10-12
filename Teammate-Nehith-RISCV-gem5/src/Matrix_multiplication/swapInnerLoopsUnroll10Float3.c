#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define n 130

int matrixA[n][n], matrixB[n][n];

int resultantMatrix[n][n];

void multiplyIntegrated(){
    for(int i=0; i<n; i++){
       for(int k=0; k<n; k++){
            int val = matrixA[i][k];
            float floatVal = val;
            int j = 0;
            for(;j<n-9;j+=10){
                resultantMatrix[i][j] += (floatVal*matrixB[k][j]);
                resultantMatrix[i][j+1] += (floatVal*matrixB[k][j+1]);
                resultantMatrix[i][j+2] += (floatVal*matrixB[k][j+2]);
                resultantMatrix[i][j+3] += (val*matrixB[k][j+3]);
                resultantMatrix[i][j+4] += (val*matrixB[k][j+4]);
                resultantMatrix[i][j+5] += (val*matrixB[k][j+5]);
                resultantMatrix[i][j+6] += (val*matrixB[k][j+6]);
                resultantMatrix[i][j+7] += (val*matrixB[k][j+7]);
                resultantMatrix[i][j+8] += (val*matrixB[k][j+8]);
                resultantMatrix[i][j+9] += (val*matrixB[k][j+9]);
            }
            for(;j<n;j++){
                resultantMatrix[i][j] += (val*matrixB[k][j]);
            }
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

    double time = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken: %lf\n",(time));
}