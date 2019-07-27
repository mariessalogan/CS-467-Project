
CFLAGS = -g -c -Wall -std=c++11

mainTest: gameState.o mainTest.cpp
	g++ -g -Wall -std=c++11 gameState.o mainTest.cpp -o mainTest

gameState.o: gameState.hpp gameState.cpp 
	g++ $(CFLAGS) gameState.hpp gameState.cpp 


clean: 
	rm *.o mainTest