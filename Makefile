PROGRAM   = towers_of_hanoi
CC        = gcc
CFLAGS    = -Wall
LDFLAGS   = -lGL -lGLU -lglut
DEP       = main.o \
			stack.o \
			draw.o \
			move.o \
			algorithm.o \
			image.o

$(PROGRAM): $(DEP)
	$(CC) -o $(PROGRAM) $(DEP) $(LDFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
