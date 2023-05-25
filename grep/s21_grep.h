#ifndef SRC_GREP_H_
#define SRC_GREP_H_
#include <getopt.h>
#define BUFF_SIZE 8192
typedef struct options {
  int e, i, v, c, l, n, h, s, f, o, non;
} opt;

static struct option long_options[] = {
    {"e", 0, 0, 'e'}, {"i", 0, 0, 'i'}, {"v", 0, 0, 'v'}, {"c", 0, 0, 'c'},
    {"l", 0, 0, 'l'}, {"n", 0, 0, 'n'}, {"h", 0, 0, 'h'}, {"s", 0, 0, 's'},
    {"f", 0, 0, 'f'}, {"o", 0, 0, 'o'}, {0, 0, 0, 0}};

void flags(char **buff, int argc, char *argv[], int *num, opt *options,
           int *flag);
void all_flags(char **buff, char *filename, opt *options, int file_count);
void non(int argc, char *filename, char **buff);
#endif  // SRC_GREP_H_
