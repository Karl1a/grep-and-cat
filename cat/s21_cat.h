#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {  // typedef allows not write "struct" all the time
  int b, e, n, s, t, v;
} opt;

static struct option long_options[] = {{"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {"number-nonblank", 0, 0, 'b'},
                                       {0, 0, 0, 0}};
#endif  // SRC_LIST_H_
