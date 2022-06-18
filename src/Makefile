CC=g++
CFLAGS=
TLIBS = -lgtest -lpthread -g
LIBS=

OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lgtest -lpthread -lrt -lm -lsubunit 
	OPEN=xdg-open
else
    LIBS=-lgtest -lm
	OPEN=open
endif

all: s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c s21_matrix_oop.cpp
	ar rcs libs21_matrix_oop.a s21_matrix_oop.o
	ranlib libs21_matrix_oop.a
	cp libs21_matrix_oop.a s21_matrix_oop.a

test:
	$(CC) $(CFLAGS) test.cpp -o test.out $(TLIBS)
	./test.out

gcov_report:
	$(CC) $(CFLAGS) -o test.out --coverage  test.cpp $(TLIBS)
	./test.out
	lcov  -t S21Matrix_test -o test.info -c -d .
	lcov --remove test.info '/usr/*' -o test_filtered.info
	genhtml -o report test_filtered.info
	
clean:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info *.dSYM *.info report *.cfg

check: 
	cp ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --quiet  --extension=cpp *.cpp *.h
	cppcheck --quiet --enable=all --language=c++ --suppress=missingIncludeSystem *.cpp *.h
	rm *.cfg

leaks: clean test
	CK_FORK=no leaks --atExit --  ./test.out

valgrind: clean test
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes ./test.out

rebuild: clean all
