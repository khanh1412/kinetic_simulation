CC = g++
CCFLAGS	= -std=c++17 -Wall -O3
INFLAGS	= -I./include
LDFLAGS	= 

all:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) test.cc -o run
	./run
	rm -f run
	python3 test.py

clean:
	rm -f run
	rm -f *.so
