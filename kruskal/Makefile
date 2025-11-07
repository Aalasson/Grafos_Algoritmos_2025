CXX = g++
CXXFLAGS = -O2 -std=gnu++11 -Wall

TARGET = kruskal
SRC = kruskal.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)
