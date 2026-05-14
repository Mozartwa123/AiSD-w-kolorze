#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGINDEX(i) i - 1 // stringi w notatkach KLO są indeksowane od 1, dlatego to makro było konieczne
#define MAX(a, b) (a > b ? a : b)

/*

Po bardziej szczegółowe wyjaśnienia (w tym idei) odsyłam do notatek (WYkład VI) :)

Ciekawe jest to, że ścieżki w tablicy sprawiły mi więcej bólu głowy niż to..., mimo że problem
jest trochę mniej trywialny... no i mamy obsługę stringów w c, co oczywiście bardzo KOCHAMY. I powiem,
że tylko raz segfaulta tu zobaczyłem, a tak to, wszystko ładnie alakowałem i zwalniałem.

Obsługa programu: 
podajemy po prostu dwa stringi na wejście, na końcu każdego ma być enter, wtedy
wypisuje LCSa tych stringów.

Kompilacja gcc -Wall -Wextra -Werror -O2 longestCommonSubsequence.c 
A potem ./a.out :)

*/

char* longestCommonSubsequence(char* x, char* y){
    int n = (int)strlen(x);
    int m = (int)strlen(y);
    int d[n+1][m+1]; // d[i][j] - LCS słów x1...xi oraz y1...yj, i lub j = 0 oznaczają po prostu puste podsłowa
    for(int i = 0; i <= n; i++)
        d[i][0] = 0; // LCS jakiegoś słowa oraz słowa pustego, będzie pusty
    for(int j = 1; j <= m; j++)
        d[0][j] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            d[i][j] =
                x[STRINGINDEX(i)] == y[STRINGINDEX(j)] ?
                        d[i - 1][j - 1] + 1 : /* jeżeli ostatnie litery podsłów są równe, 
                            zwróć długość LCS(x1...xi-1, y1...yj-1) + 1 (dodajemy po prostu 
                            jedną literkę do lcs podsłów z obciętą ostatnią literą) */
                    MAX(d[i - 1][j], d[i][j - 1]); /* albo lcs nie będzie kończył się na xi 
                            lub nie będzie kończył się na yj */
    
    // Parę brzydkich rzeczy z programowania w c (alokacja pamięci na lcs; null terminator):

    int lcslen = d[n][m] + 1;
    char* lcs = (char*)malloc(sizeof(char) * lcslen);
    lcslen--;
    lcs[lcslen] = '\0';
    lcslen--; // index ostatniej litery

    /*
        Teraz odtwarzamy lcs

        i ← n
        j ← m

        Jeżeli xi = yj, to dopisujemy to do lcs, i oraz j zmniejszamy
        wpp. jeżeli lcs x1...xi oraz y1...yj-1 był dłuższy, niż lcs x1...xi-1 oraz y1...yj, to 
        w nim szukamy kolejnej litery (czyli i zostaje, a j zmniejszamy).

        W przeciwnym razie szukamy w x1...xi-1 oraz y1...yj (j zostaje, i dekrementujemy)
        
        */
    int i = n;
    int j = m;
    while(lcslen >= 0){
        if(x[STRINGINDEX(i)] == y[STRINGINDEX(j)]){
            lcs[lcslen] = x[STRINGINDEX(i)];
            lcslen--, i--, j--;
        } else {
            if(d[i][j - 1] >= d[i - 1][j]) j--;
            else i--;
        }
    }

    return lcs;
}

int main(){
    char* x = NULL;
    char* y = NULL;
    size_t lenx = 0;
    size_t leny = 0;
    getline(&x, &lenx, stdin);
    if(x == NULL){
        return 1;
    }
    getline(&y, &leny, stdin);
    if(y == NULL){
        free(x);
        return 1;
    }
    char* s = longestCommonSubsequence(x, y);
    puts(s);
    free(s);
    free(x);
    free(y);
    return 0;
}