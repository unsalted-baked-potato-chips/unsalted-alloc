


.PHONY: default test

default:



test: ./src/*.c ./include/ualloc.h
	(cd unitc;make clean; INC_DIR=../include/ SRC_FILES=../src/*.c make run_tests)
	./unitc/run_tests
	(cd unitc; make clean)

