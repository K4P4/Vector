CC=g++
CFLAGS=-I.
DEPS = Studentas.h Vector.h Zmogus.h
OBJ = main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
 
