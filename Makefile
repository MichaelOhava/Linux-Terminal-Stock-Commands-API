#this is the makefile for the exercise
#simple make file

all: out libutils.so

out: stockdata.c linkedlist.c files_extract.c export_to_csv.c
	gcc stockdata.c linkedlist.c files_extract.c  -o stockdata.out 2>/dev/null
	gcc export_to_csv.c linkedlist.c files_extract.c -o export_to_csv.out 2>/dev/null
	gcc best_pe.c linkedlist.c files_extract.c -o best_pe.out 2>/dev/null
libutils.so: linkedlist.c files_extract.c
	gcc linkedlist.c files_extract.c -o lib.so -fPIC -shared 2>/dev/null

.PHONY: clean
clean:
	find . -name '*.out' -type f -delete 
	find . -name '*.so' -type f -delete
	find . -name 'StocksNames.txt' -type f -delete	
