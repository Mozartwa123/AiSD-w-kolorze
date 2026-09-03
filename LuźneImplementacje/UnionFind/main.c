#include "unionFind.h"

int main(){
    int n = 6;
    int father[n];
    int size[n];
    unionFind* uf = ufinit(n, father, size);
    ufprint(uf);
    onion(uf, 0, 1);
    onion(uf, 2, 3);
    ufprint(uf);
    onion(uf, 3, 4);
    ufprint(uf);
    onion(uf, 4, 5);
    onion(uf, 5, 1);
    ufprint(uf);
    ufdelete(uf);
}