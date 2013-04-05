CC = g++
CFLAGS = -O2 -g -Wall 

SOURCES = dmscreen.cpp dot-matrix.cpp dot-font.cpp dot-string.cpp dot-matrix-3d8.cpp record_3d8.cpp recorddm_3d8.cpp \
		  vfont_5x3.cpp vfont_6x3.cpp vfont_7x3.cpp vfont_7x4.cpp vfont_7x5.cpp vfont_8x3.cpp byte-reverse.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = dmscreen

HEADERS = common.h dot-matrix.h dot-font.h vfont_6x3.h dot-string.h dot-matrix-3d8.h record_3d8.h recorddm_3d8.h \
		  vfont_5x3.h vfont_6x3.h vfont_7x3.h vfont_7x4.h vfont_7x5.h vfont_8x3.h byte-reverse.h

$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) -o $@ $^ -lncursesw

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -rvf $(OBJECTS) $(TARGET)

