-std=C11
all: s21_grep

s21_grep: 
	gcc -Wall -Werror -Wextra s21_grep.c -o s21_grep

clean:
	rm -rf *.o
	rm -rf s21_grep
rebuild: clean all

test: rebuild
	cp ../../materials/linters/.clang-format ../../src/.clang-format
	clang-format -n s21_grep.c s21_grep.h
	sh test_leaks.sh
	make clean

