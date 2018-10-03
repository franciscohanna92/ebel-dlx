;;; -- Recursive Fibonacci computation (using a stack and
;;; -- activation blocks)
;;; -- fib(N) is in r1 after execution.
    
; r30 is the frame stack pointer
    
N equ 7
; Stack frame structure
PARAM_N    equ 0
PARAM_RET  equ 4
PARAM_T1   equ 8
PARAM_T2   equ 12
PARAM_LENGTH equ 16   
    addi r30, r0, stack             ; Initialise the stack

    addi r1, r0, N                 ; Call fib( N )
    sw PARAM_N(r30), r1
    jal fib
    lw r1, PARAM_N(r30)            ; Put the result in R1 
    trap 0
    
fib:
    sw PARAM_RET(r30), r31  

    lw r1, PARAM_N(r30)            ; if n < 2 
    slti r2, r1, 2
    beqz r2, fib_suite
    addi r1, r0, 1                 ; N <- 1 
    j fib_fin

fib_suite:      
    lw r1, PARAM_N( r30 )          ; Call fib( N - 1 ) 
    addi r30, r30, PARAM_LENGTH
    addi r1, r1, -1
    sw  PARAM_N( r30 ),r1
    jal fib
    lw  r2, PARAM_N( r30 )
    addi r30, r30, -PARAM_LENGTH        
    sw  PARAM_T1( r30 ), r2        ; T1 <- fib( N - 1 ) 

    lw r1, PARAM_N( r30 )          ; Call fib( N - 2 )
    addi r30, r30, PARAM_LENGTH
    addi r1, r1, -2
    sw  PARAM_N( r30 ),r1
    jal fib
    lw  r2, PARAM_N( r30 )
    addi r30, r30, -PARAM_LENGTH        
    sw  PARAM_T2( r30 ), r2        ; T2 <- fib( N - 2 )       

    lw r1, PARAM_T1( r30 )         ; N <- T1 + T2
    lw r2, PARAM_T2( r30 )
    add r1, r1, r2

fib_fin:    
    sw PARAM_N( r30 ), r1          ; return N     
    lw r1, PARAM_RET( r30 )
    jr r1

  

data org 0
stack word [ 4*N ]
    
