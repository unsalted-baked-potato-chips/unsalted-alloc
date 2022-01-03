


.PHONY: default test

default:



test: run_tests
	./unitc/run_tests
	(cd unitc; make clean)

run_tests:
	(cd unitc; INC_DIR=../include/ SRC_FILES=../src/*.c make run_tests)
