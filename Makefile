
EXE_FILE=main
IMPLEMENTATIONS=`find src/ | grep ".cpp"` 
OBJECT_DIR=objects
MAIN_FILE=main.cpp
CMAKE_BUILD=build

clean:
	rm -rf $(OBJECT_DIR)/* $(EXE_FILE) $(CMAKE_BUILD)/*

build-obj:
	g++ -c $(IMPLEMENTATIONS)
	mv *.o $(OBJECT_DIR)

build: build-obj
	g++ $(MAIN_FILE) $(OBJECT_DIR)/*.o -o $(EXE_FILE)

build-cmake:
	cd $(CMAKE_BUILD) && cmake .. && cmake --build .

run-cmake: build-cmake
	./$(CMAKE_BUILD)/$(EXE_FILE)

run: build
	./$(EXE_FILE)
