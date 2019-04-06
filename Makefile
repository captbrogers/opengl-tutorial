BUILD_TYPE := Debug
BUILD_DIR = builds/$(BUILD_TYPE)
BIN_DIR = bin/$(BUILD_TYPE)
CXXFLAGS = -std=c++14 -Wall -fPIC -pg
ifeq ($(BUILD_TYPE),Debug)
    CXXFLAGS += -g
endif
LDFLAGS = -lGL -lglfw -lGLEW -lSOIL

ALL: $(BIN_DIR)/opengl-tutorial

$(BIN_DIR)/opengl-tutorial: $(BUILD_DIR)/Main.o $(BIN_DIR)
	g++ -o $(BIN_DIR)/opengl-tutorial $(BUILD_DIR)/Main.o $(LDFLAGS)

$(BUILD_DIR)/Main.o: src/Main.cpp $(BUILD_DIR)
	g++ $(CXXFLAGS) -c src/Main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean

clean:
	rm -rf builds bin
