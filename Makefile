CC = g++
CCFLAGS	= -std=c++17 -Wall -O3
INFLAGS	= -I./include
LDFLAGS	= 

all:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) test.cc -o run

clean:
	rm -f run
	rm -f *.so
