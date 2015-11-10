all: a.out

a.out: test.c
	gcc -g -I"$$FCS_SRC_PATH" -I"$$FCS_SRC_PATH/patsolve-shlomif/patsolve" -I"$$FCS_PATH" test.c -lfreecell-solver
