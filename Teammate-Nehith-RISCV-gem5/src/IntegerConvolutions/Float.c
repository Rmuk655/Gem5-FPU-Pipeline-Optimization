#include <stdio.h>
#include <time.h>
#include<math.h>
#include<stdlib.h>

#define IU 4
#define IU_cycles 1
#define FPU 2
#define FPU_cycles 5

#define m 500
#define n 500

int A[m], B[n], C[m+n-1];

void convolution_float(){
    float k = pow((float)FPU / (float)IU, 1) * pow((float)IU_cycles / (float)FPU_cycles, 3);
    float index = m*k/(k+1);
    int split_index = (int)index;
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            if(i<split_index){
                float prod = (float)A[i]*(float)B[j];
                C[i+j] = C[i+j] + (int)prod;
            }
            else{
                C[i+j] = C[i+j] + (A[i]*B[j]);
            }
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
    convolution_float();
    end = clock();

    double exeTime = (double)(end-start)/(CLOCKS_PER_SEC);
    printf("Time taken: %lf\n",exeTime);

}