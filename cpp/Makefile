CC = g++
CFLAGS = -O2 -g -Wall 

SOURCES = dmscreen.cpp dot-matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = dmscreen

:$(TARGET)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -lncursesw

clean: 
	rm -rvf $(OBJECTS) $(TARGET)

