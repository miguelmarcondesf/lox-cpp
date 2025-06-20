CC = g++
CFLAGS = -Iinclude -Wall -Wextra -std=c++11
SRC = src/main.cpp
TARGET = lox-cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
