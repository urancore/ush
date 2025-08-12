CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -I../../include
LDFLAGS = -L../../lib -lush -static-libgcc

OUTDIR  = ../bin
TARGET  = $(OUTDIR)/hello.exe
SRC     = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(OUTDIR)
	echo " LD    $@"
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

clean:
	echo " CLEAN"
	rm -rf $(OUTDIR)\hello.exe 2
