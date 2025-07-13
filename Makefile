CC = g++
CFLAGS = -Wall -Werror -Wextra -c -std=c++17 -pedantic

all: gcov_report

s21_matrix_oop.a:
	$(CC) $(CFLAGS) s21_matrix_oop.cpp
	ar rcs s21_matrix_oop.a *.o
	rm *.o

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) test.cpp
	$(CC) -L. -I. -o test_all test.o s21_matrix_oop.a -lgtest -pthread
	./test_all

rebuild:
	make clean
	make gcov_report

gcov_report:
	mkdir -p report
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_matrix_oop.cpp
	ar rcs s21_matrix_oop_gcov.a *.o
	ranlib s21_matrix_oop_gcov.a
	rm *.o
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage test.cpp
	$(CC) -L. -I. -o test_gcov *.o s21_matrix_oop_gcov.a -lgcov -pthread -lgtest
	./test_gcov
	gcov -o . s21_matrix_oop.cpp
	lcov -b ./ -d . --gcov-tool /usr/bin/gcov -c -o output.info --no-external
	genhtml -o report/ output.info
	xdg-open report/index.html

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h
clean:
	rm -f *.o *.a *.gcno *.gcda *.gcov *.info test_gcov test_all
	rm -fr report

valgrind:
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test_all

.PHONY: all clean rebuild gcov_report test clang valgrind