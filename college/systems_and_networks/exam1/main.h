#ifndef MAIN_H
#define MAIN_H

struct letter_obj
{
  char letter;
  struct letter_obj* next;
};

struct letter_obj* string_append(struct letter_obj*, char);
struct letter_obj* string_drop_vowels(struct letter_obj*);
void string_print(struct letter_obj*);
void string_delete(struct letter_obj*);

#endif  // MAIN_H
