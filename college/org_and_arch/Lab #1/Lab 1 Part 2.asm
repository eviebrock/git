# Erich Viebrock
# Chirag Amin

.globl main 



.text 



main:

	ori $s1, $0, 0x1
	sll $s1, $s1, 4
	ori $s1, $s1, 0x2
	sll $s1, $s1, 4
	ori $s1, $s1, 0x3
	sll $s1, $s1, 4
	ori $s1, $s1, 0x4
	sll $s1, $s1, 4
	ori $s1, $s1, 0xA
	sll $s1, $s1, 4
	ori $s1, $s1, 0xB
	sll $s1, $s1, 4
	ori $s1, $s1, 0xC
	sll $s1, $s1, 4
	ori $s1, $s1, 0xD

	ori $v0, $0, 10 
	# Sets $v0 to "10" so program will exit

syscall 
	# Exit
