# Lab 8, Part 3
# MIPS program that practices loops

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:

# Load 4 byte value from Z into $s0
# use $t0 to hold variable for incrementing

	# load word value into register s0
	lw $s0, Z
	# create temporary variable (register) i, set initially to 0
	li $t0, 0

# compare $t0 > 9, if not, do loop logic
# add 1 to 'i' ($t0)
# add 1 to $s0, register used to later modify Z

	# if i is greater than 9, go to start2
start1: bgt $t0, 9 start2
	# add 1 to i
	add $t0, 1
	# add 1 to Z
	add $s0, 1
	# go back to start1, compare conditions again
	j start1

# compare if $s0 > 0
# while $s0 <= 0, subtract 1 from $s0
# when $s0 < 0, jump to start3i, the do loop 

	# if Z is greater than 0, go to loop2
start2:	bgt $s0, 0, loop2
	# if Z is not greater than 0, go to start3
	j start3i
	# subtract 1 from Z
loop2:	sub $s0, 1
	# go back to start2, compare conditions again	
	j start2

# use start3i because do loops perform loop at least once,
# regardless if statement after while is true or false
# compute logic while $s0 < 10

	# compute logic once automatically
start3i:add $s0, 1
	# if Z is greater than 8, go to end
start3:	bgt $s0, 8, end
	# add 1 to Z
loop3:	add $s0, 1
	# go back to start3, compare conditions again
	j start3

end:	sw $s0, Z

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

# declare 'Z' as a word, with initial value 5
Z:	.word 5
