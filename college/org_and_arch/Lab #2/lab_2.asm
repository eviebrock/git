# Erich Viebrock
# Jason Lim


.globl main 



.text 



main:
	# load 8 into $v0 to read sting
        li $v0, 8
	# load adress of user input into $a0
	la $a0, input
	syscall

	# load 4 into $v0 to print sting
	li $v0, 4
	#load address in string into $a0
	la $a0, input
	syscall

	# place address of $a0 in $t0
	#or $s4, $a0, $zero

	# initialize counter at 0
	li $t5, 1

	#XXX?
	li $s0, 0xFF
	#XX?X
	li $s1, 0xFF00
	#X?XX
	li $s2, 0xFF0000
	#?XXX
	li $s3, 0xFF000000

	# XXX_
	li $t6, 0x20
	# XX_X
	li $t7, 0x2000
	# X_XX
	li $t8, 0x200000
	# _XXX
	li $t9, 0x20000000

	#XXX.
	li $s4, 0x2E
	#XX.X
	li $s5, 0x2E00
	#X.XX
	li $s6, 0x2E0000
	#.XXX
	li $s7, 0x2E000000

loop:	# load word into register
	lw $t0, 0($a0)

	#XXX?
	and $t1, $t0, $s0
	#XX?X
	and $t2, $t0, $s1
	#X?XX
	and $t3, $t0, $s2
	#?XXX
	and $t4, $t0, $s3
	
	beq $t1, $s4, done
	beq $t2, $s5, done
	beq $t3, $s6, done
	beq $t4, $s7, done

	beq $t1, $t6, adder1
check2: beq $t2, $t7, adder2
check3: beq $t3, $t8, adder3
check4: beq $t4, $t9, adder4
	
	#increment to next 4 bytes
	addi $a0, $a0, 4
	j loop

adder1: addi $t5, $t5, 1
	j check2
adder2: addi $t5, $t5, 1
	j check3
adder3: addi $t5, $t5, 1
	j check4
adder4: addi $t5, $t5, 1
	# increment to next 4 bytes
	addi $a0, $a0, 4
	# repeat loop
	j loop
	
done:	# print counter
	li $v0, 1
	# load address of register
	move $a0, $t5
	syscall

	# Sets $v0 to "10" so program will exit
	ori $v0, $0, 10 
	syscall
.data

input:	.asciiz " "