
EXE_FILE=main.out

build:
	g++ main.cpp -o $(EXE_FILE)

run: build
	./$(EXE_FILE)
	rm *.out
