CC=gcc
CFLAGS=
LDFLAGS=
RM=rm -f
dir=../../build
exe=$(dir)/getPrettyGoodPty

all : $(exe)

$(exe) : mypty.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	$(RM) $(exe)

