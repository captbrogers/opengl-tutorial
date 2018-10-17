DEBUG_DIR=builds/Debug
BIN_DEBUG_DIR=bin/Debug
RELEASE_DIR=builds/Release
BIN_RELEASE_DIR=bin/Release
GL_FLAGS=-lGL -lglfw -lGLEW

debug:
	gcc -Wall -L./lib -fPIC -pg -g -c src/Main.cpp -o $(DEBUG_DIR)/Main.o
	g++ -o $(BIN_DEBUG_DIR)/opengl-tutorial \
	$(DEBUG_DIR)/Main.o \
	$(GL_FLAGS) -lSOIL

release:
	gcc -Wall -L./lib -fPIC -O2 -c src/Main.cpp -o $(RELEASE_DIR)/Main.o
	g++ -o $(BIN_RELEASE_DIR)/opengl-tutorial \
	$(RELEASE_DIR)/Main.o \
	-s $(GL_FLAGS) -lSOIL

.PHONY: clean

clean:
	rm -rf $(DEBUG_DIR)/*
	rm -rf $(BIN_DEBUG_DIR)/*
	rm -rf $(RELEASE_DIR)/*
	rm -rf $(BIN_RELEASE_DIR)/*
