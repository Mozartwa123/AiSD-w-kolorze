#include "heap.h" 
// #include <stdio.h>  
 
void moveDown(int n, int i, int* H){
	if(i >= n){
		return;
	} 
	int k = i;
	int j = k;
	do {
		j = k;
		if(2 * (j + 1) <= n && H[k] < H[2 * (j + 1) - 1]){
			k = 2 * (j + 1) - 1;
		}
	    if(2 * (j + 1) < n && H[k] < H[2 * (j + 1)]){
			k = 2 * (j + 1);  
		}
		if(j != k){
			H[j] ^= H[k];
			H[k] ^= H[j];
			H[j] ^= H[k];
		}
	} while(k != j);
}	

void moveUp(int n, int i, int* H){
	if(i >= n){
		return;
	}
	int k = i;
	int j = k;
	do {
		j = k;
		if(j > 0 && H[k] < H[(j-1)/2]){
			k = (j - 1)/2;
		}
		if(j != k){
			H[j] ^= H[k];
			H[k] ^= H[j];
			H[j] ^= H[k];
		}
	} while(k != j);
}

void replace(int n, int i, int newValue, int* H){
	if(i >= n){
		return;
	}
	int oldValue = H[i];
	H[i] = newValue;
	if(H[i] > oldValue){
		moveUp(n, i, H);
	} else {
		moveDown(n, i, H);
	}
}

void buildHeap(int n, int* H){
	//printf("Hello");  
	for(int i = n / 2 - 1; i >= 0; i--){
		moveDown(n, i, H);
	}
}

void heapSort(int n, int* H){
	buildHeap(n, H);
	for(int i = n - 1; i > 0; i--){ 
		int top = H[i];
		H[i] = H[0];
		replace(i, 0, top, H);  
	}
}