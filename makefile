CC = gcc
CPPFLAGS = -I include
# L'option de debug -g à enlever
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LDLIBS = -lncurses
SPATH = src/
HPATH = include/
OPATH = obj/
LEVELPATH = levels/
ALL_SOURCES = $(wildcard $(SPATH)*.c)
TEST_SOURCES = $(filter-out $(SPATH)main.c, $(ALL_SOURCES))
SOURCES = $(filter-out $(SPATH)test.c, $(ALL_SOURCES))
HEADERS = $(wildcard $(HPATH)*.h)
ALL_OBJECTS = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(ALL_SOURCES))))
TEST_OBJECTS  = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(TEST_SOURCES))))
OBJECTS  = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(SOURCES))))
LEVELS = $(wildcard $(LEVELPATH)level*.txt)
DOCGEN = doxygen
DOXYFILE = doc/Doxyfile
ARCHIVE_NAME = ERKEN_Efe.tar.gz
ARCHIVE_SOURCES = $(SOURCES) $(HEADERS) makefile $(LEVELS) README.md $(DOXYFILE)
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

$(OPATH)%.o : $(SPATH)%.c $(HPATH)%.h | $(OPATH)
	@echo "-o $@ -c $^"
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(OPATH) :
	mkdir -p $@

clean :
	rm -f $(EXEC) $(TEST_EXEC) $(ALL_OBJECTS)

doc :
	$(DOCGEN) $(DOXYFILE)

archive : $(ARCHIVE_NAME)

$(ARCHIVE_NAME) : $(ARCHIVE_SOURCES)
	$(ARCHIVER) $(ARCHIVE_FLAGS) $@ $^

echo :
	@echo "All_SOURCES = $(ALL_SOURCES)"
	@echo "TEST_SOURCES = $(TEST_SOURCES)"
	@echo "SOURCES = $(SOURCES)"
	@echo "HEADERS = $(HEADERS)"
	@echo "All_OBJECTS = $(ALL_OBJECTS)"
	@echo "TEST_OBJECTS = $(TEST_OBJECTS)"
	@echo "OBJECTS = $(OBJECTS)"

