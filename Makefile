APP=DNA_Analizer

.PHONY: all app tests clean cppcheck style

CC=g++ -std=c++17 -Wall -Werror -Wextra
TEST_LIB:=./tests/tests_main.cc ./dna/dna.cc
CHECKFLAGS=-lgtest
CPPCHECKFLAG = --enable=all --language=c++ --suppress=missingIncludeSystem --std=c++17

OS = $(shell uname)

ifeq ($(OS), Linux)
	CC+=-D OS_LINUX -g -s
	CHECKFLAGS+=-lpthread
else
	CC+=-D OS_MAC-
endif

all: clean app

app: 
	@cmake -S . -B build
	@cmake --build build

dvi:
	doxygen ./docs/Doxyfile
	open ./docs/html/index.html

tests:
	@$(CC) $(TEST_LIB) $(CHECKFLAGS) -o Test
	@./Test
	@rm -rf *.o Test

clean:
	@rm -rf ./build ./docs/html

cppcheck:
	@cppcheck $(CPPCHECKFLAG) */*.cc */*/*.cc *.cc  */*.h */*/*.h *.h

style: 
	clang-format -style=google -n -verbose */*.cc */*.h
