# Минимальный Makefile без CMakeCache.txt
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
SRC = ../src/canvas.cpp ../src/draw_svg.cpp ../src/file.cpp ../src/getInfo.cpp ../src/object.cpp ../src/test_draw_des_tableaux.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = test_fonc3

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
