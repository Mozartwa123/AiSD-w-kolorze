#include <stdio.h>
#include <stdlib.h>
#include "unionFind.h"

unionFind* ufinit(int n, int father[n], int size[n]){

    unionFind* uf = (unionFind*)malloc(sizeof(unionFind)); // potrzebujemy przekazywać wskaźnik
    for(int i = 0; i < n; i++){
        father[i] = i;
        size[i] = 1;
    }
    uf->father = father;
    uf->size = size;
    uf->n = n;
    return uf;
}

void ufdelete(unionFind* uf){
    free(uf);
}

int find(unionFind* uf, int i){
    return uf->father[i] = uf->father[i] == i ? i : find(uf, uf->father[i]);
}

void onion(unionFind* uf, int i, int j){ 
    // bo język c to język dla cebulaków:)
    // tak na poważnie union jest słowej kluczowym
    int rooti = find(uf, i);
    int rootj = find(uf, j);
    if(rooti == rootj){
        return;
    }
    if(uf->size[rooti] < uf->size[rootj]){
        rooti ^= rootj;
        rootj ^= rooti;
        rooti ^= rootj;
    }
    uf->father[rootj] = rooti;
    uf->size[rooti] += uf->size[rootj];
}

void ufprint(unionFind* uf){
    // absurdalnie nieoptymalna funkcja do debugowania :(
    for(int i = 0; i < uf->n; i++){
        int root = find(uf, i);
        printf("\n=== ZBIÓR O KORZENIU %i I ROZMIARZE %i ===\n\n", root, uf->size[root]);
        int counter = 1;
        for(int j = 0; j < uf->n; j++){
            if(find(uf, j) == root){
                printf("%i. %i\n", counter, j);
                counter++;
            }
        }
    }
}