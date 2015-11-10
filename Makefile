all: a.out

a.out: test-w-calls.c
	gcc -g -I"$$FCS_SRC_PATH" -I"$$FCS_SRC_PATH/patsolve-shlomif/patsolve" -I"$$FCS_PATH" $< -lfreecell-solver
