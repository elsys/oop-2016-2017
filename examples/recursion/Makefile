CXXFLAGS = -g -Wall


OBJ = queens.o
SRC = queens.cc hilbert.cc

OUT = queens


all: $(OUT)


$(OUT): $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(OUT)


clean:
	rm -f *~ a.out $(OUT) *.o files.pdf


files.pdf:
	enscript -r -2 --highlight --line-numbers -o - $(SRC) Makefile | ps2pdf - files.pdf

pdf: files.pdf
