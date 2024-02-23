TARGET = SmartCalc
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
MODULES = $(wildcard calculator/modules/*.c)
OBJECTS = $(patsubst %.c, obj/%.o, $(MODULES))
TEST_SRC = $(wildcard calculator/tests/*.c)
TEST_OBJ =  $(patsubst %.c, obj/%.o, $(TEST_SRC))

ifeq ($(OS), Linux)
	LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit
else
	LDLIBS = -lcheck -lm
endif

.PHONY: all install uninstall dvi dist test gcov_report valgrind_check clang_check clang clean fclean

all: fclean install

obj/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd SmartCalc && qmake && make && make clean && rm -rf Makefile && mv SmartCalc.app ../../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/SmartCalc.app ../build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"

test: $(OBJECTS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o test
	@echo "┏=========================================┓"
	@echo "┃            TESTING MODULES...           ┃"
	@echo "┗=========================================┛"
	@./test

gcov_report: calculator/modules/*.c calculator/tests/*.c
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	$(CC) $(CFLAGS) $(GFLAGS) calculator/modules/*.c calculator/tests/*.c $(LDLIBS) -o calculator/tests/testing
	./calculator/tests/testing
	@mkdir -p tests/controller_gcov
	@mv *.gcno ./tests/controller_gcov/ && mv *.gcda ./tests/controller_gcov/
	@lcov -t "test_coverage" -o krustygw_test_coverage.info -c -d .
	@genhtml -o report krustygw_test_coverage.info
	@open report/index.html
	@rm -rf *.gcda *.gcno report/test_coverage.info tests/modules_gcov tests/controller_gcov


clang_check:
	@echo "┃  Checking your code for Google Style    ┃"
	@cp ../materials/linters/.clang-format .
	@clang-format -n calculator/modules/*.c calculator/tests/*.c calculator/*.h SmartCalc/*.cpp SmartCalc/*.h
	@rm ./.clang-format

clang:
	@echo "┃  Formatting your code for Google Style  ┃"
	@cp ../materials/linters/.clang-format .
	@clang-format -i calculator/modules/*.c calculator/tests/*.c calculator/*.h SmartCalc/*.cpp SmartCalc/*.h
	@rm ./.clang-format

leaks_check: test
	cppcheck --enable=all --suppress=missingIncludeSystem calculator/modules/*.c SmartCalc/*.cpp
	@echo "┏=========================================┓"
	@echo "┃        Starting leaks check...          ┃"
	@echo "┗=========================================┛"
	@leaks -atExit -- ./test > leaks.log
	@echo "┏=========================================┓"
	@echo "┃        Leaks check is over              ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"

clean:
	rm -rf test obj report *.info calculator/tests/testing *.log

fclean: clean
	@rm -rf ../build ../dist ~/Desktop/$(TARGET).app

