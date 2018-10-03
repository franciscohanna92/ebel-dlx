;;-----------------------------------------------------------------
;;-- Simple bubble sort
;;-- Shows inverting loops
;;-- By Etienne Bergeron et Eric Lesage
;;-- 2001-02-14

; for(  i=0; i<N-1; i++ ) {             //-- for1
;     Ind_Min = i;
;
;     for( j=i+1; j<N; j++ )            //-- for2
;          if( tab[j] < tab[Ind_Min] )  //-- if1
;              Ind_Min = j;
;
;     if( i != Ind_Min ) {              //-- if2
;       tempo = tab[i];
;       tab[i] = tab[Ind_Min];
;       tab[Ind_Min] = tempo;
;     }
;  }


; Register allocation
;--------------------
; i -->  r1
; j -->  r2
; IndMin --> r3
;-- The following register do not traverse basic blocks in the flowgraph.
;-- >= r10   Dynamic register allocation for temporary computations.


code    org 0                                                  
;------------
for1_init:     ADD   r1, r0, r0
               J     for1_test
		
for1_body:     ADDI  r3, r1, 0
for2_init:     ADDI  r2, r1, 1
               J     for2_test
for2_body:     
if1_test:      SLLI  r10, r2, 2
               LW    r10, tab(r10)
			   SLLI  r11, r3, 2
               LW    r11, tab(r11)
               SLT   r12, r10, r11
               BEQZ  r12, if1_end
		
if1_true:      ADD   r3, r2, r0
if1_end:       
for2_incr:     ADDI  r2, r2, 1      
for2_test:     SLTI  r10, r2, N 
               BNEZ  r10, for2_body
		
if2_test:      SNE   r10, r1, r3
               BEQZ  r10, if2_end
		
if2_true:      SLLI  r13, r1, 2
	           SLLI  r14, r3, 2
	           LW    r10, tab(r13)
               LW    r11, tab(r14)
               SW    tab(r13), r11
               SW    tab(r14), r10
if2_end:       
for1_incr:     ADDI  r1, r1, 1
for1_test:     SLTI  r11, r1, N_1
               BNEZ  r11, for1_body
exit:          TRAP  0
   

data    org 0 
;------------
N   EQU (tab_end-tab)/4 ;;-- N
N_1 EQU N - 1           ;;-- N-1
tab       word 26,21,84,71,1,4,16,31,15,56,8,20,34,6,43,28,66,13,7,32,2,3
tab_end:
