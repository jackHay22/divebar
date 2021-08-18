TARGET = divebar.out
SOURCES := $(wildcard src/*.cc) $(wildcard src/*/*.cc)
SOURCES += $(wildcard src/*/*/*.cc) $(wildcard src/*/*/*/*.cc)
BUILD_DIR = build
OBJECTS = $(SOURCES:.cc=.o)
BUILDOBJECTS := $(patsubst %,$(BUILD_DIR)/%,$(SOURCES:.cc=.o))
CFLAGSO = -std=c++17 -O2 -g -Wall
LDFLAGS := -lSDL2 -lSDL2_image

.PHONY: all clean
all: $(TARGET)

%.o: %.cc
	mkdir -p $(BUILD_DIR)/$(dir $@)
	g++ $(CFLAGSO) -o $(BUILD_DIR)/$@ -c $^
$(TARGET): $(OBJECTS)
	g++ $(CFLAGSO) $(BUILDOBJECTS) -o $@ $(LDFLAGS)
clean::
	rm -r build || true
	rm $(TARGET) || true
