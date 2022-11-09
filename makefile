CC = gcc
CFLAGS = -Wall -Wextra -g		# L'option de debug -g à enlever
LDFLAGS =
LDLIBS = -lncurses
ALL_SOURCES = $(wildcard *.c)
TEST_SOURCES = $(filter-out main.c, $(ALL_SOURCES))
SOURCES = $(filter-out test.c, $(ALL_SOURCES))
HEADERS = $(wildcard *.h)
ALL_OBJECTS = $(ALL_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
OBJECTS = $(SOURCES:.c=.o)
DOXYGEN_FLAGS =
LEVELS = $(wildcard level*.txt)
ARCHIVE_NAME = ERKEN_Efe.tar.gz
ARCHIVE_SOURCES = $(SOURCES) $(HEADERS) makefile $(LEVELS) README.md Doxyfile
ARCHIVER = tar
ARCHIVE_FLAGS = -cvzf
TEST_EXEC = sokoban_test
EXEC = sokoban

.PHONY : all test clean doc archive

all : $(EXEC)

test : $(TEST_EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(TEST_EXEC) : $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(EXEC) $(TEST_EXEC) $(ALL_OBJECTS)

doc :
	doxygen $(DOXYGEN_FLAGS)

archive : $(ARCHIVE_NAME)

$(ARCHIVE_NAME) : $(ARCHIVE_SOURCES)
	$(ARCHIVER) $(ARCHIVE_FLAGS) $@ $^
