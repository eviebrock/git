// Erich Viebrock

#include <stdlib.h>
#include <stdio.h>

int rand1 = 21;
int rand2 = 20;

int main(void)
{
	printf("Welcome to Wythoff's Game!\n");
	printf("Author: Erich Viebrock\n\n");
	printf("Enter two positive numbers to initialize the random number generator.\n");	
	printf("Number 1: ");
	scanf("%d", &rand1);
	printf("Number 2: ");
	scanf("%d", &rand2);

	while (rand1 <= 0 || rand2 <= 0)
	{
		printf("Invalid input!\n\n");
		printf("Enter two positive numbers to initialize the random number generator.\n");
		printf("Number 1: ");
		scanf("%d", &rand1);
		printf("Number 2: ");
		scanf("%d", &rand2);
	}
	
	// rand nums, tie to aMarbles & bMarbles
	int get_random()
	{
		rand1 = 36969 * (rand1 & 65535) + (rand1 >> 16);
		rand2 = 36969 * (rand2 & 65535) + (rand2 >> 16);
		return (unsigned int) ((rand1 << 16) + rand2) % 50;
	}

	// heap totals
	int aMarbles = get_random();
	int bMarbles = get_random();

	// user input variables
	int numChoice;
	char heapChoice;

	// tmp variable used when pulling from heap c
	int least;

	while (aMarbles > 0 || bMarbles > 0)
	{
		printf("\nHeapA   HeapB\n");
		printf("-------------\n");
		printf(" %d      %d\n\n", aMarbles, bMarbles);
		printf("What heap would you like to draw from? Enter 'a', 'b', or 'c' for both: ");
		scanf(" %c", &heapChoice);
		while ((heapChoice == 'a' || heapChoice == 'c') && aMarbles == 0)
		{
			printf("Invalid input!\n");
			printf("What heap would you like to draw from? Enter 'a', 'b', or 'c' for both: ");
			scanf(" %c", &heapChoice);
		}
		while ((heapChoice == 'b' || heapChoice == 'c') && bMarbles == 0)
		{
			printf("Invalid input!\n");
			printf("What heap would you like to draw from? Enter 'a', 'b', or 'c' for both: ");
			scanf(" %c", &heapChoice);
		}
		if (heapChoice == 'a')
		{
			printf("How many marbles do you want to remove from Heap A? ");
			scanf("%d", &numChoice);
			if (aMarbles > 1)
			{
				while (numChoice > (aMarbles/2) || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap A? ");
					scanf("%d", &numChoice);
				}
			}
			else
			{
				while (numChoice > aMarbles || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap A? ");
					scanf("%d", &numChoice);
				}
			}
			aMarbles = aMarbles - numChoice;
			// ai
			if (aMarbles > 0 || bMarbles > 0)
			{
				if (aMarbles == 0)
				{
					if (bMarbles == 1)
					{
						bMarbles--;
						printf("Computer selected to remove 1 from Heap B.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (bMarbles/2));
						printf("Computer selected to remove %d from Heap B.\n", numChoice);
						bMarbles = bMarbles - numChoice;
					}
				}
				else if (bMarbles == 0)
				{
					if (aMarbles == 1)
					{
						aMarbles--;
						printf("Computer selected to remove 1 from Heap B.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (aMarbles/2));
						printf("Computer selected to remove %d from Heap A.\n", numChoice);
						aMarbles = aMarbles - numChoice;
					}
				}
				else
				{
					heapChoice = get_random();
					if (heapChoice < 10) //heap a
					{
						if (aMarbles == 1)
						{
							aMarbles--;
							printf("Computer selected to remove 1 from Heap 							A.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (aMarbles/2));
							printf("Computer selected to remove %d from Heap A.\n", numChoice);
							aMarbles = aMarbles - numChoice;
						}
					}
					else if (heapChoice > 30) //heap b
					{
						if (bMarbles == 1)
						{
							bMarbles--;
							printf("Computer selected to remove 1 from Heap B.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (bMarbles/2));
							printf("Computer selected to remove %d from Heap B.\n", numChoice);
							bMarbles = bMarbles - numChoice;
						}
					}
					else //heap c
					{
						if (aMarbles > bMarbles)
						{
							least = bMarbles;
						}
						else if (bMarbles > aMarbles)
						{
							least = aMarbles;
						}
						else
						{
							least = aMarbles;
						}
						if (least == 1)
						{
							aMarbles--;
							bMarbles--;
							printf("Computer selected to remove 1 from Heap C.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (least/2));
							printf("Computer selected to remove %d from Heap C\n", numChoice);
							aMarbles = aMarbles - numChoice;
							bMarbles = bMarbles - numChoice;
						}
					}
				}
			}
		}
		else if (heapChoice == 'b')
		{
			printf("How many marbles do you want to remove from Heap B? ");
			scanf("%d", &numChoice);
			if (bMarbles > 1)
			{
				while (numChoice > (bMarbles/2) || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap B? ");
					scanf("%d", &numChoice);
				}
			}
			else
			{
				while (numChoice > bMarbles || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap B? ");
					scanf("%d", &numChoice);
				}
			}
			bMarbles = bMarbles - numChoice;
			// ai
			if (aMarbles > 0 || bMarbles > 0)
			{
				if (aMarbles == 0)
				{
					if (bMarbles == 1)
					{
						bMarbles--;
						printf("Computer selected to remove 1 from Heap B.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (bMarbles/2));
						printf("Computer selected to remove %d from Heap B.\n", numChoice);
						bMarbles = bMarbles - numChoice;
					}
				}
				else if (bMarbles == 0)
				{
					if (aMarbles == 1)
					{
						aMarbles--;
						printf("Computer selected to remove 1 from Heap A.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (aMarbles/2));
						printf("Computer selected to remove %d from Heap A.\n", 						numChoice);
						aMarbles = aMarbles - numChoice;
					}
				}
				else
				{
					heapChoice = get_random();
					if (heapChoice < 10) //heap a
					{
						if (aMarbles == 1)
						{
							aMarbles--;
							printf("Computer selected to remove 1 from Heap 							A.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (aMarbles/2));
							printf("Computer selected to remove %d from Heap A.\n", numChoice);
							aMarbles = aMarbles - numChoice;
						}
					}
					else if (heapChoice > 30) //heap b
					{
						if (bMarbles == 1)
						{
							bMarbles--;
							printf("Computer selected to remove 1 from Heap B.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (bMarbles/2));
							printf("Computer selected to remove %d from Heap B.\n", numChoice);
							bMarbles = bMarbles - numChoice;
						}
					}
					else //heap c
					{
						if (aMarbles > bMarbles)
						{
							least = bMarbles;
						}
						else if (bMarbles > aMarbles)
						{
							least = aMarbles;
						}
						else
						{
							least = aMarbles;
						}
						if (least == 1)
						{
							aMarbles--;
							bMarbles--;
							printf("Computer selected to remove 1 from Heap C.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (least/2));
							printf("Computer selected to remove %d from Heap C.\n", numChoice);
							aMarbles = aMarbles - numChoice;
							bMarbles = bMarbles - numChoice;
						}
					}
				}
			}
		}
		else if (heapChoice == 'c')
		{
			printf("How many marbles do you want to remove from Heap C? ");
			scanf("%d", &numChoice);
			if (aMarbles > bMarbles)
			{
				
				while (numChoice > (bMarbles/2) || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap C? ");
					scanf("%d", &numChoice);
				}
			}
			else if (bMarbles > aMarbles)
			{
				while (numChoice > (aMarbles/2) || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap C? ");
					scanf("%d", &numChoice);
				}
			}
			else
			{
				while (numChoice > (aMarbles/2) || numChoice <= 0)
				{
					printf("Invalid input!\n");
					printf("How many marbles do you want to remove from Heap C? ");
					scanf("%d", &numChoice);
				}
			}			
			aMarbles = aMarbles - numChoice;
			bMarbles = bMarbles - numChoice;
			// ai
			if (aMarbles > 0 || bMarbles > 0)
			{
				if (aMarbles == 0)
				{
					if (bMarbles == 1)
					{
						bMarbles--;
						printf("Computer selected to remove 1 from Heap B.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (bMarbles/2));
						printf("Computer selected to remove %d from Heap B.\n", numChoice);
						bMarbles = bMarbles - numChoice;
					}
				}
				else if (bMarbles == 0)
				{
					if (aMarbles == 1)
					{
						aMarbles--;
						printf("Computer selected to remove 1 from Heap A.\n");
					}
					else
					{
						do {
							numChoice = get_random()/4;
						} while (numChoice <= 0 || numChoice > (aMarbles/2));
						printf("Computer selected to remove %d from Heap A.\n", numChoice);
						aMarbles = aMarbles - numChoice;
					}
				}
				else
				{
					heapChoice = get_random();
					if (heapChoice < 10) //heap a
					{
						if (aMarbles == 1)
						{
							aMarbles--;
							printf("Computer selected to remove 1 from Heap A.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (aMarbles/2));
							printf("Computer selected to remove %d from Heap A.\n", numChoice);
							aMarbles = aMarbles - numChoice;
						}
					}
					else if (heapChoice > 30) //heap b
					{
						if (bMarbles == 1)
						{
							bMarbles--;
							printf("Computer selected to remove 1 from Heap B.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (bMarbles/2));
							printf("Computer selected to remove %d from Heap B.\n", numChoice);
							bMarbles = bMarbles - numChoice;
						}
					}
					else //heap c
					{
						if (aMarbles > bMarbles)
						{
							least = bMarbles;
						}
						else if (bMarbles > aMarbles)
						{
							least = aMarbles;
						}
						else
						{
							least = aMarbles;
						}
						if (least == 1)
						{
							aMarbles--;
							bMarbles--;
							printf("Computer selected to remove 1 from Heap C.\n");
						}
						else
						{
							do {
								numChoice = get_random()/4;
							} while (numChoice <= 0 || numChoice > (least/2));
							printf("Computer selected to remove %d from Heap C.\n", numChoice);
							aMarbles = aMarbles - numChoice;
							bMarbles = bMarbles - numChoice;
						}
					}
				}
			}
		}
		else
		{

		}
	}
	printf("Game over!\n\n");
}
