DESTDIR = /usr/local

CC = gcc
CFLAGS =-Wextra -Wall -std=gnu99 -Iinclude -Wno-unused-parameter -Wno-unused-variable -Wno-duplicate-decl-specifier -Wl,-rpath,$(PWD)/lib -Wl,-rpath,$(DESTDIR)/lib
LDFLAGS = -Llib -lgeoh
LIBFLAGS = -fpic -shared 

GEOH_C_SOURCES = src/geoh.c 
GEOH_C_BINS = bin/encode bin/decode 
GEOH_C_UNITTESTS = bin/tests
GEOH_TARGET_LIB = lib/libgeoh.so
GEOH_INCLUDE_FILE = include/geoh.h

BINDIR = bin
LIBDIR = lib

OBJS = $(GEOH_C_SOURCES:.c=.o)

all: $(BINDIR) $(LIBDIR) $(GEOH_TARGET_LIB) $(GEOH_C_BINS) 

bin/encode: src/encode.c $(GEO_TARGET_LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

bin/decode: src/decode.c $(GEOH_TARGET_LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(GEOH_TARGET_LIB): $(GEOH_C_SOURCES) 
	$(CC) $(CFLAGS) $(LIBFLAGS) $^ -o $@

$(GEOH_C_UNITTESTS): tests/tests.c $(GEOH_C_SOURCES)
	$(CC) $(CFLAGS) $^ -lcmocka -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

test: all $(GEOH_C_UNITTESTS) 
	$(GEOH_C_UNITTESTS)

install: $(GEOH_TARGET_LIB)
	cp $(GEOH_INCLUDE_FILE) $(DESTDIR)/include
	cp $(GEOH_TARGET_LIB) $(DESTDIR)/lib
	ldconfig -n $(DESTDIR)/lib

uninstall: 
	rm $(DESTDIR)/$(GEOH_INCLUDE_FILE)
	rm $(DESTDIR)/$(GEOH_TARGET_LIB)

clean:
	rm -rf $(BINDIR) $(LIBDIR)
