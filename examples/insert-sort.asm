;; Insertion sort of a table
code org

		addi r1, r0, N

loop1: 
		beqz r1, fin1
		addi r2, r0, N-1
loop2:	
		beqz r2, fin2

		lb r3, tab( r2 )
		addi r5, r2, -1
		lb r4, tab( r5 )
		
		slt r6, r3, r4
		beqz r6, cont

swap:	sb tab( r2 ), r4
		sb tab( r5 ), r3

cont:			
		addi r2, r2, -1
		j loop2
fin2:		
		addi r1, r1, -1			
		j loop1
fin1:	trap 0


data org

N equ (tabfin - tab)
tab byte ((5,4,9,1,10,67,15,542,12,6,82,13)[5],56)[2]
tabfin:
