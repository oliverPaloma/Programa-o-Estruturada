CC = gcc
CFLAGS = -Wall
TARGET = cronograma

all: $(TARGET)

$(TARGET): main.o paloma.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o paloma.o

main.o: main.c paloma.h
	$(CC) $(CFLAGS) -c main.c

projeto.o: paloma.c paloma.h
	$(CC) $(CFLAGS) -c paloma.c

clean:
	rm -f *.o $(TARGET)
