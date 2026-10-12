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

    int min1;
    // INT_MAX = ~(1<<31)
    min1 = ~(1<<31);

    for(int i = 0; i<n; i++){
        int value = arr[i];
        if(value < min1){
            min1 = value;
        }
    }

    printf("min Element for Int: %d\n",min1);

}