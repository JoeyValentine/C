CC = gcc
CFLAGS = -W -Wall
TARGET = 20141510.out
SRCS = 20141510.h 20141510.c
OBJECTS = 20141510.o

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

$(OBJECTS): 20141510.c
	$(CC) -c 20141510.c $(CFLAGS)

clean:
	rm -rf *.o *.out
