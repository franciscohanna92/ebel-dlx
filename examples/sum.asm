; Sum two registers

A equ 2
B equ 69

add r1,r0,r0    ; r1 is sum
addi r2,r0,A    ; load A into register r2
addi r3,r0,B    ; load B into register r2

add r1,r2,r3    ; calcualte A + B

end: trap 0     ; end