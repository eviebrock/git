#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "your_functions.h"

// Selection sort algorithm
// Arguments:
//  (1) Pointer to start of array
//  (2) Number of elements in array
// Return value: None

void selectionSort(int *array_start, int array_size)
{
  	printf("Using selection sort algorithm...\n");
	
	int i, j, min;
	for (i = 0; i < array_size-1; i++)
	{
		min = i; // sets initial index to min
		for (j = i+1; j < array_size; j++) // steps through array with different variable to compare to next element
		{
			if (array_start[j] < array_start[min]) // compares second array with min
			{
				min = j; // if true, sets j to min
			}
		}
		int temp; // create temporary variable to allow swapping
		temp = array_start[i]; // gives value of index 'i' to temp
		array_start[i] = array_start[min]; // changes value of 'i' to min
		array_start[min] = temp; // gives min value of i
	}
	
  	return;

}



/*
void bubbleSort(int *array_start, int array_size)
{
	printf("Using bubble sort algorithm...\n");

	int temp;
	 
	for (int i = (array_size - 1); i > 0; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			if (array_start[j-1] > array_start[j])
			{
		      		temp = array_start[j-1];
				array_start[j-1] = array_start[j];
				array_start[j] = temp;
		    	}
		}
	}
  
  	return;
}
*/



// Merge sort algorithm
// Arguments:
//  (1) Pointer to start of array
//  (2) Number of elements in array
// Return value: None
void mergeSort(int *array_start, int *temp_array_start, int array_size)
{
  	printf("Using merge sort algorithm...\n");

	//code

  	// Note that I have already allocated a temporary
  	// array for you to use in your merge sort algorithm

  	// Feel free to create other helper functions
  	// to assist with the merge sort


  	return;
}
/*
else if(strcmp(argv[1], "selection") == 0)
{
	selectionSort(my_array, ARRAY_SIZE);
}
*/
