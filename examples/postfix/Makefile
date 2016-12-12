CXXFLAGS = -g -Wall


OBJ = plus.o interpreter.o main.o binary_operation.o composite_operation.o

OUT = calc


all: $(OUT)


$(OUT): $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(OUT)


clean:
	rm -f *~ a.out $(OUT) *.o

