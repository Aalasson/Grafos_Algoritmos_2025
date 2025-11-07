CXX = g++
CXXFLAGS = -O2 -std=gnu++11 -Wall

TARGET = kosaraju
SRC = kosaraju.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)
