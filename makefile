OBJS = Player.o Ball.o Main.o
CC = g++
DEBUG = -g
CFLAGS = -fopenmp -Wall -c
LFLAGS = -fopenmp -Wall
BOOSTFLAGS = /usr/local/lib/boost/libboost_chrono.a /usr/local/lib/boost/libboost_system.a -std=c++14

a : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o a $(BOOSTFLAGS)

Player.o : Point.h Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp $(BOOSTFLAGS)

Ball.o : Point.h Ball.cpp Ball.h
	$(CC) $(CFLAGS) Ball.cpp $(BOOSTFLAGS)

Main.o : Point.h Player.h Main.cpp
	$(CC) $(CFLAGS) Main.cpp $(BOOSTFLAGS)

clean: \rm *.o *~ p
