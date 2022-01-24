
EXE_FILE=main.out
IMPLEMENTATIONS=`find src/ | grep ".cpp"` 
OBJECT_DIR=objects
MAIN_FILE=main.cpp

clean:
	rm $(OBJECT_DIR)/* $(EXE_FILE)

build-obj:
	g++ -c $(IMPLEMENTATIONS)
	mv *.o $(OBJECT_DIR)

build: build-obj
	g++ $(MAIN_FILE) $(OBJECT_DIR)/*.o -o $(EXE_FILE)

run: build
	./$(EXE_FILE)
