
CFLAGS = -g -Wall -std=c++11

mainTest: GameState.o Room.o Item.o mainTest.o
	g++ $(CFLAGS) GameState.o Room.o Item.o mainTest.o -o mainTest

mainTest.o: mainTest.cpp GameState.hpp Item.hpp Room.hpp
	g++ $(CFLAGS) -c mainTest.cpp GameState.hpp Item.hpp Room.hpp

GameState.o: GameState.hpp GameState.cpp Item.hpp Room.hpp
	g++ $(CFLAGS) -c GameState.hpp GameState.cpp Item.hpp Room.hpp

Room.o: Room.hpp Room.cpp Item.hpp
	g++ $(CFLAGS) -c Room.hpp Room.cpp Item.hpp

Item.o: Item.hpp Item.cpp
	g++ $(CFLAGS) -c Item.hpp Item.cpp
	
clean: 
	rm *.o *.gch mainTest