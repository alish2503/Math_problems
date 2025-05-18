CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -I../math_dependencies/include
TARGET = main
SOURCES = main.cpp ../math_dependencies/src/Matrix.cpp ../math_dependencies/src/plot.cpp src/methods.cpp src/linal.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
