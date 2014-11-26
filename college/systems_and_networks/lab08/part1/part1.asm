# Lab 8, Part 1
# MIPS program that calculates equations

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:

# In this block, initial values are set
# A = $t1
# B = $t2
# C = $t3
# D = $t4
# E = $t5
# F = $t6
# Z = $t7

	# load value 10 into A
	ori $t1, $0, 10
	# load value 15 into B
	ori $t2, $0, 15
	# load value 5 into C
	ori $t3, $0, 5
	# load value 2 into D	
	ori $t4, $0, 2
	# load value 7 into E
	ori $t5, $0, 7
	# load value -3 into F. use load immediate command to load negative values
	li  $t6, -3
	# load value 0 into Z
	ori $t7, $0, 0

# In this block, the arithmetic is performed
### FIRST SET OF TEMPORARY VARIABLES ###
# A+B = $s0
# C*D = $s1
# E-F = $s2
# A/C = $s3
### SECOND SET OF TEMPORARY VARIABLES ###
# $s0-$s1 = $s4
# $s4+$s2 = $s5
# $s5-$s3 = $s6

	# add A & B, save in first temporary register
	add $s0, $t1, $t2
	# multiply C & D, save in second temporary register
	mul $s1, $t3, $t4
	# subtract E & F, save in third temporary register
	sub $s2, $t5, $t6
	# divide A & C, save in fourth temporary register
	div $s3, $t1, $t3
	# subtract first and second temporary register, save in fifth temporary register
	sub $s4, $s0, $s1
	# add fifth and third temporary register, save in sixth temporary register
	add $s5, $s4, $s2
	# subtract sixth and fourth temporary register, save in seventh temporary register
	sub $s6, $s5, $s3
	# overwrite first temporary register to save final value of Z
	sw  $s6, Z

# Exit the program by meansZ of a syscall.
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
# declare 'D' as a word, with initial value 2
D:	.word 2
# declare 'E' as a word, with initial value 7
E:	.word 7
# declare 'F' as a word, with initial value -3
F:	.word -3
# declare 'Z' as a word, with initial value 0
Z:	.word 0
