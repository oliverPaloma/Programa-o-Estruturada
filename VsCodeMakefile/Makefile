CC = gcc
CFLAGS = -Wall
TARGET = cronograma

all: $(TARGET)

$(TARGET): main.o projeto.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o projeto.o

main.o: main.c projeto.h
	$(CC) $(CFLAGS) -c main.c

projeto.o: projeto.c projeto.h
	$(CC) $(CFLAGS) -c projeto.c

clean:
	rm -f *.o $(TARGET)
