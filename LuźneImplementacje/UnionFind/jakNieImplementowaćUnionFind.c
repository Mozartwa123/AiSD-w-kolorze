#include <stdio.h>

// wartość wskaźnika na korzeń będzie identyfikować zbiór

typedef struct {
    int size; // rozmiar poddrzewa
    int setname; // nazwa zbioru do którego ufnode należy
    ufnode* father; // wskaźnik na ojca
} ufnode;

typedef struct {
    ufnode** root; // rooty zbiorów
    ufnode** element; // tablica zawierająca wskaźnik na dany element w drzewie
    int n; // moc uniwersum
    int m; // ilość zbiorów
} unionFind;

ufnode* makeUfnode(int setname){
    ufnode* v = (ufnode*)malloc(sizeof(ufnode));
    v -> size = 1;
    v -> father = v;
    return v;
}

unionFind* init(int n){
    unionFind* uf = (unionFind*)malloc(sizeof(unionFind));
    uf->root = (ufnode**)malloc(sizeof(ufnode*));
    uf->element = (ufnode**)malloc(sizeof(ufnode*));
    uf->n = n;
    for(int i = 0; i < n; i++) uf->root[i] = uf->element[i] = makeUfnode(i);
    return uf;
}

void uffree(unionFind* uf){
    free(uf->root);
    int n =  uf->n;
    for(int i = 0; i < n; i++) free(uf->element[i]);
    free(uf->element);
    free(uf);
}

ufnode* findhelper(ufnode* v){
    if(v -> father == v) return v;
    ufnode* root = findhelper(v->father);
    v->father = root; // podwieszanie
    v->setname = root -> setname; // najwyżej usunę
    return root;
}

ufnode* find(unionFind* uf, int i){ return findhelper(uf->element[i]); }

void onion(int A, int B, unionFind* uf){
    ufnode* root1 = uf->root[A];
    ufnode* root2 = uf->root[B];
    if(root1 -> size > root2 -> size){
        root2 -> father = root1;
        root2 -> setname = root1 -> setname;
    }
    root1 -> father = root2;
    root1 -> setname = root2 -> setname;
}
