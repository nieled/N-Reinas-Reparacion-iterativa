#
# makefile
# niel, 2016-12-01 10:23
#

all:
	@echo "Problema de las N-Reinas"
	g++ -Wall -o nreinas.o nreinas.cxx
run:
	./nreinas.o
clear:
	rm nreinas.o

# vim:ft=make
#
