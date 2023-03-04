CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
SOURCES = testMap.cpp
SOURCES2 = testDict.py

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
	.\$(TARGET) | python $(SOURCES2)

