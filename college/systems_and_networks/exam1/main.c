#include <stdlib.h>
#include <stdio.h>

#include "main.h"

// In this program, a "string" is a linked list of characters.
// Each object is a structure with the name "letter_obj" that
// contains a character, and a pointer to the next list item.
//
// Example:  String "UOP"
//
// -------------     -------------     --------------
// | Char: U   |     | Char: O   |     | Char: P    |
// | Next: =========>| Next: =========>| Next: NULL |
// -------------     -------------     --------------
//


int main()
{
  char filename[]="data.txt";
  char letter;
  FILE *fp = NULL;
  struct letter_obj *string = NULL;

  fp = fopen(filename, "r");
  
  if(fp == NULL)
    {
      printf("Error: Unable to open input file\n");
      return 1;
    }

  // Read in the input file one character at a time
  letter = fgetc(fp);
  while(letter != EOF)
    {
      // Add each character to a string in linked-list format
      // "string" will always stay pointing to the first character.
      string = string_append(string, letter);

      // Get another character
      letter = fgetc(fp);
    }

  // Close the file - done with input
  fclose(fp);

  // Print out the original string
  printf("Original string read from file: \n");
  string_print(string);
  printf("\n");

  // Modify the string, dropping all vowels from it
  string = string_drop_vowels(string);
  
  // Print out the modified string
  printf("Modified string with vowels dropped: \n");
  string_print(string);
  printf("\n");

  // Delete the string (calls free() for each letter in string)
  string_delete(string);

  // Free dynamically allocated memory
  free(object); // invalid code, not sure why :(
  return 0;
}


// Append character to the end of a string.
// Argument 1: Pointer to an existing string (or NULL, if no existing string)
// Argument 2: Character to append to end of string
// Return: Pointer to the start of the modified string
struct letter_obj* string_append(struct letter_obj* string, char letter)
{
  struct letter_obj* ptr;

  // Allocate heap space for 1 additional letter object
  // (which is a character + pointer to the next object).
  // Obviously, we'll want to free() this heap space later
  // on when the program is finished with it.
  struct letter_obj* object = malloc(sizeof (struct letter_obj)); 

  // Set member variables in the new object
  object->letter = letter;
  object->next = NULL;

  // Add the new object to the end of the existing string
  if(string == NULL)
    {
      // There is no existing string
      // Return a pointer to just this new object
      return object;
    }
  else
    {
      // There is an existing string.  Walk it till the end
      ptr = string;
      while(ptr->next != NULL)
	ptr = ptr->next;

      // ptr now is at the end of original string
      // Add the new object to the end
      ptr->next = object;

      // Return a pointer to the original head of the string
      return string;
    }
}

// Print out a string, character by character
// Argument 1: Pointer to start of string
void string_print(struct letter_obj* object)
{
  while(object != NULL)
    {
      printf("%c", object->letter);
      object = object->next;
    }

  return;
}


// Delete a string by free()ing every character
// Argument 1: Pointer to start of string
void string_delete(struct letter_obj* object)
{
  struct letter_obj* next_object;

  while(object != NULL)
    {
      next_object = object->next;
      free(object);
      object = next_object;
    }

  return;
}

// Modify a string by dropping all vowels
// Argument 1: Pointer to start of string
// Return: Pointer to the start of the modified string
//   (this pointer may be different, if the first letter was dropped)
struct letter_obj* string_drop_vowels(struct letter_obj* object)
{
  struct letter_obj* string_start = object;
  struct letter_obj* prior_object = NULL;

  while(object != NULL)
    {
      if(object->letter == 'a'
	 || object->letter == 'e'
	 || object->letter == 'i'
	 || object->letter == 'o'
	 || object->letter == 'u')
	{
	  // ** FOUND A VOWEL **
	  // "object" is currently a vowel
	  // Drop it by adjusting pointers to remove it from our linked list
	  if(prior_object != NULL)
	    {
	      // Common case - we're in the middle of the string
	      // Skip over this letter by making the previous letter
	      // point to the next letter.
	      prior_object->next = object->next;
	    }
	  else
	    {
	      // Special case - we're at the start of the string 
	      // and dropping a letter. In this case, the start
	      // must advance.
	      string_start = object->next;
	    }

	  // This stays put, and only advances when we find a non-vowel
	  prior_object = prior_object;

	  // Advance to next letter in string
	  object = object->next;
	}
      else
	{
	  // This object is not a vowel, and can stay in the string
	  prior_object = object;
	  object = object->next;
	}
    }

  return string_start;
}
