##### Commun
CC = gcc

##### Chemins
SPATH = src/
HPATH = include/
OPATH = obj/
DPATH = dep/
LEVELPATH = levels/

##### Executables
TEST_EXEC = sokoban_test
EXEC = sokoban

##### Options
CPPFLAGS = -I include
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = -lncurses
DEPFLAGS = -MT $@ -MMD -MP -MF $(DPATH)$*.Td

##### Fichiers
ALL_SOURCES = $(wildcard $(SPATH)*.c)
TEST_SOURCES = $(filter-out $(SPATH)main.c, $(ALL_SOURCES))
SOURCES = $(filter-out $(SPATH)test.c, $(ALL_SOURCES))
HEADERS = $(wildcard $(HPATH)*.h)
ALL_OBJECTS = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(ALL_SOURCES))))
TEST_OBJECTS  = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(TEST_SOURCES))))
OBJECTS  = $(addprefix $(OPATH),$(patsubst %.c,%.o,$(notdir $(SOURCES))))
ALL_DEPENDS = $(addprefix $(DPATH),$(patsubst %.c,%.d,$(notdir $(ALL_SOURCES))))
LEVELS = $(wildcard $(LEVELPATH)level*.txt)

##### Générateur de documentation
DOCGEN = doxygen
DOXYFILE = doc/Doxyfile
DOCPATH = doc/doxygen

##### Générateur d'archive
ARCHIVE_NAME = ERKEN_Efe.tar.gz
ARCHIVE_SOURCES = $(SOURCES) $(HEADERS) makefile $(LEVELS) README.md $(DOXYFILE)
ARCHIVER = tar
ARCHIVE_FLAGS = -cvzf

##### Divers
### Protection contre interruption lors de la compilation
POSTCOMPILE = mv -f $(DPATH)$*.Td $(DPATH)$*.d && touch $@

##### Règles de construction
.PHONY : all test clean cleandoc cleanarchive cleanall doc archive

all : $(EXEC)

test : $(TEST_EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(TEST_EXEC) : $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(OPATH)%.o : $(SPATH)%.c $(DPATH)%.d | $(OPATH) $(DPATH)
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<
	@$(POSTCOMPILE)

$(OPATH) :
	mkdir -p $@

$(DPATH) :
	mkdir -p $@

$(ALL_DEPENDS) :

### Un des deux, c'est la même chose
# include $(wildcard $(ALL_DEPENDS))
-include $(ALL_DEPENDS)

clean :
	rm -f $(EXEC) $(TEST_EXEC) $(ALL_OBJECTS) $(ALL_DEPENDS)

cleandoc :
	rm -rf $(DOCPATH)

cleanarchive :
	rm -f $(ARCHIVE_NAME)

cleanall : clean
cleanall : cleandoc
cleanall : cleanarchive
cleanall :
	rm -rf $(OPATH) $(DPATH)

doc :
	$(DOCGEN) $(DOXYFILE)

archive : $(ARCHIVE_NAME)

$(ARCHIVE_NAME) : $(ARCHIVE_SOURCES)
	$(ARCHIVER) $(ARCHIVE_FLAGS) $@ $^
