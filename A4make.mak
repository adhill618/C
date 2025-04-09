

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = Assignment4
OBJS = main.o myDSlib.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c myDSlib.h
	$(CC) $(CFLAGS) -c main.c

myDSlib.o: myDSlib.c myDSlib.h
	$(CC) $(CFLAGS) -c myDSlib.c

clean:
	rm -f *.o $(TARGET)
