CC = g++
CFLAGS = -Wall -std=c++11
TARGET = masterMind

all: $(TARGET)

$(TARGET): play.cpp $(TARGET).cpp $(TARGET).h
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)
