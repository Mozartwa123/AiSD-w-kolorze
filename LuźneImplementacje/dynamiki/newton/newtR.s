.globl newtR

# n będzie podawane w rejestrze %rdi
# k w %rsi

# dla przejrzystości zakładamy, że n ≥ k
newtR:
	testq	%rsi,%rsi # jeżeli k = 0, zwróć 1
	je	L2	
	cmpq	%rdi,%rsi # jeżeli n < k zwróć 0
	jg	L1
	decq	%rdi # dekrementujemy n
	pushq	%rdi # zapamiętujemy n i k na stosie, bo kolejne wywołania mogą nadpisać rejestry
	pushq	%rsi
	call	newtR # wywołujemy rekurencyjnie n - 1 nad k
	popq	%rsi # pobieramy k ze stosu
	popq	%rdi # pobieramy n - 1 ze stosu
	decq	%rsi # dekrementujemy k
	pushq	%rax # spamiętujemy wynik poprzedniego wywołania na stosie
	call	newtR # wywołujemy rekurencyjnie n - 1 nad k - 1
	popq	%rcx # pobieramy wynik poprzedniego wywołania ze stosu
	leaq	(%rax,%rcx), %rax # sumujemy n - 1 nad k oraz n - 1 nad k - 1 i zwracamy
	ret
L1:
	xorq	%rax,%rax
	ret
L2:
	movq	$1,%rax
	ret
