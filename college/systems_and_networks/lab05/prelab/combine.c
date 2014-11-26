#include "config.h"
#include "vec.h"
#include "combine.h"

#include <stdio.h>

// ORIGINAL function.
// This combiner function uses the greater amount
// of abstraction to operate, but has the slowest
// performance.
void combine1(vec_ptr v, data_t *dest)
{
  printf("Running combine1() - No code-level optimizations\n");

  long int i;

  *dest = IDENT;

  for(i=0; i < vec_length(v); i++)
    {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
    }
}


// CODE MOTION OPTIMIZATION:

// Move the call to vec_length() out of the loop
// because we (the programmer) know that the vector length will
// not change in the middle of the combine() function. 
// The compiler, though, doesn't know that!
void combine2(vec_ptr v, data_t *dest)
{
  printf("Running combine2()\n");
  printf("Added optimization: Code motion\n");

  long int i;

  *dest = IDENT;
  
  int tmp_length = vec_length(v);

  for(i=0; i < tmp_length; i++)
    {
      data_t val;
      get_vec_element(v, i, &val);
      *dest = *dest OP val;
    }

}


// REDUCING PROCEDURE CALLS OPTIMIZATION:

// This optimization eliminates the function call to
// get_vec_element() and accesses the data directly,
// trading off higher performance versus some loss
// of program modularity.
void combine3(vec_ptr v, data_t *dest)
{
  printf("Running combine3()\n");
  printf("Added optimization: Reducing procedure calls\n"); 

  long int i;

  *dest = IDENT;
  
  int tmp_length = vec_length(v);

  data_t *ptr;
  ptr = get_vec_start(v);

  for(i=0; i < tmp_length; i++)
    {
      *dest = *dest OP ptr[i];
    }
 
}


// ELIMINATING UNNEEEDED MEMORY ACCESSES OPTIMIZATION:

// This optimization eliminates the trip to memory
// to store the result of each operation (and retrieve it
// the next time). Instead, it is saved in a local variable 
// (i.e. a register in the processor)
// and only written to memory at the very end.
void combine4(vec_ptr v, data_t *dest)
{
  printf("Running combine4()\n");
  printf("Added optimization: Eliminating unneeded memory accesses\n");

  long int i;

  int tmp = IDENT;
  
  int tmp_length = vec_length(v);

  data_t *ptr;
  ptr = get_vec_start(v);

  for(i=0; i < tmp_length; i++)
    {
      tmp = *dest OP ptr[i];
    }
  *dest = tmp;

}


// LOOP UNROLLING x2
// (i.e. process TWO vector elements per loop iteration)
void combine5x2(vec_ptr v, data_t *dest)
{
  printf("Running combine5x2()\n");
  printf("Added optimization: Loop unrolling x2\n");

  long int i;

  int tmp = IDENT;
  
  int tmp_length = vec_length(v);

  data_t *ptr;
  ptr = get_vec_start(v);

  for(i=0; i<tmp_length; i=i+2)
    {
      tmp = (*dest OP ptr[i]) OP ptr[i+1];
    }
  if(i == tmp_length+1)
    {
      tmp = *dest OP ptr[i-1];
    }
  *dest = tmp;

}

// LOOP UNROLLING x3
// (i.e. process THREE vector elements per loop iteration)
void combine5x3(vec_ptr v, data_t *dest)
{
  printf("Running combine5x3()\n");
  printf("Added optimization: Loop unrolling x3\n");

  long int i;

  int tmp = IDENT;
  
  int tmp_length = vec_length(v);

  data_t *ptr;
  ptr = get_vec_start(v);

  for(i=0; i<tmp_length; i=i+3)
    {
      tmp = (*dest OP ptr[i]) OP ptr[i+1] OP ptr[i+2];
    }
  if(i == tmp_length+1)
    {
      tmp = *dest OP ptr[i-1];
    }
  else if(i == tmp_length+2)
    {
      tmp = *dest OP ptr[i-2];
    }
  *dest = tmp;

}


// LOOP UNROLLING x2 + 2-way parallelism
void combine6(vec_ptr v, data_t *dest)
{
  printf("Running combine6()\n");
  printf("Added optimization: Loop unrolling x2, Parallelism x2\n");

  long int i;

  int tmp0 = IDENT;
  int tmp1 = IDENT;
  
  int tmp_length = vec_length(v);

  data_t *ptr;
  ptr = get_vec_start(v);

  for(i=0; i<tmp_length; i=i+2)
    {
      tmp0 = *dest OP ptr[i];
      tmp1 = *dest OP ptr[i+1];
    }
  if(i == tmp_length+1)
    {
      tmp1 = *dest OP ptr[i-1];
    }
  *dest = tmp0;
  *dest = tmp1;

}
