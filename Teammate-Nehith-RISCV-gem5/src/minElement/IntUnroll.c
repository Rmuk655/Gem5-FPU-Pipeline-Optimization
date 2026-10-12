#include<stdio.h>
#include<stdlib.h>

#define n 100000

int arr[n];

int main(){
    
    srand(20);
    // Initialization ensuring that the values are less than (2^24-1)
    for(int i = 0; i<n; i++){
        arr[i] = rand()&((1<<24)-1);
    }

    // INT_MAX = ~(1<<31)
    int min1, min2, min3, min4, min5;
    min1 = ~(1<<31);
    min2 = ~(1<<31);
    min3 = ~(1<<31);
    min4 = ~(1<<31);
    min5 = ~(1<<31);

    int val1, val2, val3, val4, val5;

    int* arrptr = arr;
    int* endptr = arr+n-4;
    while((long long)arrptr < (long long)(endptr)){

        val4 = arrptr[0];
        val1 = arrptr[1];
        val2 = arrptr[2];
        val3 = arrptr[3];
        val5 = arrptr[4];

        min4 = (val4 < min4)?val4:min4;
        min1 = (val1 < min1)?val1:min1;
        min2 = (val2 < min2)?val2:min2;
        min3 = (val3 < min3)?val3:min3;
        min5 = (val5 < min5)?val5:min5;

        arrptr += 5;
    }

    while((long long)arrptr < (long long)(arr+n)){
        val1 = arrptr[0];   
        min1 = (val1 < min1)?val1:min1;
        arrptr += 1;
    }

    if(min2 < min1){
        min1 = min2;
    }
    if(min3 < min1){
        min1 = min3;
    }
    if(min4 < min1){
        min1 = min4;
    }
    if(min5 < min1){
        min1 = min5;
    }

    printf("min Element for IntUnroll: %d\n",min1);

}