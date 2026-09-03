long newtDyn1(long n, long k){
	long N[n + 1][k + 1];
	for(int i = 0; i <= n; i++)
	    for(int j = 0; j<=k; j++)
		N[i][j] = i < j ? 0 : (j == 0 ? 1 : N[i - 1][j] + N[i - 1][j - 1]);
	return N[n][k];
}

/* Ćwiczenie dla czytelnika: Zoptymalizować pamięciowo powyższą procedurę - powinienem to sam zrobić, ale
 * to miała być tylko rozgrzewka..., a nie przerabianie WDI, gdy trzeba się zajmować AiSDem */
