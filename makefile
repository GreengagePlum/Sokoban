# Makefile for project compilation
# Copyright (C) 2022, 2023 Efe ERKEN
#
# This file is part of Sokoban
#
# Sokoban is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Sokoban is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Sokoban.  If not, see <https://www.gnu.org/licenses/>.
#
# SPDX-License-Identifier: GPL-3.0-or-later

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
CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra
LDFLAGS = -Llib
LDLIBS = -lncurses -lSDL2
DEPFLAGS = -MT $@ -MMD -MP -MF $(DPATH)$*.Td

##### Fichiers
ALL_SOURCES = $(wildcard $(SPATH)*.c)
TEST_SOURCES = $(filter-out $(SPATH)main.c, $(ALL_SOURCES))
SOURCES = $(filter-out $(SPATH)test.c, $(ALL_SOURCES))
ALL_HEADERS = $(wildcard $(HPATH)*.h)
ALL_OBJECTS = $(addprefix $(OPATH), $(patsubst %.c,%.o, $(notdir $(ALL_SOURCES))))
TEST_OBJECTS  = $(addprefix $(OPATH), $(patsubst %.c,%.o, $(notdir $(TEST_SOURCES))))
OBJECTS  = $(addprefix $(OPATH), $(patsubst %.c,%.o, $(notdir $(SOURCES))))
ALL_DEPENDS = $(addprefix $(DPATH), $(patsubst %.c,%.d, $(notdir $(ALL_SOURCES))))
LEVELS = $(wildcard $(LEVELPATH)level*.txt)

##### Générateur de documentation
DOCGEN = doxygen
DOXYFILE = doc/Doxyfile
DOCPATH = doc/doxygen/
DOCTARGET = $(DOCPATH)html/

##### Générateur d'archive
ARCHIVE_NAME = ERKEN_Efe.tar.gz
ARCHIVE_SOURCES = $(SOURCES) $(ALL_HEADERS) makefile $(LEVELS) README.md $(DOXYFILE)
ARCHIVER = tar
ARCHIVE_FLAGS = -cvzf

##### Divers
### Protection contre interruption lors de la compilation
POSTCOMPILE = mv -f $(DPATH)$*.Td $(DPATH)$*.d && touch $@

##### Règles de construction
.PHONY : all test SDL2 doc archive clean cleanSDL2 cleandoc cleanarchive cleanall

all : $(EXEC)

test : $(TEST_EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TEST_EXEC) : $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OPATH)%.o : $(SPATH)%.c $(DPATH)%.d | $(OPATH) $(DPATH)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -o $@ $<
	@$(POSTCOMPILE)

$(OPATH) :
	mkdir -p $@

$(DPATH) :
	mkdir -p $@

$(ALL_DEPENDS) :

-include $(ALL_DEPENDS)

clean :
	rm -f $(EXEC) $(TEST_EXEC) $(ALL_OBJECTS) $(ALL_DEPENDS)

cleanSDL2 :
	rm -rf bin/ include/SDL2/ lib/ share/

cleandoc :
	rm -rf $(DOCPATH)

cleanarchive :
	rm -f $(ARCHIVE_NAME)

cleanall : clean
cleanall : cleanSDL2
cleanall : cleandoc
cleanall : cleanarchive
cleanall :
	rm -rf $(OPATH) $(DPATH)

doc : $(DOCTARGET)

$(DOCTARGET) : $(ALL_SOURCES) $(ALL_HEADERS) README.md $(DOXYFILE)
	$(DOCGEN) $(DOXYFILE)

archive : $(ARCHIVE_NAME)

$(ARCHIVE_NAME) : $(ARCHIVE_SOURCES)
	$(ARCHIVER) $(ARCHIVE_FLAGS) $@ $^

SDL2 :
	cd SDL2 && ./configure --prefix=$(PWD)/
	cd SDL2 && make install -j6
