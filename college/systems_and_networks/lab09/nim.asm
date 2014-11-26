# Erich Viebrock

.globl main
.text

# needs at least 3 subroutines, for example
	# rand_num
	# print_game
	# user_input

main:

# Perform initial user prompts
# Welcome to game, display author
# Use tmp registers to store letters for
# comparisons
# $t2 = Heap A
# $t3 = Heap B
# $t4 = Heap C

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, initOutput1
	# make syscall to perform output command
	syscall
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, initOutput2
	# make syscall to perform output command
	syscall
	# load 'a' into $t2 for comparison
	li $t2, 'a'
	# load 'b' into $t2 for comparison
	li $t3, 'b'
	# load 'c' into $t2 for comparison
	li $t4, 'c'
	
# Prompt user for first random number
# Obtain first number
# Prompt user for second random number
# Obtain second random number

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, randNumPrompt
	# make syscall to perform output command
	syscall
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, randNum1
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t0 -> aMarbles
	move $t0, $v0
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, randNum2
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t0 -> aMarbles
	move $t1, $v0

	###########################
	# BEGIN RAND NUM FUNCTION #
	###########################

	#int get_random()
	#{
	#	rand1 = 36969 * (rand1 & 65535) + (rand1 >> 16);
	#	rand2 = 36969 * (rand2 & 65535) + (rand2 >> 16);
	#	return (unsigned int) ((rand1 << 16) + rand2) % 50;
	#}
	
	# use $t5 to hold rand1 shifted right 16 bits
	srl $t6, $t0, 16
	# load 65535 into register $t5
	li $t5, 65535
	# and the binary bits of $t0 and $t5
	and $t0, $t0, $t5
	# load 36969 into register $t5
	li $t5, 36969
	# multiply $t0 and $t5
	mul $t0, $t0, $t5
	# add $t0 and $t5
	add $t0, $t0, $t6
	
	# use $t5 to hold rand1 shifted right 16 bits
	srl $t6, $t1, 16
	# load 65535 into register $t5
	li $t5, 65535
	# and the binary bits of $t0 and $t5
	and $t1, $t1, $t5
	# load 36969 into register $t5
	li $t5, 36969
	# multiply $t0 and $t5
	mul $t1, $t1, $t5
	# add $t0 and $t5
	add $t1, $t1, $t6
	
	# shift $t0 16 bits to the left	
	sll $t0, $t0, 16
	# add $t0 and $t1, save in $t0
	add $t0, $t0, $t1
	# load 50 into register $t5
	li $t5, 50
	# divide sum by 50
	divu $t0, $t0, $t5
	# sets $t0 to modulus from previous division
	mfhi $t0

	# save value in $t0 to $s0
	move $s0, $t0

	# use $t5 to hold rand1 shifted right 16 bits
	srl $t6, $t0, 16
	# load 65535 into register $t5
	li $t5, 65535
	# and the binary bits of $t0 and $t5
	and $t0, $t0, $t5
	# load 36969 into register $t5
	li $t5, 36969
	# multiply $t0 and $t5
	mul $t0, $t0, $t5
	# add $t0 and $t5
	add $t0, $t0, $t6
	
	# use $t5 to hold rand1 shifted right 16 bits
	srl $t6, $t1, 16
	# load 65535 into register $t5
	li $t5, 65535
	# and the binary bits of $t0 and $t5
	and $t1, $t1, $t5
	# load 36969 into register $t5
	li $t5, 36969
	# multiply $t0 and $t5
	mul $t1, $t1, $t5
	# add $t0 and $t5
	add $t1, $t1, $t6
	
	# shift $t0 16 bits to the left	
	sll $t0, $t0, 16
	# add $t0 and $t1, save in $t0
	add $t0, $t0, $t1
	# load 50 into register $t5
	li $t5, 50
	# divide sum by 50
	divu $t0, $t0, $t5
	# sets $t0 to modulus from previous division
	mfhi $t0
		
	# save value in $t0 to $s0
	move $s1, $t0

	###########################
	# END RAND NUMS FUNCTIONS #
	###########################	

# Print the game board. Displays each heap with
# heap titles and respective marble count

board:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, heapTitles
	# make syscall to perform output command
	syscall
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, divideLine
	# make syscall to perform output command
	syscall
	# load 1 into $v0 to output integer
	li $v0, 1
	# move value in $s0 to $a0	
	move $a0, $s0
	# make syscall to output integer
	syscall
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, separateTotals
	# make syscall to perform output command
	syscall
	# load 1 into $v0 to output integer
	li $v0, 1
	# move value in $s1 to $a0
	move $a0, $s1
	# make syscall to output integer
	syscall
	# check if game is over
	bgt $s0, 0, input1
	# check if game is over
	bgt $s1, 0, input1	
	# jump to exit function
	j exit

# Prompt player 1 which heap to pick from

