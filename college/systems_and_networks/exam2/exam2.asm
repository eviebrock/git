# Exam 2

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:	# A
	li $t3 65
	# Z
	li $t4 90
	# a
	li $t5 97
	# z
	li $t6 122
	li $t8 13
	li $t9 26

	# put address of 'orig' into $t1, pointer
	la $t1, orig
	# load character value of orig into $t0, at address of $t1
	lb $t0, 0($t1)
	# put address of 'new' into $t1, pointer
	la $t7, new
	# load null into $t2 for comparison
	li $t2, 0

	# increment through string until null is found
	# if null is found, jump to 'done'
	# $t0 = letter value of memory address saved in $t1

	# compare letter stored in $t0
if1:	bge $t0, $t3, if2
	j elsif1
if2:	ble $t0, $t4, cond1

elsif1:	bge $t0, $t5, elsif2
	j else
elsif2:	ble $t0, $t6, cond2

else:	sb $t0, 0($t7)		
	# increment memory of orig address by 1
	add $t1, $t1, 1
	# increment memory of new address by 1
	add $t7, $t7, 1		
	# load new letter after incrementing memory address
	lb $t0, 0($t1)
	# if $t0 is null, we reached end of string. jump to notFound
	beq $t0, $t2, fin
	# jump back to initial comparison
	j if1



cond1:	sub $t0, $t0, $t3
	add $t0, $t0, $t8
	div $t0, $t0, $t9
	mfhi $t0
	add $t0, $t0, $t3
	sb $t0, 0($t7)

	# increment memory of orig address by 1
	add $t1, $t1, 1
	# increment memory of new address by 1
	add $t7, $t7, 1		
	# load new letter after incrementing memory address
	lb $t0, 0($t1)
	j if1

cond2:	sub $t0, $t0, $t4
	add $t0, $t0, $t8
	div $t0, $t0, $t9
	mfhi $t0
	add $t0, $t0, $t4
	sb $t0, 0($t7)

	# increment memory of orig address by 1
	add $t1, $t1, 1
	# increment memory of new address by 1t
	add $t7, $t7, 1		
	# load new letter after incrementing memory address
	lb $t0, 0($t1)

	j if1

fin:	sb $t2, 0($t7)

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, output1
	# make syscall to perform output command
	syscall

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, orig
	# make syscall to perform output command
	syscall
	
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, output2
	# make syscall to perform output command
	syscall

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, new
	# make syscall to perform output command
	syscall


end:	# end of program

# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"
	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)

# Space for the variables

output1:.asciiz "Original string: "
output2:.asciiz "\nDecoded string: "
orig:	.asciiz "Gvtre Ebne!"
new:.space 100
