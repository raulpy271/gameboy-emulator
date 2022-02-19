
EXE_FILE=main
CMAKE_BUILD=build
TEST_EXE=tests/unit_test

clean:
	rm -rf  $(EXE_FILE) $(CMAKE_BUILD)/*

generate-buildsystem: 
	cd $(CMAKE_BUILD) && cmake ..

build-cmake:
	 cmake --build $(CMAKE_BUILD)

build-tests:
	cd $(CMAKE_BUILD) && make unit_test

run: build-cmake
	./$(CMAKE_BUILD)/$(EXE_FILE)

run-tests: build-tests
	./$(CMAKE_BUILD)/$(TEST_EXE)

