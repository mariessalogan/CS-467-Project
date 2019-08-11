/************************************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Last Modified: 7-28-19
* Class: CS 467 Capstone Summer '19
* Description: Test main file for midway project evalution.
************************************************************************************************/
#include "GameState.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Consumable.hpp"
#include "Container.hpp"
#include "EscapePod.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;


int main(){

	GameState * game = new GameState();
 	
 	char * path ;
 	char pathName [] = "/default";
 	char cwdName [1000];
 	memset(cwdName, '\0', sizeof(cwdName));
 	getcwd(cwdName, sizeof(cwdName));
 	strcat(cwdName, pathName);

 	path = cwdName;

 	cout << "Reading in GameState file from default folder." << endl;
 	cout << "***************************************************************************" << endl;
	game->readInGameState(path);


 	cout << "Reading in room files from default folder." << endl;
 	cout << "***************************************************************************" << endl;
	game->readInRooms(path);

	//Testing file read in
	cout << "Testing successful file read in." << endl;
	cout << "***************************************************************************" << endl;
	for(int i = 0 ; i < 17 ; i++){
		cout << game->getShipLocal(i)->getName() << endl;
		cout << "	" << "Long Desc: " << game->getShipLocal(i)->getLongDesc() << endl;
		cout << "	" << "Short Desc: " << game->getShipLocal(i)->getShortDesc() << endl;
		cout << "	" << "Visited: " << game->getShipLocal(i)->getVisited() << endl;
		cout << endl;
	}


	cout << "Testing GameState Private Variables:" << endl;
	cout << "***************************************************************************" << endl;
	cout << "Oxygen Levels: " << game->getOxygen() << endl;
	cout << "gameWon: " << game->getGameWon() << endl;
	cout << "gameQuit: " << game->getGameQuit() << endl;
	cout << "Inventory Size: " << game->getInventorySize() << endl;
	cout << "Game Intro: ";
	game->printIntro();
	cout << "Win Description: "; 
	game->printWinDesc();
	cout << "Loss Description: ";
	game->printLossDesc();

	
	game->setOxygen(1);
	cout << "Oxygen Set to 1: " << game->getOxygen() << endl;

	game->decOxygen();
	cout << "Oxygen decremented to 0: " << game->getOxygen() << endl;

	game->setInventorySize(7);
	cout << "Set inventory to 7: " << game->getInventorySize() << endl;

	game->incInventorySize();
	cout << "Increment inventory to 8: " << game->getInventorySize() << endl;

	game->decInventorySize();
	cout << "Decrement inventory to 7: " << game->getInventorySize() << endl;

	cout << "Testing Position, Current Room Name: " << game->getPosition()->getName() << endl;

	cout << "Testing Game Save functionality" << endl;

	game->_saveGame();

	Item * testItem = new Item();
	testItem->setName("Captain's Badge");
	testItem->setDesc1("whatever");
	testItem->setDesc2("ok");
	testItem->setPickup(true);
	testItem->setSecondVerb("run");
	testItem->setConditionMet(false);
	testItem->setLocationName("bunk");
	game->getPosition()->setItem(testItem);
	testItem->actionFunction(game, "shake");
	cout << "Desc2: " << testItem->getDesc2() << "\n";

    game->_takeItem("Captain's Badge");
	game->getPosition()->setItemCount(0);
    game->_printInventory();
	cout << "Item count in current Room: " << game->getPosition()->getItemCount() << endl;

	Item *drink = new Consumable();
	drink->setName("Coffee");
	drink->setConditionMet(false);
	cout << "drink name: " << drink->getName() << "\n";
	cout << "Oxygen before Consumable: " << game->getOxygen() << endl;
	drink->actionFunction(game, "drink");

	cout << "Oxygen incremented after Consumable: " << game->getOxygen() << endl;
 	
	Container *box = new Container();
	box->setName("Coffeemaker");
	box->setConditionMet(false);
	box->setItem(drink);
	box->actionFunction(game, "open");
	cout << "Item count in current Room: " << game->getPosition()->getItemCount() << endl;
	cout << "Items in room are: ";
	game->getPosition()->printItemNames();

	EscapePod *escape = new EscapePod();
	cout << "Room before escape pod: " << game->getGameWon() << "\n";
	escape->actionFunction(game, "verb");
	cout << "Room after escape pod: " << game->getGameWon() << "\n";


	//cout << "Item name in current Room: " << game->getPosition()->getItem("Employee Manual")->getName() << endl;

	//cout << "Testing printing item descriptions: " ;
	//game->printItems();

	
	return 0;
}
