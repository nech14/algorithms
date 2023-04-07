CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
SOURCES = myArray.cpp

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = m1.exe
else
	RM = rm
	TARGET = m1
endif

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)


clean:
	echo $(OS)
	$(RM) $(TARGET)



run: all

ifeq ($(OS), Windows_NT)
	.\$(TARGET)
else
	./$(TARGET)
endif
