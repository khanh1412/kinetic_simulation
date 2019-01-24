all:
	g++ -std=c++17 -I./include -Wall -O3 test.cc
clean:
	rm -f a.out
