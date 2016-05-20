OBJS = Player.o Ball.o Main.o Main_wrap.o
CC = g++
DEBUG = -g
OMPFLAGS = -fopenmp
CFLAGS = -Wall -fPIC -c
LFLAGS = -Wall -shared
BOOSTFLAGS = /usr/local/lib/boost/libboost_chrono.so /usr/local/lib/boost/libboost_system.so -std=c++14

_Main.so : $(OBJS)
	$(CC) $(OMPFLAGS) $(LFLAGS) $(OBJS) $(BOOSTFLAGS) -o _Main.so

Player.o : Point.h Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

Ball.o : Point.h Ball.cpp Ball.h
	$(CC) $(CFLAGS) Ball.cpp

Main.o : Point.h Player.h Main.h Main.cpp
	$(CC) $(OMPFLAGS) $(CFLAGS) Main.cpp $(BOOSTFLAGS)

Main_wrap.o : Main_wrap.c
	$(CC) $(CFLAGS) Main_wrap.c -I/usr/include/python2.7 -lpython2.7
	
clean : 
	\rm -f *.o
