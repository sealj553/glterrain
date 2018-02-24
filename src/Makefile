TARGET := glterrain

CXX := g++

#debug
#CXXFLAGS := -std=c++17 -g -O2 -Wall -Wfatal-errors -MMD -fsanitize=thread
#LDLIBS := -lpthread -lGL -lGLEW -lglfw -fsanitize=thread

CXXFLAGS := -std=c++17 -O2 -Wall -Wfatal-errors -MMD
LDLIBS := -lpthread -lGL -lGLEW -lglfw -lSOIL

srcfiles := $(shell find . -maxdepth 2 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(TARGET)

$(TARGET): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(objects) $(LDLIBS)

clean:
	rm -f $(objects) $(TARGET) *.d

-include *.d
