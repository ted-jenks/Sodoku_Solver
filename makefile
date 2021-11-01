CC=g++
CFLAGS=-g -Wall

_DEPS = sudoku.h
DEPS = $(patsubst %,%,$(_DEPS))

_OBJ = main.o sudoku.o 
OBJ = $(patsubst %,%,$(_OBJ))

sudoku: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean

clean:
	rm -f *.o *~ core *~ 