/************************************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Last Modified: 8-13-19
* Class: CS 467 Capstone Summer '19
* Description: Test main file for midway project evalution.
************************************************************************************************/
#include "GameState.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;

int main() {

	cout << R"(
  ____                    ____                         _____                            
 |  _ \  ___  ___ _ __   / ___| _ __   __ _  ___ ___  | ____|___  ___ __ _ _ __   ___ _ 
 | | | |/ _ \/ _ \ '_ \  \___ \| '_ \ / _` |/ __/ _ \ |  _| / __|/ __/ _` | '_ \ / _ (_)
 | |_| |  __/  __/ |_) |  ___) | |_) | (_| | (_|  __/ | |___\__ \ (_| (_| | |_) |  __/_ 
 |____/ \___|\___| .__/  |____/| .__/ \__,_|\___\___| |_____|___/\___\__,_| .__/ \___(_)
           _____ |_|          _|_|_                                _      |_|           
          |_   _| |__   ___  | ____|___  ___ __ _ _ __   ___ _ __ (_)_ __   __ _        
            | | | '_ \ / _ \ |  _| / __|/ __/ _` | '_ \ / _ \ '_ \| | '_ \ / _` |       
            | | | | | |  __/ | |___\__ \ (_| (_| | |_) |  __/ | | | | | | | (_| |       
            |_| |_| |_|\___| |_____|___/\___\__,_| .__/ \___|_| |_|_|_| |_|\__, |       
                                                 |_|                       |___/  
)" << endl << endl;

	GameState * game = new GameState();
	bool menu = false;
	char * path;
	bool gameOver = false;
	
 	char cwdName [1000];
	memset(cwdName, '\0', sizeof(cwdName));
	getcwd(cwdName, sizeof(cwdName));

	cout << "\t1) New Game" << endl;
	cout << "\t2) Load Game" << endl;
	cout << "\t3) Exit " << endl << endl;

	while(!menu){
		string menuChoice;

		cout << "> Select option 1, 2, or 3: ";

		getline(cin, menuChoice);

		if(menuChoice == "1"){
			char newPathName [] = "/default";
		 	strcat(cwdName, newPathName);
 			path = cwdName;
			menu = true;
		}
		else if(menuChoice == "2"){
			char savePathName [] = "/saves";
 			strcat(cwdName, savePathName);
 			path = cwdName;
			menu = true;
		}
		else if(menuChoice == "3"){
			exit(0);
		}
		else{
			cout << "Invalid Entry..." << endl;
		}
	}
//--------------------------------------------------------------------
	
	game->readInGameState(path);
	game->readInRooms(path);
	game->readInItems(path);
	game->setItemLocations();

	cout << string(5, '\n');

	game->printIntro();

	//sleep(6);

	while(gameOver == false){

		string input; 
		vector<string> parsedLine;
		
		game->printCurRoomDesc();

		//PRINT STATEMENT FOR DEBUGGING
		cout << "Current room Name: " << game->getPosition()->getName() << endl;
		cout << "O2 Level: " << game->getOxygen() << endl;
		
		//game->printItemsForAllRooms();
		//game->printAllItems();

		cout << endl;
		game->getPosition()->printItemNames();
		cout << endl;
		game->getPosition()->printFeatureNames();
		cout << endl;
		game->printExits();


		cout << "> ";

		getline(cin, input);

		cout << "\n";

		parsedLine = parse(input, ' ');

		game->enactVerb(parsedLine, game);

		input.clear();

		//Check O2 Stat
		if(game->getOxygen() <= 0){
			cout << "ALERT ALERT!!! OXYGEN LEVELS NOW TOO LOW TO MAINTAIN LIFE SUPPORT!!!" << endl << endl;
			cout << "Unable to escape in time you slowly lose conciousness and die as the last molecules of oxygen vent from the ship." << endl;
			game->setGameLost(true);
		}

		//Command Center Alein
		if(game->getPosition()->getName() == "command center"){
			
			int requirements = 0;

			
			if(game->_checkInventory("phaser") != NULL){
				requirements++;
			}
			if(game->_checkInventory("charger") != NULL){
				requirements++;
			}
			if(game->_checkInventory("armor") != NULL){
				requirements++;
			}
			if(game->_checkInventory("goggles") != NULL){
				requirements++;
			}

			if(requirements == 4){
				cout << "You enter the bright room of the command center. You see the captain’s chair in the center of the room, and the pilots desk is filled with dinosaurs  One of the T-rexes looked like he had suddenly but inevitably betrayed a stegosaurus. You see movement on the left side of the room thanks to your thermal goggles. As soon as you notice the heat signature of the alien, it lands a blow across your chest. Luckily you are wearing the armor that you found earlier.  His claw bounces off the armor, and you swing your phaser up in response. You squeeze the trigger twice, just as you were trained and they both land squarely between the alien’s eyes. The alien falls over dead." << endl;
			}
			else{
				cout << "You enter the bright room of the command center. You see the captain’s chair in the center of the room, and the pilots desk is filled with dinosaurs. One of the T-rexes looked like he had suddenly but inevitably betrayed a stegosaurus. You are suddenly knocked back and there is a white hot pain across your chest. You look down and see blood gushing from your chest, it looks like a claw made the wound. “There must be an alien in here,” is your last thought as you fade away, your last moments spent in confusion." << endl;
				game->setGameLost(true);
			}
			
		}
		//Check if in the escape pod
		else if(game->getPosition()->getName() == "escape pod"){

			cout << "Safety at last! You stumble into the escape pod, where there is an ergonomic chair that will fold out into a hibernation bed when activated. Someone has thoughtfully placed a bottle of vodka with a glass next to the chair, likely a soldier was using the pod as a room for some private drinking. You look to the right and see a porthole that shows the vast expanse of space. You can see a planet surrounded by four moons far away, otherwise it’s a black blanket dotted with distant stars. You breathe a sigh of relief, sit in the chair and press the button to activate the escape pod.  You sip at the vodka as you watch the spaceship slowly get smaller out of the porthole. \n";
	

			game->setGameWon(true);
		}

		//Print Win / Loss / Quit message and end loop
		if(game->getGameWon() == true){
			gameOver = true; 
			game->printWinDesc();
			cout << "____    ____  ______    __    __     ____    __    ____  __  .__   __.  __   __   __\n\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  | |  | |  | |  | \n \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  | |  | |  | |  | \n  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  | |  | |  | |  | \n    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   | |__| |__| |__| \n    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__| (__) (__) (__)\n";	
		}
		else if(game->getGameLost() == true){
			gameOver = true;
			game->printLossDesc();
		}
		else if(game->getGameQuit() == true){
			gameOver = true; 
		}
	}


	return 0;
}

