#include "s21_cat.h"

void flags(int argc, char *argv[], opt *options);
void reader(int argc, char *argv[], opt *options);
void option_b(FILE *f);
void option_n(FILE *f);
void option_e(FILE *f);
void option_s(FILE *f);
void option_t(FILE *f);
void option_v(FILE *f);
void none(FILE *f);

int main(int argc, char *argv[]) {
  opt options = {0};
  flags(argc, argv, &options);
  reader(argc, argv, &options);
  return 0;
}

void flags(int argc, char *argv[], opt *options) {
  int opt;
  int opt_index = 0;
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                            &opt_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      default:
        fprintf(stderr, "use: 'b, e, n, s, t, v, T, E'\n");
        exit(1);
    }
  }
}

void reader(int argc, char *argv[], opt *options) {
  FILE *f;
  for (; optind < argc; optind++) {
    f = fopen(argv[optind], "r+");
    if (f) {
      int cur;
      int flag = 0;
      int str_cnt = 1;
      int empty = 0;
      while ((cur = fgetc(f)) != EOF) {
        if (options->s) {
          if (cur == '\n') empty++;
          if (cur != '\n') empty = 0;
          if (empty > 2) continue;
        }
        if (options->b) {  //
          if (cur != '\n') {
            if (flag == 0) {
              printf("%6d\t", str_cnt++);
              flag = 1;
            }
          } else {
            flag = 0;
          }
        }
        if (options->n && (!options->b)) {
          if (flag == 0) printf("%6d\t", str_cnt++);
          if (cur == '\n') flag = 0;
          if (cur != '\n') flag = 1;
        }
        if (options->e && cur == '\n') {
          printf("$");
        }
        if (options->t && cur == '\t') {
          printf("^");
          cur = 'I';
        }
        if (options->v) {
          if (cur != '\n') {
            if (cur < 32 && cur != 9 && cur != 10) {
              printf("^");
              cur += 64;
            } else if (cur > 127 && cur < 160) {
              printf("M-^");
              cur -= 64;
            } else if (cur == 127) {
              printf("^");
              cur -= 64;
            }
          }
        }
        printf("%c", cur);
      }
    }
    fclose(f);
  }
}
