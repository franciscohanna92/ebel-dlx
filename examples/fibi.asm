;;; -- Iterative Fibonacci computation
;;; -- Result of fib(N) is put in R1
    
N equ 7
    
    addi r5, r0, N-1    ; -- Init
    addi r1, r0, 1
    addi r2, r0, 1

loop: beqz r5, fin
    
    add r3, r2, r1      ; -- Iterative Loop
    add r1, r0, r2
    add r2, r0, r3

    addi r5, r5, -1
    j loop

fin:  add r1, r3, r0    ; -- Result in r1
    trap 0
