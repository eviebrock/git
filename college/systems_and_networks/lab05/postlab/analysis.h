#ifndef ANALYSIS_H
#define ANALYSIS_H

// The hash table
typedef struct HELE {
    char *word;
    int freq;
    struct HELE *next;
} h_rec, *h_ptr;

void lowercase(char *s);
void new_table(int size);
h_ptr new_element(char *s);
unsigned hash_function(char *s);
char *save_string(char *s);
h_ptr sort_words();
void insert_string(char *s);
void init_token(FILE *in);
char *get_word();
char *get_token(int ngram);
void word_freq(FILE *src, int details, int ngram, int size);

#endif


