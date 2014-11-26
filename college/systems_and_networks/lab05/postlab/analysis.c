// Based on dictionary.c 
// "Computer Systems: A Programmer's Perspective", Second Edition
// by Randal E. Bryant and David R. O'Hallaron

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "options.h"
#include "analysis.h"

// Global variables to store statistics
int wcnt = 0; /* Number of words */
int ucnt = 0; /* Number of unique words */
int mcnt = 0; /* Count of Most frequent word */
int scnt = 0; /* Count of number of singletons */
char *mstring = ""; /* Most frequent word */
int llen = 0; /* Length of the longest word */
char *lstring = ""; /* A longest string */
int lcnt = 0; /* Number of words having maximum length */

// The hash table
h_ptr *htable;
int tsize;

// Convert string to lower case
void lowercase(char *s)
{
  int i;
  int len = strlen(s);
  
  for (i = 0; i < len; i++)
    {
      if (s[i] >= 'A' && s[i] <= 'Z')
	s[i] -= ('A' - 'a');
    }
}


// Hash table functions
void new_table(int size)
{
    tsize = size;
    htable = (h_ptr *) calloc(size, sizeof(h_ptr));
    if (!htable) {
	fprintf(stderr, "Couldn't allocate hash array, exiting\n");
	exit(1);
    }

    // At the beginning, each element in the hash table
    // is a NULL pointer
    for(int i=0; i<size; i++)
      {
	htable[i]=NULL;
      }
}

// Allocate new element to store in hash table
h_ptr new_element(char *s)
{
    h_ptr result = (h_ptr) malloc(sizeof(h_rec));
    int wlen = strlen(s);
    if (wlen > llen) {
	lstring = s;
	llen = wlen;
	lcnt = 1;
    } else if (wlen == llen)
	lcnt++;
    if (!result) {
	fprintf(stderr, "Couldn't allocate hash element, exiting\n");
	exit(1);
    }

    result->word = s;
    result->freq = 1;
    result->next = NULL; // JAS: Fixed Valgrind report of un-init variable use later
    return result;
}


// Hash function: Simply add characters together
unsigned hash_function(char *s)
{
  unsigned val = 0;
  int c;

  // String ends in null character: \0
  // Step through string character by character
  // adding the ASCI codes together. Use modular
  // division at end to wrap to hash table size.
  c = *s;
  while(c != '\0')
    {
      val = val + c;
      s++;
      c = *s;
    }

  return val % tsize;
}


// Allocate space for string (to be stored in hash table)
char *save_string(char *s)
{
  char *result = (char *) malloc(strlen(s)+1);
  if (!result)
    {
      fprintf(stderr, "Couldn't allocate space for string, exiting\n");
      exit(1);
    }
  strcpy(result,s);
  return result;
}


// *Recursively* find string in list.  Add to end if not found
h_ptr find_element(h_ptr ls, char *s)
{
  if (!ls) 
    {
      // Come to end of list.  Insert this one 
      ucnt++;
      return new_element(save_string(s));
    }

  if (strcmp(s,ls->word) == 0) 
    {
      ls->freq++;
      if (ls->freq > mcnt)
	{
	  mcnt = ls->freq;
	  mstring = ls->word;
	}
      return ls;
    }

  ls->next = find_element(ls->next, s);
  return ls;
}

// Insertion Sort all elements in hash table by frequency
// (combine all buckets in hash table)
// Note that this DESTROYS THE HASH TABLE while running.
// A new array (large enough to hold all elements
// in the hash table) is created. This array holds pointers
// to the existing elements in the hash table. At the end,
// the 'next' pointers in the elements are changed to form a linked
// list in sorted order. (This act destroys the hash table struture).


h_ptr sort_words()
{
    h_ptr ls = NULL;
    h_ptr ele;
    h_ptr *array = calloc(ucnt, sizeof(h_ptr));
    int i, j;
    int cnt = 0;
    scnt = 0; // Count singletons

    // Sort hash table elements and save as pointers in 'array'
    /*
    for (i = 0; i < tsize; i++)
       for (ele = htable[i]; ele != NULL; ele = ele->next)
       {
	    if (ele->freq == 1)
            {
		scnt++;
            }
	    for (j = cnt; j > 0 && ele->freq > array[j-1]->freq; j--)
            {
	      array[j] = array[j-1];
            }

	    array[j] = ele;
	    cnt++;
       }
    */
    int pivot, tmp;
    pivot = 0;
    i = 0;
        

    // Convert the hash table into a big linked list
    // based on the order in 'array'
    ls = array[0];
    for (j = 0; j < cnt-1; j++)
	array[j]->next = array[j+1];
    array[cnt-1]->next = NULL;
    free ((void *) array);
    return ls;








}

// Insert string into hash table at correct location
void insert_string(char *s)
{
    int index;
    lowercase(s);
    index = hash_function(s);
    htable[index] = find_element(htable[index], s);  
}

