#Bradley Chang Lab 2 Caesar Cipher and Xor Cipher Makefile
CC = gcc
DEFINES =
DEBUG = -g
CFLAGS = $(DEFINES) $(DEBUG) -Wall -Wextra -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized -Werror
COMMENT = "This is a comment"

PROG1 = caesar
PROG2 = xor
PROGS = $(PROG1) $(PROG2)

all: $(PROGS)

$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) -o $(PROG1) $(PROG1).o
	chmod og-rx $(PROG1)

$(PROG2): $(PROG2).o
	$(CC) $(CFLAGS) -o $(PROG2) $(PROG2).o
	chmod og-rx $(PROG2)

$(PROG1).o: $(PROG1).c #$(PROG1).h
	$(CC) $(CFLAGS) -c $(PROG1).c

$(PROG2).o: $(PROG2).c
	$(CC) $(CFLAGS) -c $(PROG2).c

#hellofunc.o: hellofunc.c $(PROG1).h
#	$(CC) $(CFLAGS) -c hellofunc.c


clean cls:
	rm -f $(PROG1) *.o *~ \#*

ci:
	if [ ! -d RCS ] ; then mkdir RCS; fi
	ci -t-none -l -m"lazy commit" [Mm]akefile *.[ch]

TAR_FILE = ${LOGNAME}_$(PROG1).tar.gz
tar:
	rm -f $(TAR_FILE)
	tar cvaf $(TAR_FILE) *.[ch] [Mm]akefile
	tar tvaf $(TAR_FILE)

comment:
	echo $(COMMENT)

opt:
	make clean
	make DEBUG=-O
