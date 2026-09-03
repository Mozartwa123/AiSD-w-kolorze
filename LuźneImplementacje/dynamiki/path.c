#include <stdio.h>
#include <limits.h>

#define DEBUG 1 // Jeśli nie chcecie pomocniczych wypisań zmieńcie to makro na 0 i skompilować ponownie
#define IFDEBUG if(DEBUG)

// kompilacja gcc -Wall -Wextra -Werror -O2 path.c, potem ./a.out

/*
 * D[i][j] oznacza długości dróg wiodących do pola i, j z pól o kolumnie j-1 i wierszy i+1,i,i-1.
 * 
 * Niech P[i][j] oznacza długość najkrótszej ścieżki do pola i, j
 *
 * Wtedy P[i][0] = D[i][0], bo taką pokonaliśmy z pola startowego
 *
 * P[i][j] = długość ścieżki do najbliższego sąsiada + droga z tego sąsiada (D[i][j])
 * (dogłębsze uzasadnienie w notatkach)
 *
 * Ciekawostka: to zadanie było na wstępie do programowania w języku c. 
 * I do dzisiaj napawa mnie ono wstydem (tj. Jest bardzo łatwe, a i tak jestem takim thebilem,
 * że nie potrafię go zrobić):-(
 *  i przypomina mi, jak bardzo nie nadaję się do IT
 * 
 * Ale ktoś sobie wmówił, że jednak się nadaje, więc niestety próbuję robić
 * 
 * Dobra wiadomość! Poniższy kod to 100% moja robota, żadnego AiSlopu:) - napisane i zdebugowane w bólach
 * 
 * w odr. o. roz. z pr. pół r. temu =-$
 * * */

void printP(int col, int cols, int rows, int P[rows][cols]){
	/*
		Funkcja do debugu długości ścieżek po dotarciu do kolejnych kolumn
	*/
	puts("Stan tablicy P:");
	for(int i = 0; i < rows; i++){
		for(int j = 0; j <= col; j++)
			printf("%i ", P[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

int getShortestEdge(int rows, int cols, int row, int col, int P[rows][cols]){
	/*
		Znajdowanie najbliższej odległości do poprzednika
	*/
	IFDEBUG printf("Jesteśmy w polu (%i, %i)\n", row, col); 
	int up = row > 0 ? P[row-1][col-1] : INT_MAX;
	int left = P[row][col-1];
	int down = row < rows - 1 ? P[row+1][col-1] : INT_MAX;
	IFDEBUG printf("Możliwe długości ścieżek to %i, %i, %i\n", up, left, down);
	int min = left < up ? left : up;
	min = down < min ? down : min;
	IFDEBUG printf("Wybieram %i\n\n", min);
	return min;
}

int getShortestAdj(int rows, int cols, int row, int col, int P[rows][cols]){
	/*
		Znajdowanie poprzednika
	*/
	int up = row > 0 ? P[row-1][col-1] : INT_MAX;
	int left = P[row][col-1];
	int down = row < rows ? P[row+1][col-1] : INT_MAX;
	int minrow = left < up ? row : row - 1;
	minrow = down < P[minrow][col-1] ? row + 1 : minrow;
	return minrow;
}

int shortestPath(int rows, int cols, int D[rows][cols]){
	int P[rows][cols];
	IFDEBUG puts("Stan tablicy P");
	for(int row = 0; row < rows; row++){
	    P[row][0] = D[row][0];
		IFDEBUG printf("%i\n", P[row][0]);
	}
	IFDEBUG putchar('\n');
	for(int col = 1; col < cols; col++){
	    for(int row = 0; row < rows; row++)
			P[row][col] = getShortestEdge(rows, cols, row, col, P) + D[row][col];
		IFDEBUG printP(col, cols, rows, P); // To wypisywanie nieco zaburza złożoność czasową, ale to ma być tylko pomoc
	}
	int min = INT_MAX;
	int minrow = 0;
	for(int row = 0; row < rows; row++){
		if(min > P[row][cols - 1]){
			min = P[row][cols - 1];
			minrow = row;
		}
	}

	IFDEBUG puts("Ostatecznie dostajemy ścieżkę:");

	for(int col = cols - 1; col >= 0; col--){
		printf("(%i, %i)\n", minrow, col);
		if(col != 0)
			minrow = getShortestAdj(rows, cols, minrow, col, P);	
	}
	return min;
}

int main(void){
	int rows, cols;
	if(scanf("%i %i", &rows, &cols) != 2)
	    return 1;
	int D[rows][cols];
	for(int row = 0; row < rows; row++)
		for(int col = 0; col < cols; col++)
			if(scanf("%i", &(D[row][col])) != 1)
				return 1;
	printf("%i\n", shortestPath(rows, cols, D));
	return 0;
}