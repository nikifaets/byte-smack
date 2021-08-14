CC=gcc -std=c++17 -lstdc++fs
CXX=g++ -std=c++17 -lstdc++fs
RM=rm -f

SRCS=main.cpp filesystemIterator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: filesystemIterator

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS) 

main.o: main.cpp

filesystemIterator.o: main.cpp filesystemIterator.h filesystemIterator.cpp

clean:
	$(RM) $(OBJS)
