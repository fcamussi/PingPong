
CC = gcc -Wall
CFLAGS = `pkg-config --cflags gtk+-2.0`
LIBS = `pkg-config --libs gtk+-2.0`


pingpong: main.o window.o pingpong.o graphics.o
	$(CC) -o pingpong main.o window.o pingpong.o graphics.o $(LIBS)

main.o: main.c window.h pingpong.h
	$(CC) $(CFLAGS) -c main.c

window.o: window.c window.h pingpong.h graphics.h types.h
	$(CC) $(CFLAGS) -c window.c

pingpong.o: pingpong.c pingpong.h window.h graphics.h types.h
	$(CC) $(CFLAGS) -c pingpong.c

graphics.o: graphics.c graphics.h pingpong.h
	$(CC) $(CFLAGS) -c graphics.c

clean:
	rm -f *.o pingpong
