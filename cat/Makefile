-std=C11
all: s21_cat

s21_cat: s21_cat.o
	gcc -Wall -Werror -Wextra s21_cat.c -o s21_cat

clean:
	rm -rf *.o
	rm -rf s21_cat
rebuild: clean all

test: rebuild
	cp ../../materials/linters/.clang-format ../../src/.clang-format
	clang-format -n s21_cat.c s21_cat.h
	rm ../.clang-format
	sh test_func_cat.sh
	sh test_leak_cat.sh
	make clean
