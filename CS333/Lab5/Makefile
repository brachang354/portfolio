#Bradley Chang Lab 5 Cypher
CC = gcc
DEFINES =
DEBUG = 
CFLAGS = -Wall -Wextra -Wshadow -Wunreachable-code \
-Wredundant-decls -Wmissing-declarations \
-Wold-style-definition -Wmissing-prototypes \
-Wdeclaration-after-statement -Wno-return-local-addr \
-Wunsafe-loop-optimizations -Wuninitialized \
-Wno-unused-parameter -Werror

COMMENT = "This is a comment"

PROG1 = thread_hash
PROGS = $(PROG1)

all: $(PROGS)

$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) -o $@ $^ -lcrypt
	#chmod og-rx $(PROG1)

$(PROG1).o: $(PROG1).c thread_hash.h
	$(CC) $(CFLAGS) -c $< -g


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
