
CFLAGS = -g -Wall -std=c++11

mainLoopTest: GameState.o Room.o Item.o mainLoopTest.cpp parser.o CommandCenter.o Holodeck.o
	g++ $(CFLAGS) GameState.o Room.o Item.o mainLoopTest.cpp parser.o CommandCenter.o Holodeck.o -o mainLoopTest

mainTest: GameState.o Room.o Item.o mainTest.o parser.o Consumable.o Container.o EscapePod.o
	g++ $(CFLAGS) GameState.o Room.o Item.o mainTest.o parser.o Consumable.o  Container.o EscapePod.o -o mainTest

mainTest.o: mainTest.cpp GameState.hpp Item.hpp Room.hpp Holodeck.hpp CommandCenter.hpp  Consumable.hpp Container.hpp EscapePod.hpp
	g++ $(CFLAGS) -c mainTest.cpp GameState.hpp Item.hpp Room.hpp Holodeck.hpp CommandCenter.hpp Consumable.hpp Container.hpp EscapePod.hpp

GameState.o: GameState.hpp GameState.cpp Item.hpp Room.hpp Holodeck.hpp CommandCenter.hpp EscapePod.hpp
	g++ $(CFLAGS) -c GameState.hpp GameState.cpp Item.hpp Room.hpp Holodeck.hpp CommandCenter.hpp EscapePod.hpp

Room.o: Room.hpp Room.cpp Item.hpp
	g++ $(CFLAGS) -c Room.hpp Room.cpp Item.hpp

Item.o: Item.hpp Item.cpp
	g++ $(CFLAGS) -c Item.hpp Item.cpp
	
Holodeck.o: Holodeck.hpp Holodeck.cpp
	g++ $(CFLAGS) -c Holodeck.hpp Holodeck.cpp

CommandCenter.o: CommandCenter.hpp CommandCenter.cpp
	g++ $(CFLAGS) -c CommandCenter.hpp CommandCenter.cpp

Consumable.o: Consumable.hpp Consumable.cpp
	g++ $(CFLAGS) -c Consumable.hpp Consumable.cpp

Container.o: Container.hpp Container.cpp
	g++ $(CFLAGS) -c Container.hpp Container.cpp

EscapePod.o: EscapePod.hpp EscapePod.cpp
	g++ $(CFLAGS) -c EscapePod.hpp EscapePod.cpp

parser.o: parser.hpp parser.cpp
	g++ $(CFLAGS) -c parser.hpp parser.cpp
	
clean: 
	rm *.o *.gch mainTest
