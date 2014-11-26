# Lab 8, Part 2
# MIPS program that compares registers

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:

# $s0 -> A
# $s1 -> B
# $s2 -> C
# $s3 -> Z

	# load word value into register s0
	lw $s0, A
	# load word value into register s1
	lw $s1, B
	# load word value into register s2
	lw $s2, C
	# load word value into register s3
	lw $s3, Z

# if, if else, and else

	# if A > B, go to next
	bgt $s0, $s1, next
	# if A < B, go to logic2
	bgt $s1, $s0, logic2
	# add 1 and $s2, save final value in $t2
	add $t2, $s2, 1
	# if C+1 = 7, go to logic2
	beq $t2, 7, logic2
	# if none of the previous conditions are true, set Z = 3
	li $s3, 3
	# jump to done1, the beginning of switch statements
	j done1
	# second half of first if statement, if c >= 5, go to logic 1
next:	bge $s2, 5, logic1

	# logic statement for first if statement
logic1:	li $s3, 1
	# jump to done1, the beginning of switch statements
	j done1
	
	# logic statement for first if statement
logic2:	li $s3, 2
	# jump to done1, the beginning of switch statements
	j done1

# switch statements

	# First switch statement
done1:	beq $s3, 1, case1
	# Second switch statement
	beq $s3, 2, case2
	# Third switch statement
	beq $s3, 3, case3
	# Default statement
	li $s3, 0
	# jump to done2
	j done2

	# load -1 into $s3
case1:	li $s3, -1
	# jump to done2	
	j done2

	# Second switch statement
case2:	li $s3, -2
	# jump to done2
	j done2

	# Third switch statement
case3:	li $s3, -3
	# jump to done2
	j done2
	
	# save value in $s3 into Z
done2:	sw $s3, Z

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

# declare 'A' as a word, with initial value 10
A:	.word 10
# declare 'B' as a word, with initial value 15
B:	.word 15
# declare 'C' as a word, with initial value 5
C:	.word 5
# declare 'Z' as a word, with initial value 0
Z:	.word 0
