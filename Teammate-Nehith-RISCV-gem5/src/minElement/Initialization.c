#include<stdio.h>
#include<stdlib.h>

#define n 100000

int arr[n];

int main(){

    srand(99);
    // Initialization ensuring that the values are less than (2^24-1)
    for(int i = 0; i<n; i++){
        arr[i] = rand()&((1<<24)-1);
    }

    printf("%d",arr[n-1]);
}