input1:	############	
	# PLAYER 1 #
	############

	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, heapChoiceAsk1
	# make syscall to perform output command
	syscall
	# load 8 into $v0 to read string
	li $v0, 8
	# load address of user input into $a0
	la $a0, heapChoice
	# load the max size of the string to $a1, includes "/0"
	li $a1, 10
	# make syscall to save string to register	
	syscall
	# put address of string into $t1, pointer
	la $t5, heapChoice
	# load character value into $t6, at address of $t5
	lb $t6, 0($t5)
	# compare letter stored in $t0 to 'a'. if true, jump to ??? -> heap a stuff
	beq $t6, $t2, heapA1
	# compare letter stored in $t0 to 'b'. if true, jump to ??? -> heap b stuff
	beq $t6, $t3, heapB1
	# compare letter stored in $t0 to 'c'. if true, jump to ??? -> heap acstuff
	beq $t6, $t4, heapC1

# Prompt player 2 which heap to pick from

input2:	############	
	# PLAYER 2 #
	############
	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, heapChoiceAsk2
	# make syscall to perform output command
	syscall
	# load 8 into $v0 to read string
	li $v0, 8
	# load address of user input into $a0
	la $a0, heapChoice
	# load the max size of the string to $a1, includes "/0"
	li $a1, 10
	# make syscall to save string to register	
	syscall
	# put address of string into $t1, pointer
	la $t5, heapChoice
	# load character value into $t6, at address of $t5
	lb $t6, 0($t5)
	# compare letter stored in $t0 to 'a'. if true, jump to ??? -> heap a stuff
	beq $t6, $t2, heapA2
	# compare letter stored in $t0 to 'b'. if true, jump to ??? -> heap b stuff
	beq $t6, $t3, heapB2
	# compare letter stored in $t0 to 'c'. if true, jump to ??? -> heap acstuff
	beq $t6, $t4, heapC2

heapA1:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceA
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> aMarbles
	move $t7, $v0
	# subtract marbles from heap a total
	sub $s0, $s0, $t7
	# jump to board
	j input2

heapB1:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceB
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> bMarbles
	move $t7, $v0
	# subtract marbles from heap b total
	sub $s1, $s1, $t7
	# jump to board
	j input2
		
heapC1:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceC
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> cMarbles
	move $t7, $v0
	# subtract marbles from heap a total
	sub $s0, $s0, $t7
	# subtract marbles from heap b total
	sub $s1, $s1, $t7
	# jump to board
	j input2

heapA2:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceA
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> aMarbles
	move $t7, $v0
	# subtract marbles from heap a total
	sub $s0, $s0, $t7
	# jump to board
	j board

heapB2:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceB
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> bMarbles
	move $t7, $v0
	# subtract marbles from heap b total
	sub $s1, $s1, $t7
	# jump to board
	j board
		
heapC2:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, numChoiceC
	# make syscall to perform output command
	syscall
	# load 5 into $v0 to read integer
	li $v0, 5
	# make syscall to read integer	
	syscall
	# move value in $v0 to $t7 -> cMarbles
	move $t7, $v0
	# subtract marbles from heap a total
	sub $s0, $s0, $t7
	# subtract marbles from heap b total
	sub $s1, $s1, $t7
	# jump to board
	j board

exit:	# load 4 into $v0 to print string
	li $v0, 4
	# load address of string to be printed
	la $a0, gameOver
	# make syscall to perform output command
	syscall

# load 10 into $v0 to end program
li $v0 10
# make syscall to end program
syscall

# memory structures are placed after .data assembler directive
.data
# create string to output welcome message
initOutput1:	.asciiz "Welcome to Wythoff's Game!\n"
# create string to output author
initOutput2:	.asciiz "Author: Erich Viebrock\n"
# create string to prompt user for positive numbers
randNumPrompt:	.asciiz "\nEnter two positive numbers to initialize the random number generator.\n"
# create string for first random number
randNum1:	.asciiz "Number 1: "
# create string for second random number
randNum2:	.asciiz "Number 2: "
# create string to display heap titles
heapTitles:	.asciiz "\nHeapA   HeapB\n"
# create string to divide titles from totals
divideLine:	.asciiz "---------------------\n"
# create string to space out heap totals
separateTotals:	.asciiz "             "
# create string to ask user which heap to draw from
heapChoiceAsk1:	.asciiz "\n\nPlayer 1, what heap would you like to draw from? Enter 'a', 'b', or 'c' for both: "
# create string to ask user which heap to draw from
heapChoiceAsk2:	.asciiz "Player 2, what heap would you like to draw from? Enter 'a', 'b', or 'c' for both: "
# create 1 byte array to store a single character, the user's heap choice
heapChoice:	.space 10
# create string to ask user how many marbles they want to take from heap a
numChoiceA:	.asciiz "How many marbles do you want to remove from Heap A? "
# create string to ask user how many marbles they want to take from heap b
numChoiceB:	.asciiz "How many marbles do you want to remove from Heap B? "
# create string to ask user how many marbles they want to take from heap c
numChoiceC:	.asciiz "How many marbles do you want to remove from Heap C? "
# game over prompt
gameOver:	.asciiz "\n\nGame over!"