// Extract word from file
#define BSIZE 1024
char buf[BSIZE];
int bufvalid = 0;
FILE *infile;

void init_token(FILE *in) {
    bufvalid = 0;
    infile = in;
}

// Added some non-ASCII characters encountered in European parliament corpus
static char *skipchar = " \t\n\r.,:;/<>()[]{}?!\"-'\0xc2\0xa0";

// Keep getting tokens.  Return NULL when no more
char *get_word()
{
    char *s = NULL;
    while (1) {
	if (bufvalid) {
	    s = strtok(NULL, skipchar);
	    if (s)
		break;
	}
	if (!fgets(buf, BSIZE, infile))
	    return NULL;
	bufvalid = 1;
	s = strtok(buf, skipchar);
	if (s)
	    break;
    }
    wcnt++;
    return s;
}


#define MAXNG 10

char *get_token(int ngram)
{
    /* Buffer of last ngram-1 tokens */
    static char token_buf[MAXNG][BSIZE];
    static int first = 1;
    static int bindex = 0; /* In which buffer to insert next token */
    static char sbuf[BSIZE];
    char *nextpos = sbuf;
    int i; int index;

    if (ngram == 1)
	return get_word();
    if (first) {
	/* Get ngram-1 tokens */
	while (bindex < ngram-1) {
	    char *word = get_word();
	    if (!word) {
		return NULL; /* Document doesn't have enough tokens */
	    }
	    strcpy(token_buf[bindex++], word);
	}
	first = 0;
    }
    /* Get new token */
    char *word = get_word();
    if (!word) {
	return NULL; /* No more ngrams */
    }
    strcpy (token_buf[bindex++], word);
    if (bindex >= MAXNG)
	bindex = 0;
    /* Generate string of last ngram-1 tokens */
    index = bindex - ngram;
    if (index < 0)
	index += MAXNG;
    for (i = 0; i < ngram; i++) {
	if (i != 0)
	    *nextpos++ = ' ';
	word = token_buf[index];
	strcpy(nextpos, word);
	nextpos += strlen(word);
	index++;
	if (index >= MAXNG)
	    index = 0;
    }
#if 0
     printf("Next n-gram = '%s'\n", sbuf);
#endif
    return sbuf;
}



// Find statistics of word frequency in document
void word_freq(FILE *src, int details, int ngram, int size)
{
    char *s;
    h_ptr list_head, ptr;

    printf(" Initializing hash table...\n");
    init_token(src);
    new_table(size);

    printf(" Inserting all n-grams into hash table in lowercase form...\n");
    while ((s = get_token(ngram)))
      {
	insert_string(s);
      }

    printf(" Sorting all hash table elements according to frequency...\n");
    list_head = sort_words();
    // NOTE: At this point, the hash table structure has been destroyed!
    // All of the elements are now in a single *sorted* linked list.
    // The head of the list is pointed to by the 'list_head' pointer

    if (details > 0) {
	printf("\nAnalysis Details:\n(Top %i list of n-grams)\n", details);
	ptr = list_head;
	while (ptr && details--) {
	    printf("%d\t'%s'\n", ptr->freq, ptr->word);
	    ptr = ptr->next;
	}
    }

    printf("\nAnalysis Summary:\n");
    printf("%d total n-grams\n", wcnt);
    printf("%d unique n-grams\n", ucnt);
    printf("%d singleton n-grams (occur only once)\n", scnt);
    printf("Most common n-gram (with %d occurrences) is '%s' \nLongest n-gram (%d have length %d) is '%s'\n",
	   mcnt, mstring, lcnt, llen, lstring);

    ptr = list_head;
    h_ptr tmp;
    while(ptr != NULL)
    {
       tmp = ptr->next;       
       free(ptr->word);
       free(ptr);
       ptr = tmp;
    }
}

int main(int argc, char *argv[])
{
    int details = 10;
    int hash_table_size = 1024;
    int ngram = 1;
    char *fname = NULL;
    FILE *infile = stdin;

    printf("Running analysis program...\n");

    add_string_option("file", &fname);
    add_int_option("ngram", &ngram);
    add_int_option("details", &details);
    add_int_option("hash-table-size", &hash_table_size);

    printf("\nOptions used when running program:\n");
    parse_options(argc, argv, NULL);
    show_options(stdout);

    printf("N-gram size %d\n", ngram);
    if (fname) {
	infile = fopen(fname, "r");
	if (!infile) {
	    fprintf(stderr, "Couldn't open file '%s'\n", fname);
	    exit(1);
	}
    }

    printf("\nRunning analysis... (This can take several minutes or more!)\n");
    word_freq(infile, details, ngram, hash_table_size);
    printf("Total time = %f seconds\n", (double) clock() / CLOCKS_PER_SEC);
    fclose(infile);
    
    //free dynamically allocated memory
    free(htable);
    free(save_string);
    
    return 0;
}
