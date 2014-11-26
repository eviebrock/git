# Lab 8, Part 5
# MIPS program that practices loops

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
		
# t1 -> string
# make system call to print string, in this case
# output 'output1', the initial user prompt
# load first memory address of output1, then
# increment through string until null character
# is reached

	# put address of string into $t1, pointer
	la $t1, string
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, output1
	# make syscall to perform output command
	syscall

# make system call to read string from prompt
# string max size of 256 bytes
# load first memory address of string, then
# increment through string until null character
# is reached

	# load 8 into $v0 to read string
	li $v0, 8
	# load address of user input into $a0
	la $a0, string
	# load the max size of the string to $a1, includes "/0"
	li $a1, 256
	# make syscall to save string to register	
	syscall

# $t0 = letter value of memory address saved in $t1
# $t2 is used to compare letter in string to 't'
# $t3 is used to comapre letter in string to null character

	# load character value into $t0, at address of $t1, increment $t1
	lb $t0, 0($t1)
	# load 't' into $t2 for comparison
	li $t2, 't'
	# load null character into $t3 for comparison
	li $t3, 0

# increment through string until t is found
# if t isn't found, jump to 'nope'
# $t0 = letter value of memory address saved in $t1

	# compare letter stored in $t0 to 't'. if true, jump to found
search:	beq $t0, $t2, found
	# increment memory address by 1
	add $t1, $t1, 1		
	# load new letter after incrementing memory address
	lb $t0, 0($t1)
	# if $t0 is null, we reached end of string. jump to notFound
	beq $t0, $t3, nope
	# jump back to initial comparison
	j search

# case if found 't' in string. use syscall to print string, then
# syscall to print the actual t found in string, rather than
# t hard coded in intial printed string

found:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, output2
	# make syscall to perform output command
	syscall
	# load 11 into $v0 to print character
	li $v0, 11
	# load character found
	move $a0, $t0
	# make syscall to perform output command
	syscall
	# jump to end
	j end

# case if unfound 't' in string. use syscall to print string,
# then reach end of program

nope:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, output3
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

# declare 256 bytes of storage to hold array up to 256 characters
string:	.space 256
# Initial user prompt
output1:.asciiz "Enter a word: "
# Prompt if found
output2:.asciiz "Matching character is: " 
# Prompt if not found
output3:.asciiz "No match found.\n"
