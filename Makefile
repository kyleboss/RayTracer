# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = `Magick++-config --cxxflags --cppflags` -g -Wall

# the build target executable:
TARGET = rayTracer

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp `Magick++-config --ldflags --libs` -I/opt/X11/include -lX11 -L/opt/X11/lib/ -L/usr/local/lib -Dcimg_use_png -lpthread -lpng -lz

clean:
	$(RM) $(TARGET)