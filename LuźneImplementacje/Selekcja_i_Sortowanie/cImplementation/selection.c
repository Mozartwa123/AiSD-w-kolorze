#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(i, j) i^=j; j^=i; i^=j
#define RANDOM(b, e) rand() % (e - b + 1) + b
#define USEINSERT 5

/*
Chociaż zatytułowałem ten plik selection.c, to znajdziecie tutaj dwie wersje partycjonowania Hoora, sortowanie
szybkie, przez wstawianie, no i oczywiście deterministyczny algorytm selecji, który działa w czasie liniowym
Kompilacja: gcc -g -Wall -Wextra -Werror -O3 -pedantic selection.c
Uruchomienie: ./a.out
Program najpierw wypisze posortowaną tablicę arr1, a potem linijka po linijce wypisze pierwszy, drugi, .., trzynasty
element tablicy arr5
*/

void insertSort(int* arr, int b, int e){
    for(int i = b; i <= e; i++){
        int j = i;
        int temp = arr[j];
        while(j > b && temp < arr[j - 1]){
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }
}

int partition1(int* arr, int b, int e){
    // uprzedzam, że coś z tą implementacją jest nie tak...
    // wydawało mi się, że jest równoważne partition 2, ale tylko ta druga wersja działa w selection
    // bug hunterzy mile widziani:)
    int i = b, j = e, pivot = arr[0];
    while(i < j){
        while(arr[i] < pivot) i++;
        while(arr[j] > pivot) j--;
        if(i < j){
            SWAP(arr[i], arr[j]);
            i++; j--;
        }
    }
    return j;
}

int partition2(int* arr, int b, int e){
    int i = b - 1, j = e + 1, pivot = arr[b];
    while(1){
        do{}while(arr[++i] < pivot);
        do{}while(arr[--j] > pivot);
        if(i >= j) return j;
        SWAP(arr[i], arr[j]);
    }
}

void printArr(int* arr, int b, int e){
    for(int i = b; i <= e; i++)
        printf("%i ", arr[i]);
    putchar('\n');
}


void quicksort(int* arr, int b, int e){
    if(b < e){
        int r = RANDOM(b, e);
        if(arr[b] != arr[r]){
            SWAP(arr[b], arr[r]);
        }
        int p = partition2(arr, b, e);
        quicksort(arr, b, p);
        quicksort(arr, p+1, e);
    }
}

void naiveMedian(int* arr, int b, int e){
    // printf("Function naiveMedian called with pointers %i, %i\n", b, e);
    // naiwny algorytm w oczekiwanym czasie O(nlogn), sortuje tablice a następnie medianę zamienia z pierwszym elementem
    if(e < b){
        return;
    }
    if(e - b < USEINSERT){
        insertSort(arr, b, e);
    } else {
        quicksort(arr, b, e);
    }
    int medianPos = (e + b) / 2;
    if(arr[b] != arr[medianPos]){
        SWAP(arr[b], arr[medianPos]);
    }
}

int makeFives(int* arr, int b, int e){
    // funkcja, dla każdej piątki (bądź reszty niepodzielnej przez 5)
    // sortuje ją, i dla każdej piątki kolejne mediany umieszcza na początku tablicy
    // na końcu zwraca index ostatniej takiej mediany
    int pos = b;
    for(int i = b, j = b; i <= e; i+=5, j++){
        pos = j;
        int k = i + 4;
        if(k > e) k = e;
        // printf("Before ");
        // printArr(arr, i, k);
        naiveMedian(arr, i, k);
        // printf("After ");
        // printArr(arr, i, k);
        // printArr(arr, b, e);
        if(arr[i] != arr[j]){
            SWAP(arr[i], arr[j]);
        }
    }
    // printArr(arr, b, e);
    // printf("End on position %i\n", pos);
    return pos;
}

int selection(int* arr, int b, int e, int k){
    // wybór k-tego elementu w deterministycznym czasie liniowym (ale z wypierdzistą stałą)
    // oczywiście k-ty, tj. index w posortowanej tablicy, czyli np. element pierwszy będzie zerowym, etc.
    // zwany też algorytmem magicznych piątek
    // ten algorytm przysporzył mi mnóstwo Cierpień Młodego Wertera...
    if(e - b < USEINSERT){
        // jeśli problem jest prosty, naiwnie sortujemy i wybieramy k-ty element
        insertSort(arr, b, e);
        return arr[b + k];
    }
    // znajdujemy mediany kolejnych piątek
    int fivesEnd = makeFives(arr, b, e);
    // rekurencyjnie znajdujemy medianę tych median
    int pivot = selection(arr, b, fivesEnd, (fivesEnd - b)/2);
    // przesuwamy pivota na początkową pozycję roważanej podtablicy
    for(int i = b; i <= e; i++){
        if(arr[i] == pivot){
            if(arr[i] != arr[b]){
                SWAP(arr[b], arr[i]);
            }
            break;
        }
    }
    int j = partition2(arr, b, e);
    // Może się zdarzyć, że pivot będzie tylko w pierwszej połówce..., zatem trzeba sprawdzić w której jest dokładnie
    // Dla przykładu, że tak rzeczywiście może być wystarczy popartycjonować posortowaną tablicę
    for(int i = j + 1; i <= e; i++){
        if(arr[i] == pivot){
            // wtedy elementy pod indeksami b, ..., b + j - b są mniejsze równe od pivota, zatem jest j - b + 1-szym elementem
            int p = j - b + 1;
            return p == k ? pivot : (p > k ? selection(arr, b, j, k) : selection(arr, j + 1, e, k - p));
        }
    }
    // b, ..., b + j - b są mniejsze równe od pivota, ale dalsze są już większe, pivot jest j - b elementem
    int p = j - b;
    return p == k ? pivot : (p > k ? selection(arr, b, j, k) : selection(arr, j + 1, e, k - p));
}

int main(){
    srand(time(NULL));
    int arr1[] = {55, 42, 13, 41, 24, 61, 99, 1, 22, 25, 14, 32, 24, 100, 25, 77, 2, 4, 3};
    int n = sizeof(arr1)/sizeof(int);
    quicksort(arr1, 0, n - 1);
    printArr(arr1, 0, n - 1);
    //printArr(arr1, 0, n - 1);
    //printArr(arr1, 0, n - 1);
    int arr5[] = {55, 42, 13, 41, 24, 61, 99, 1, 22, 25, 14, 32, 24};
    // int arr6[] = {55, 42, 13, 41, 24, 61, 99, 1, 22, 25, 14, 32, 24, 100};
    // makeFives(arr5, 0, 12);
    // makeFives(arr6, 0, 13);
    // int arr7[] = {1, 2, 3, 4, 5, 6, 7};
    for(int i = 0; i <= 12; i++){
        // bardzo nieefektywne, niestabilne, sortowanie
        // który jest gorszy czasowo (pod względem stałej, bo asymptotycznie, chyba taki sam)
        // od buble sorta
        printf("%i\n", selection(arr5, 0, 12, i));
    }
}