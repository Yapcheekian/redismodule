ifndef RMUTIL_LIBDIR
	RMUTIL_LIBDIR=../rmutil
endif

CC=gcc

all: example1 example2 example3

example1:
	$(CC) -I . -fPIC -std=gnu99 -c -o module1.o module1.c \
	&& $(LD) -o module1.so module1.o -shared -Bsymbolic -lc

example2:
	$(CC) -I . -fPIC -std=gnu99 -c -o module2.o module2.c \
	&& $(LD) -o module2.so module2.o -shared -Bsymbolic -lc

# example3:
# 	cd rmutil && make && cd ../example && make
