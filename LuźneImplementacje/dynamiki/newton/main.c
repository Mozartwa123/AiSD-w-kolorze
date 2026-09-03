#include <stdio.h>
/*
 * Idea:
 *
 * Chcemy liczyć symbol newtona korzystając z toższamości Pascala, tj.
 *
 * Niech newt(n, k) oznacza n po k. Wtedy newt(n, k) = 0, gdy k > n, newt(n, k) = 1 gdy k = 1, w pozostałych przypadkach (oczywiście dla naturalnych n, k) mamy newt(n, k) = newt(n - 1, k) + newt(n - 1, k - 1).
 *
 * Z racji, iż interdycyplinarność to efektywna metoda nauki, postanowiłem połączyć powtórkę AiSD z powtórką z ASKa, dlatego naiwne liczenie powyższej rekurencji zaimplementowałem w assemblerze:)
 *
 * Jeśli ktoś chce odpalić ten program można użyć komendy gcc -Wall -Werror -Wextra -O2 main.c newtR.s newtDyn.c do skompilowania programu.
 *
 * Potem zwyczajnie ./a.out i wpisać po przecinku n i k
 * */

long newtR(long n, long k);
long newtDyn1(long n, long k);

int main(){
	long n, k;
	if(scanf("%li %li", &n, &k) != 2) return 1;
	printf("%li\n", newtDyn1(n, k));
	printf("%li\n", newtR(n, k));
	return 0;
}
