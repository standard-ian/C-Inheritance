# Ian Leuty ileuty@pdx.edu 10/8/2024

CC = g++

DEFINES =
DEBUG = -g
STANDARD = -std=c++17
WERROR = -Werror
FLAGS = -Wall $(STANDARD) $(DEBUG) $(DEFINES) $(WERROR)
SOURCES = *.cpp
#OBJECTS = *.o

PROG1 = program1

PROGS = $(PROG1) $(PROG2) $(PROG3)

all: $(PROGS)

$(PROG1): $(SOURCES)
	$(CC) $(FLAGS) $(SOURCES) $(OBJECTS) -o $(PROG1)

clean cls:
	rm -f $(PROGS) *.o *~ \#*

TAR_FILE = ${LOGNAME}_$(PROG1).tar.gz

tar:
	rm -f $(TAR_FILE)
	tar cvaf $(TAR_FILE) *.txt *.cpp *.h [Mm]akefile
	tar tvaf $(TAR_FILE)

git :
	if [ ! -d .git ] ; then git init; fi
	git add *.cpp *.h *.txt ?akefile
	git commit
	git push
