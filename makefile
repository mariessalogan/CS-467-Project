
CFLAGS = -g -Wall -std=c++11

spaceEscape: GameState.o Room.o Item.o main.cpp parser.o Consumable.o Container.o
	g++ $(CFLAGS) GameState.o Room.o Item.o main.cpp parser.o Consumable.o Container.o -o spaceEscape

Room.o: Room.hpp Room.cpp Item.hpp 
	g++ $(CFLAGS) -c Room.hpp Room.cpp Item.hpp 

Container.o: Container.hpp Container.cpp Item.hpp GameState.hpp
	g++ $(CFLAGS) -c Container.hpp Container.cpp Item.hpp GameState.hpp

Consumable.o: Consumable.hpp Consumable.cpp Item.hpp GameState.hpp
	g++ $(CFLAGS) -c Consumable.hpp Consumable.cpp Item.hpp GameState.hpp

Item.o: Item.hpp Item.cpp GameState.hpp
	g++ $(CFLAGS) -c Item.hpp Item.cpp GameState.hpp

GameState.o: GameState.hpp GameState.cpp Item.hpp Room.hpp Consumable.hpp Container.hpp
	g++ $(CFLAGS) -c GameState.hpp GameState.cpp Item.hpp Room.hpp Consumable.hpp Container.hpp

parser.o: parser.hpp parser.cpp
	g++ $(CFLAGS) -c parser.hpp parser.cpp
	
clean: 
	rm *.o *.gch spaceEscape
