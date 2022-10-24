CC = gcc
CFLAGS = -Wall -Wextra
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
MAKEFILE = makefile
README = README.md
DOXYFILE = Doxyfile
DOXYGEN = doxygen
DOXYGEN_FLAGS =
LEVELS = $(wildcard level*.txt)
ARCHIVE_NAME = ERKEN_Efe.tar.gz
ARCHIVE_SOURCES = $(SOURCES) $(HEADERS) $(MAKEFILE) $(LEVELS) $(README) $(DOXYFILE)
ARCHIVE = tar
ARCHIVE_FLAGS = -cvzf
EXEC = sokoban

$(EXEC) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm sokoban
	rm *.o

doc :
	$(DOXYGEN) $(DOXYGEN_FLAGS)

archive : $(ARCHIVE_SOURCES)
	$(ARCHIVE) $(ARCHIVE_FLAGS) $(ARCHIVE_NAME) $^

