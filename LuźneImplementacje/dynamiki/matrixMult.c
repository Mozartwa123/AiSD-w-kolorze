#include <stdio.h>
#include <limits.h>

// Uwaga... dla przykładowych danych program działa ok.
// Ale łowcy bugów - bądźcie czujni! Nie miałem siły znajdywać większych danych:(

// Zadania dla czytelnika, jeśli znajdzie czas:)

// 1. ~n(n-1) pamięci w dp jest nieużywana - może warto to zoptymalizować?
// 2. Napisać coś lepszego do odtwarzania kolejności niż printefująca rekurencja, może jakiś stos?

int findMinCost(int i, int j, int n, int m[n][n], int d[n+1]){
	int min = INT_MAX;
	int mink = 0;
	for(int k = i; k < j; k++){
		/*
		 *
		 * m[i][k] - mnożenie macierzy M[i]...M[k] da macierz o wymiarach d[i]*d[k+1]
		 * m[k+1][j] - mnożenie macierzy M[k+1]...M[j] da macierz o wymiarach d[k+1]*d[j+1]
		 * 
		 * */
		int cost = m[i][k] + m[k + 1][j] + d[i] * d[k + 1] * d[j+1];
		if(min > cost){
			min = cost;
			mink = k;
		}
	}
	m[i][j] = min;
	return mink;
}

int matMult(int n, int d[n+1], int p[n][n]){
	/*
	 * d[0], ..., d[n] → wymiary macierzy
	 * M[0], ..., M[n - 1] → macierze, tż. wymiary M[i] to d[i] x d[i+1]
	 * m[i][j] → optymalny koszt pomnożenia macierzy M[i], ..., M[j]
	 * p[n][n] → pusta tablica (do odtwarzania ścieżki)
	 * */
	int m[n][n];
	for(int i = 0; i < n; i++){
	    m[i][i] = 0; // Koszt pomnożenia jednej macierzy to 0, bo nic nie mnożymy, gdy macierz jest 1
		p[i][i] = -1;
	}
	for(int s = 1; s < n; s++)
	    for(int i = 0; i + s < n; i++){ // zaczynamy w wierszu 0 i kolumnie s, kończymy na wierszu n - s i kolumnie n
			int j = i + s; // numer kolumny to numer wiersza przesunięty o wartość s
			// czyli rozważając s-tą przekątną
			// rozważamy (0, s), (1, s + 1), ..., (n - s, s + n - s)
    		p[i][j] = findMinCost(i, j, n, m, d);
	    }
	// todo: odtworzenie rozwiązania - na pewno p[n-1][n-1] będzie ostatnim mnożeniem, potem rekurencja
	return m[0][n - 1];
}

void order(int n, int p[n][n], int i, int j){ // c to counter
	if(i >= j){
		return;
	}
	int k = p[i][j]; // ostatnie optymalne mnożenie macieży Mi ... Mj
	// sprawdzamy, jaka była optymalna kolejność Mi ... Mk oraz Mk+1 ... Mj
	order(n, p, i, k);
	order(n, p, k+1, j);
	printf("\t\t%i\n", k + 1);
}

int main(){
	int d[] = {10, 1, 10, 1};
	int n = 3;
	// przykład z notatek... A ma wymiary 10 x 1, B ma wymiary 1 x 10, a C ma wymiary 10 x 1
	int p[3][3];
	printf("### Optymalny koszt mnożenia macierzy wynosi %i ###\n", matMult(n, d, p));
	putchar('\n');
	puts("### Optymalna kolejność mnożenia ###\n");
	order(3, p, 0, n - 1);
	return 0;
}
