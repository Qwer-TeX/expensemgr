#  Makefile -- The Master Makefile for the whole distribution

#  Copyright (C) 2024  Mitnew
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program. If not, see <http://www.gnu.org/licenses/>.
#
PREFIX = /usr/local
CC	=	cc
CFLAGS	=	-Wall -g -DVERSION=$(version)
SOURCES	=	main.c importFile.c exportFile.c updateRecord.c deleteRecord.c newRecord.c readRecord.c \
					blankRecords.c
OBJECTS	=	$(SOURCES:.c=.o)

package = gnubank
version = 0.2
tarname = $(package)
distdir = $(tarname)-$(version)

all:		gbank

install:
	[[ -d $(PREFIX) ]] || install -v -dm755 $(PREFIX)
	[[ -d $(PREFIX) ]] && install -v -m755 gbank $(PREFIX)/bin

install-strip:
	[[ -d $(PREFIX) ]] || install -v -dm755 $(PREFIX)
	[[ -d $(PREFIX) ]] && install -v -m755 -s gbank $(PREFIX)/bin

uninstall:
	[[ -x $(PREFIX)/bin/gbank ]] && rm -r $(PREFIX)/bin/gbank

strip:	gbank
	strip $^

gbank: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJECTS):	gnubank.h

dist: $(distdir).tar.gz

$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)

$(distdir):
	mkdir -p $(distdir)
	cp Makefile $(distdir)
	cp $(wildcard *.c) $(wildcard *.h) $(distdir)
	cp README ChangeLog COPYING $(distdir)

tags: ctags etags

ctags:
	ls *.c | xargs ctags -a

etags:
	ls *.c | xargs etags -a

distclean: clean

clean:
	rm -f gbank $(OBJECTS) TAGS tags

help:
	@echo "Run make to build gbank" 
	@echo "Use make PREFIX=/some/directory to specify a prefix "
	@echo ""
	@echo "all              ( Default )"
	@echo "help             Print help" 
	@echo "gbank            Build"
	@echo "tags             build all emacs and vi tags"
	@echo "ctags            build vi/ex tags"
	@echo "etags            build emacs tags"
	@echo "strip            Strip xecutable"
	@echo "install          Install"
	@echo "install-strip    Strip install"
	@echo "uninstall        Uninstall"
	@echo "dist             Pack a tarball for release"
	@echo "clean            Clean all"
	@echo "distclean        Clean & Rinse distribution"

.PHONY: all clean stripped gbank dist clean distclean help install install-strip
