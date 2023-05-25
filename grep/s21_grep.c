#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int num_flags = 0, i = 0, flag = 1;
  opt options = {0};
  char *buff = calloc(1024, sizeof(char));
  if (buff) {
    flags(&buff, argc, argv, &num_flags, &options, &flag);
    int file_count = argc - optind;
    if (flag == 1) {
      if (options.non) {
        for (i = 2; i <= argc - 1; i++) {
          char *filename = argv[i];
          non(argc, filename, &buff);
        }
      } else {
        for (i = num_flags + 2; i < argc; i++) {
          char *filename = argv[i];
          all_flags(&buff, filename, &options, file_count);
        }
      }
    }
  }
  free(buff);
  return 0;
}

void non(int argc, char *filename, char **buff) {
  FILE *f;
  regex_t regex;
  char temp, line[1024];
  memset(line, 0, sizeof(line));
  int j = 0;
  f = fopen(filename, "r");
  if (f) {
    regcomp(&regex, *buff, REG_EXTENDED);
    while ((temp = fgetc(f)) != EOF) {
      if (temp != '\n') {
        line[j] = temp;
        j++;
      } else {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
          if (argc < 4)
            printf("%s\n", line);
          else
            printf("%s:%s\n", filename, line);
        }
        j = 0;
        memset(line, 0, sizeof(line));
      }
    }
    regfree(&regex);
    fclose(f);
  } else {
    fprintf(stderr, "%s: No such file or directory\n", filename);
  }
}

void flags(char **buff, int argc, char *argv[], int *num, opt *options,
           int *flag) {
  int opt, opt_index = 0;
  options->non = 1;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                            &opt_index)) != -1) {
    switch (opt) {
      case 'i':
        options->i = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'e':
        options->e = 1;
        options->non = 0;
        if (*num > 0) strcat(*buff, "|");
        *num = *num + 1;
        strcat(*buff, optarg);
        break;
      case 'v':
        options->v = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'c':
        options->c = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'l':
        options->l = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'n':
        options->n = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'h':
        options->h = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 's':
        options->s = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case 'f':
        *num = *num + 1;
        options->f = 1;
        options->non = 0;
        break;
      case 'o':
        options->o = 1;
        options->non = 0;
        *num = *num + 1;
        break;
      case '?':
        fprintf(stderr,
                "usage: ./s21_grep [-chilnosv][-e pattern][-f file][pattern] "
                "[file ...]\n");
        *flag = 0;
        break;
    }
  }
  if (!options->e && !options->f) strcat(*buff, argv[optind++]);
}

void all_flags(char **buff, char *filename, opt *options, int file_count) {
  FILE *f;
  regex_t regex;
  char *line = calloc(BUFF_SIZE, sizeof(char *));
  int line_cnt = 0, line_cnt_v = 0, lineNum = 1, flags;
  f = fopen(filename, "r");
  if (options->i) {
    flags = REG_ICASE;
  } else {
    flags = REG_EXTENDED;
  }
  if (f) {
    regcomp(&regex, *buff, flags);
    while (!feof(f)) {
      if (fgets(line, BUFF_SIZE, f)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
          line_cnt++;
          if (!options->c && !options->l && !options->v) {
            if (!options->h && file_count > 1) printf("%s:", filename);
            if (options->n) printf("%d:", lineNum);
            if (!options->o) printf("%s", line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
          }
        }
        if (options->v && regexec(&regex, line, 0, NULL, 0) != 0) {
          line_cnt_v++;
          if (!options->c && !options->l) {
            if (!options->h && file_count > 1) printf("%s:", filename);
            if (options->n) printf("%d:", lineNum);
            if (!options->o) printf("%s", line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
          }
        }
        lineNum++;
      }
    }
    if (options->l && options->v && line_cnt_v > 0) printf("%s\n", filename);
    if (options->l && !options->v && line_cnt > 0) printf("%s\n", filename);
    if (options->c && f && !options->h) {
      if (options->l && file_count) printf("1\n");
      if (options->v) {
        if (file_count > 1)
          printf("%s:%d\n", filename, line_cnt_v);
        else
          printf("%d\n", line_cnt_v);
      } else {
        if (file_count > 1)
          printf("%s:%d\n", filename, line_cnt);
        else
          printf("%d\n", line_cnt);
      }
    }
    regfree(&regex);
    fclose(f);
  } else if (!f && !options->s && !options->e) {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
  }
  free(line);
}
