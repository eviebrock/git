# A Demonstration of some simple MIPS instructions

# used to test QtSPIM


.globl main 


.text 


main:

ori $t2, $0, 25 

ori $t3, $0, 12

add $t4, $t2, $t3


sub $t5, $t2, $t3


ori $v0, $0, 10 
# Sets $v0 to "10" so program will exit

syscall 
# Exit
