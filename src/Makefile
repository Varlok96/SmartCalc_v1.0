CC = gcc -std=c11 -Wall -Wextra -Werror -g
OS = $(shell uname)
GCOVFLAGS = -L. --coverage

FILESo = pars.o stack.o 

ifeq ($(OS), Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	FLAGS = -lcheck -lm
endif

all: install
	../build/SmartCalc.app/Contents/MacOS/SmartCalc

install: uninstall
	mkdir -p ../build
	qmake6 SmartCalc/SmartCalc.pro -o ../build/Makefile
	cd ../build; make > /dev/zero 2> /dev/zero
	mkdir -p ~/Applications ; cp -r ../build/SmartCalc.app ~/Applications/SmartCalc.app

uninstall: clean
	rm -rf ../build
	rm -rf ~/Applications/SmartCalc.app
	
gcov_report: calc.a test
	rm -f *.g*
	$(CC) -w tests_calc.c pars.c $(FLAGS) $(GCOVFLAGS) calc.a -o test
	./test
	lcov -t test -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

ist:
	cd .. && tar -czvf SmartCalc.tar src

dvi:
	open dvi.html

test: calc.a 
	rm -rf asd.check
	@cat tests/headers.check >> asd.check				#headers
	@cat tests/test_pars.check >> asd.check 		    #compare

	checkmk clean_mode=1 asd.check > tests_calc.c
	rm -rf asd.check
	$(CC) -c tests_calc.c
	$(CC) tests_calc.o calc.a $(FLAGS) -o test
	./test


tests_calc.o:
	$(CC) -c tests_calc.c

calc.a: $(FILESo)
	ar -rc calc.a $(FILESo)
	ranlib calc.a
	rm -f *.o


pars.o:
	$(CC) -c pars.c

stack.o:
	$(CC) -c stack.c 

clang:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -i SmartCalc/credit.cpp SmartCalc/debit.cpp SmartCalc/mainwindow.cpp SmartCalc/main.cpp
	clang-format -style=google -i SmartCalc/credit.h SmartCalc/debit.h SmartCalc/mainwindow.h

git: clean
	git add . && git commit -m "add" && git push

clean:
	rm -rf *.o *.a *.out *.gcda *.gcno test tests_calc.c
	rm -rf .vscode/ a.out.dSYM/ report/ test.dSYM/ ../.vscode/ ../.DS_Store

valgrind: test
	CK_FORK=no valgrind  --leak-check=full  --track-origins=yes  ./test
