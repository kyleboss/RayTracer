# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = rayTracer

all: $(TARGET)

$(TARGET): $(TARGET).cpp
<<<<<<< Updated upstream
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
=======
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp -I$HOME/include -L/usr/X11R6/lib -lX11
>>>>>>> Stashed changes

clean:
	$(RM) $(TARGET)