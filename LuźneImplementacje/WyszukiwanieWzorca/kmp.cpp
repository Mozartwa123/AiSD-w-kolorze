#include <cstdio>
#include <cstdlib>
#include <string>

// Tym razem w c++ ze względu na to, że mam dość c stringów
// kompilacja g++ -Wall -Wextra -Werror -pedantic kmp.cpp
// uruchomienie ./a.out - wypisuje najpierw ładnie funkcję pi, a potem wypisuje przesunięcia
// uwaga - indeksowanie jest od 0 - co powoduje, że jeżeli prefiksosufiks p1...pq nie istnieje, to pi[q] = -1!

int* genPi(std::string s){
    int len = s.length();
    int* pi = (int*)malloc(sizeof(int) * len);
    pi[0] = -1;
    int k = -1;
    for(int q = 1; q < len; q++){
        while(k > -1 && s[k + 1] != s[q]) k = pi[k];
        if(s[k + 1] == s[q]) k++;
        pi[q] = k;
    }
    return pi;
}

int main(){
    std::string s = "abacaba";
    int* pi = genPi(s);
    int len = s.length();
    for(int i = 0; i < len; i++){
        printf("%2c ", s[i]);
    }
    putchar('\n');
    for(int i = 0; i < len; i++){
        printf("%2i ", pi[i]);
    }
    putchar('\n');
    std::string t = "abacabacaba";
    int q = -1;
    int n = t.length();
    for(int i = 0; i < n; i++){
        while(q > -1 && s[q + 1] != t[i]) q = pi[q];
        if(s[q + 1] == t[i]) q++;
        if(q == len - 1){
            printf("Wzorzec występuje w tekście z przesunięciem %i\n", i - len + 1);
            q = pi[q];
        }
    }
    free(pi);
}