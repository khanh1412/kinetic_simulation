CC = g++
CCFLAGS	= -std=c++17 -Wall -O3 -g
INFLAGS	= -I./include -I./opengl/include -I./opengl/include/vendor
LDFLAGS	= -lGL -lGLEW -lglfw

all:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) test.cc -o run

gl:
	$(CC) $(CCFLAGS) $(INFLAGS) $(LDFLAGS) testgl.cc ./libEngine.so -o run

clean:
	rm -f run
	rm -f *.so
