/*
    Zapakowałem to co prawda w structa dla jakieś hierarchi, ale to raczej wielkiego sensu raczej
    nie ma
*/

typedef struct{
    int n;
    int* father;
    int* size;
    // int* root;
} unionFind;

unionFind* ufinit(int n, int father[n], int size[n]);
// Alokuje unionFinda na stercie. Chcemy unikać alokowania, więc użytkownik sam deklaruje obie tablice
void ufdelete(unionFind* uf);
// Nie używać dwa razy! Nie zwalniać unionFinda w inny sposób niż używając tej funkcji
int find(unionFind* uf, int i);
// dla danego unionFinda i elementu itego w uniwersum znajduje reprezentanta
void onion(unionFind* uf, int i, int j);
// łączy zbiory do którego należą i oraz j
void ufprint(unionFind* uf);
// absurdalnie nieoptymalna funkcja do debugowania :(
// co gorsza wypisuje zbiór tyle razy ile wynosi moc zbioru...
