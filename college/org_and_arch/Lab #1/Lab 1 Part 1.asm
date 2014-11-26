# Erich Viebrock
# Chirag Amin

.globl main 


.text 


main:
	# $s1 = 0x1234
	ori $s1, $0, 0x1234
	# $s1 = 0x12340000
	sll $s1, $s1, 16
	# $s1 = 0x1234ABCD
	ori $s1, $s1, 0xABCD

	ori $v0, $0, 10 
	# Sets $v0 to "10" so program will exit
syscall 
	# Exit
