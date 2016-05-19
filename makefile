OBJS = Player.o Ball.o Main.o Main_wrap.o
CC = g++
DEBUG = -g
OMPFLAGS = -fopenmp
CFLAGS = -Wall -fPIC -c
LFLAGS = -Wall -shared
BOOSTFLAGS = /usr/local/lib/boost/libboost_chrono.a /usr/local/lib/boost/libboost_system.a -std=c++14

_Main.so : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o _Main.so

Player.o : Point.h Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

Ball.o : Point.h Ball.cpp Ball.h
	$(CC) $(CFLAGS) Ball.cpp

Main.o : Point.h Player.h Main.h Main.cpp
	$(CC) $(CFLAGS) Main.cpp

Main_wrap.o : Main_wrap.c
	$(CC) $(CFLAGS) Main_wrap.c -I/usr/include/python2.7 -lpython2.7
	
clean : \rm *.o *~ p
