// Erich Viebrock
// Program reveals the mystery of how multidimensional arrays are stored

#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("\nIn this program, a two dimensional (2x2) array is declared. Arrays are declared by ");
	printf("array[row][column], which we will step \nthrough with a pointer and reveal the memory ");
	printf("address of each individual element. We will first increment the column, then \nincrement ");
	printf("the row.\n\nBelow are the memory addresses of the array:\n");	

	//array[row][col]

	int array[2][2];

	int *point1 = &array[0][0];
	int *point2 = &array[0][1];
	int *point3 = &array[1][0];
	int *point4 = &array[1][1];

	printf("\nAddress of array[0][0]: %p\n", point1);
	printf("Address of array[0][1]: %p\n", point2);
	printf("Address of array[1][0]: %p\n", point3);
	printf("Address of array[1][1]: %p\n", point4);

	printf("\nAs we suspected, a two dimensional array stores elements by incrementing the column, ");
	printf("then incrementing the row. Notice how \neach memory address increments the least ");
	printf("significant bit by a value of 4 as we move through the array. This is because we \ndeclared");
	printf(" an integer array, which stores elements in 4 bytes each. Also note when we have a least ");
	printf("significant bit of 8, the \nnext memory address's least significant bit is 'c'. This is ");
	printf("because memory addresses are stored in hexadecimal, which uses \na = 10, b = 11, c = 12, ");
	printf("d = 13 e = 14, and f = 15.\n");

	printf("\nNow, let's do the same thing, but with a three dimensional (2x2x2) array. \n\nBelow are ");
	printf("the memory address of the array:\n");

	int uhray[2][2][2];
	
	int *poynt1 = &uhray[0][0][0];
	int *poynt2 = &uhray[0][0][1];
	int *poynt3 = &uhray[0][1][0];
	int *poynt4 = &uhray[0][1][1];
	int *poynt5 = &uhray[1][0][0];
	int *poynt6 = &uhray[1][0][1];
	int *poynt7 = &uhray[1][1][0];
	int *poynt8 = &uhray[1][1][1];

	printf("\nAddress of array[0][0][0]: %p\n", poynt1);
	printf("Address of array[0][0][1]: %p\n", poynt2);
	printf("Address of array[0][1][0]: %p\n", poynt3);
	printf("Address of array[0][1][1]: %p\n", poynt4);
	printf("Address of array[1][0][0]: %p\n", poynt5);
	printf("Address of array[1][0][1]: %p\n", poynt6);
	printf("Address of array[1][1][0]: %p\n", poynt7);
	printf("Address of array[1][1][1]: %p\n", poynt8);

	printf("\nNotice how memory is stored in the same fashion as the two dimensional array. Therefore, ");
	printf("we can conclude the rightmost \nelement in the array is incremented first, then increments ");
	printf("from right to left. Although we only tested two and three \ndimensional arrays, the same ");
	printf("concept should apply to an array of any dimension.\n\n");

	return 0;
}
