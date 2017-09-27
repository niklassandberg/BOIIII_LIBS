OBJS = env_test.o BOENV.o arduinomock.o
CC = g++
DEBUG = 
CFLAGS = -Wall -DMOCK_ARDUINO -c $(DEBUG)
LFLAGS = -Wall -DMOCK_ARDUINO $(DEBUG)

env_test : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o env_test

BOENV.o : ../BOENV.h arduinomock.h
	$(CC) $(CFLAGS) ../BOENV.cpp

arduinomock.o : arduinomock.h arduinomock.cpp
	$(CC) $(CFLAGS) arduinomock.cpp

all : env_test

clean :
	rm -rf ./*.o env_test
