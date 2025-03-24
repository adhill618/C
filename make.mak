CC = gcc
CFLAGS = -Wall
SOURCES = test.c utility.c myAO.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
