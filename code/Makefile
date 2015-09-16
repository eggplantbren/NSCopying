CFLAGS = -std=c++11 -m64 -O3 -flto -march=native -funroll-loops -fPIC -Wall -Wextra -pedantic -DNDEBUG
OBJECTS = RNG.o SpikeSlab.o Utils.o

default:
	g++ $(CFLAGS) -c *.cpp Examples/*.cpp
	g++ -o main main.o $(OBJECTS)
	g++ -o postprocess postprocess.o $(OBJECTS)
	rm -f *.o

