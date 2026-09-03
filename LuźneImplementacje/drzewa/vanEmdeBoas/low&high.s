# .globl low
.globl sqrtOf2Pow
.globl main
# .globl high

sqrtOf2Pow:
    # Uwaga, działa poprawnie wtw argument (%rdi) jest postaci 2^(2^k)
    lzcnt %rdi, %rax
    mov   $64, %rcx
    sub   %al, %cl
    shr   $1, %cl
    shr   %cl, %rdi
    movq  %rdi, %rax
    ret

low:
    # 2 argumenty %rdi - nasza liczba
    # %rsi - długość tej liczby
    