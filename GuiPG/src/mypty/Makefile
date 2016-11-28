CC=gcc
CFLAGS=-Wall -pedantic -std=c99
#CFLAGS=-DDEBUG
LDFLAGS=
RM=rm -f
dir=../../build
exe=$(dir)/getPrettyGoodPty

all: $(exe)

$(exe): mypty.o print_err_if.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

mypty.o: mypty.c 
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

print_err_if.o: print_err_if/print_err_if.c\
                print_err_if/print_err_if.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.o $(exe)
