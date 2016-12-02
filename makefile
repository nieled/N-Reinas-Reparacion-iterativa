#
# makefile
# niel, 2016-12-01 10:23
#

all:
	@echo "Problema de las N-Reinas"
	g++ -Wall -o nreinas nreinas.cxx
run:
	./nreinas
clear:
	rm nreinas



# vim:ft=make
#
