#include <stdio.h>
#include "heap.h"

int main(){
    int H[15] = {0, 4, 2, 5, 3, 6, 7, 10, 1, 42, -32, -108, 16, 59, 2};
    //printf("Hello"); 
    heapSort(15, H);  
    for(int i = 0; i < 15; i++){
        printf("%i ", H[i]);
    }
    printf("\n"); 
    return 0; 
}
