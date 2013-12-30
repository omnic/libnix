# Basic C-related flags
CC = clang
CFLAGS = -O2 -march=native -mtune=native
C_LIBFLAGS = -FPIC

# BEGIN OS-Dependent Flags

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIB_XTENSION = so
	LIB_FLAGS   += -shared
endif
ifeq ($(UNAME_S),Darwin)
	LIB_XTENSION = dylib
	LIB_FLAGS   += -dynamiclib
endif

# CLOSE OS-Dependent Flags

all:	build/libnix.$(LIB_XTENSION)

test:	all
	@echo "No tests available ATM, sorry."

clean:	build
	rm -rvf build

build:
	mkdir -pv build

build/libnix.$(LIB_XTENSION):	build/mapfile.o build/textfile.o
	$(CC) $(LIB_FLAGS) -o build/libnix.$(LIB_XTENSION) build/mapfile.o build/textfile.o

build/mapfile.o:	build libnix.h mapfile.c
	$(CC) -c mapfile.c -o build/mapfile.o $(C_LIBFLAGS) $(CFLAGS)

build/textfile.o:	build libnix.h textfile.c
	$(CC) -c textfile.c -o build/textfile.o $(C_LIBFLAGS) $(CFLAGS)
