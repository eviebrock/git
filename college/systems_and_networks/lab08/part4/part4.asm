# Lab 8, Part 4
# MIPS program that practices loops

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:

# load integer array values, null integer array values,
# and two variables
# use $t0 to increment through for loop
# use $t1 to increment through memory addresses

	# load int value into register s0
	lw $s0, C
	# create temporary variable 'i' with initial value 0
	li $t0, 0
	# create temporary variable 'j' with initial value 4
	li $t1, 4
	# put first element address of arrayA into $t2
	la $t2, arrayA
	# put address of arrayB into $t3
	la $t3, arrayB

# load integer value to $t4, $t5 from 
# memory address of $t2, $t3, respectively
# then add integer values, and save result

	# compute at index 0
	# pull array element at address j of arrayA, save in $t4
	lw $t4, 0($t2)
	# pull array element at address j of arrayB, save in $t5
	lw $t5, 0($t3)
	# add B[j] & C, save A[j], 
	add $t4, $t5, $s0
	# save sum in array
	sw $t4, 0($t2)
	
# use $t0 to hold temporary variable, increment on each 
# pass through loop. increment each address by 4 bytes
# pull element from memory address, add, save sum, repeat 

	# if i > 3, exit loop
start1:	bgt $t0, 3, exit
	# add 1 to i
	add $t0, $t0, 1
	# add 4 to address of arrayA
	add $t2, $t2, $t1
	# add 4 to address of arrayB
	add $t3, $t3, $t1
	# pull array element at address j of arrayA, save in $t4
	lw $t4, 0($t2)
	# pull array element at address j of arrayB, save in $t5
	lw $t5, 0($t3)
	# add B[j] & C, save A[j], 
	add $t4, $t5, $s0
	# save sum in array
	sw $t4, 0($t2)
	# repeat loop
	j start1

# perform same basic operation, but with a while
# loop, and multiplication. increment memory addresses,
# pull element from address, modify element, then save
# modified element to respective address

	# subtract 1 from 'i'
exit:	sub $t0, 1
	# register holds value 2
	li $t6, 2
	# if i is greater than or equal to 0, go to beginning of loop
next:	bge $t0, -1, start2
	# exit loop
	j end
start2:	# pull array element at address j of arrayA, save in $t4
	lw $t4, 0($t2)
	# multiply array element of arrayA with 2
	mul $t4, $t4, $t6
	# save answer in array
	sw $t4, 0($t2)
	# subtract 4 from address of arrayA
	sub $t2, $t2, $t1
	# subtract 1 from i
	sub $t0, 1
	# repeat loop
	j next
end:	#yolo

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

# declare 20 bytes of storage to hold array of 5 integers
arrayA:.space 20
	# declare 5 element array to store values of 1, 2, 3, 4, and 5
arrayB:	.word 1, 2, 3, 4, 5
# declare 'C' as a word, with initial value 12
C:	.word 12
