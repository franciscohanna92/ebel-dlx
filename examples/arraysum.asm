; Sum of an array
add r1,r0,r0    ; r1 is counter
add r2,r0,r0    ; r2 is sum
addi r3,r0,N	;  counter
next: 
beqz r3,end     ; jump to end
slli r4, r3, 2	; word size 
subi  r4, r4, 4
lw r5, tab(r4)  ; load current
add r2,r2,r5    ; addition
addi r3, r3, -1
j next          ; next iteration
end: trap 0     ; end

data org
N equ (tabfin - tab)/4;  
tab word 1,2,3,4,5
tabfin:
