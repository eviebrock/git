# Erich Viebrock
# Chirag Amin

.globl main 



.text 



main:

	ori $s1, $0, 0xAFEC
	andi $t0, $s1, 40960
	andi $t1, $s1, 3840
	andi $t2, $s1, 224
	andi $t3, $s1, 12

	srl $t0, $t0, 4
	sll $t1, $t1, 4
	srl $t2, $t2, 4
	sll $t3, $t3, 4

	or $s2, $s2, $t0
	or $s2, $s2, $t1
	or $s2, $s2, $t2
	or $s2, $s2, $t3

	ori $v0, $0, 10 
	# Sets $v0 to "10" so program will exit

syscall 
	# Exit