CFLAGS = -std=c++11 -m64 -O3 -flto -march=native -funroll-loops -fPIC -Wall -Wextra -pedantic -DNDEBUG
LIBS =

default:
	g++ $(CFLAGS) -c *.cpp Examples/*.cpp
	g++ -o main *.o $(LIBS)
	rm -f *.o

