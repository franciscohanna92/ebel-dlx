; Recursive Factorial (yes, the risk of stack overflow exists if Q >= N)
Q equ 7                 ; Factorial of Q (Q!) will be computed.
add r1,r0,r0            ; Where are we in the stack
addi r2,r0,Q            ; Current factorial to compute

loop1: beqz r2,zero     ; End of phase I
addi r1,r1,1            ; Go farther
subi r2,r2,1            ; Compute one less
j loop1
zero: slli r4,r1,2      ; Compute address
addi r5,r5,1            ; Hard-coded 1
sw tab(r4),r5
loop2: beqz r1,end      ; End of phase II
slli r4,r1,2            ; Compute address of previous
lw r6,tab(r4)           ; Load prev
subi r1,r1,1            ; Unwind stack
addi r2,r2,1            ; Compute one more
mult r5,r6,r2            ; Multiply
slli r4,r1,2            ; Compute address of current
sw tab(r4),r5           ; Store it
j loop2
end: trap 0             ; End program

N equ 10
tab word 0[10]

toobig: trap 0
; Quicksort

; Insertion sort

