/*****************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Last Modified: 8-13-19
* Class: CS 467 Capstone Summer '19
* Description: Implementation of GameState class and functions. 
******************************************************************************/
#include "GameState.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Consumable.hpp"
#include "Container.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <cstdlib>

using namespace std;


/******************************************************************************************************************/
//Constructor and Destructor Functions
/**************************************************************************************************************/
//Demo Constructor
GameState::GameState(){

	int i;

	//Create blank rooms
	for(i = 0 ; i < 17 ; i++){
		
		ship[i] = new Room();
	}

	//Create blank regular items
	for(i = 0 ; i < 33 ; i++){
		regularItems[i] = new Item();
	}

	//Create blank containers
	for(i = 0 ; i < 5 ; i ++){
		containers[i] = new Container;
	}

	for(i = 0 ; i < 2 ; i ++){
		consumables[i] = new Consumable;
	}

	//Link rooms together.
	linkRooms();

	
	oxygen = -1; 
	gameWon = false;
	gameQuit = false;
	
	verbList[0] = "look";
	verbList[1] = "look at";
	verbList[2] = "go";
	verbList[3] = "take";
	verbList[4] = "drop";
	verbList[5] = "help";
	verbList[6] = "inventory";
	verbList[7] = "save";
	verbList[8] = "quit";
	verbList[9] = "open";
	verbList[10] = "close";
	verbList[11] = "push";
	verbList[12] = "turn on";
	verbList[13] = "turn off";
	verbList[14] = "drink";
	verbList[15] = "shake";
	verbList[16] = "read";
	verbList[17] = "scan";
	verbList[18] = "shoot";
	verbList[19] = "listen";

	//Changed by Mariessa except loss desc.  We may need to have 2? one for loss of oxygen and the other for death by alien
	intro = "You are a member of the Elite Space Force for the Federated Alliance. A month ago you departed from the capital to explore the uncharted reaches of the galaxy. Your mission was to search for other cultures and create diplomatic relations. Last night was your turn for night watch. After a normal night, you retired to your bed at 0500 hours. All is well... Or so you thought.\n" ;
	winDesc = "Safety at last! You stumble into the escape pod, where there is an ergonomic chair that will fold out into a hibernation bed when activated. Someone has thoughtfully placed a bottle of vodka with a glass next to the chair, likely a soldier was using the pod as a room for some private drinking. You look to the right and see a porthole that shows the vast expanse of space. You can see a planet surrounded by four moons far away, otherwise it’s a black blanket dotted with distant stars. You breathe a sigh of relief, sit in the chair and press the button to activate the escape pod. You sip at the vodka as you watch the spaceship slowly get smaller out of the porthole. \n";
	lossDesc = "You Lost, haha!";

	for(int i = 0 ; i < 8 ; i++){
		inventory[i] = NULL;
	}

	inventorySize = 0;
	
	//Need room data, need to build features / items first to pass in. 
	//ship = new Room()


	//*********************************************************************************************
	//Considerations for final constructor.
	//*********************************************************************************************
	//Open the directory from passed in pointer
	//Create a blank GameState object. 
	//Change GameState variables to match those of GameState file. 
	//If an item is present in GameState
		//Allocate memroy for the item, set item variables to match file data	//Allocated 16 room objects
	//Populate room objects with file data
	//If an item/feature is present in the room
		//Allocate memroy for the item, set item variables to match file data
	//Link rooms
}

//Destructor
GameState::~GameState(){
	

	int i;
	
	for(i = 0 ; i < 17 ; i++){
		free(ship[i]);
	}

	for(i = 0 ; i < 33 ; i++){
		free(regularItems[i]);
	}


	for(i = 0 ; i < 5 ; i ++){
		free(containers[i]);
	}

	for(i = 0 ; i < 2 ; i ++){
		free(consumables[i]);
	}

}

void GameState::linkRooms(){

	//Bunk
	ship[0]->setSouth(ship[2]);

	//Captians Quarters
	ship[1]->setEast(ship[2]);

	//Set Break Room
	ship[2]->setNorth(ship[0]);
	ship[2]->setEast(ship[3]);
	ship[2]->setSouth(ship[5]);
	ship[2]->setWest(ship[1]);

	//Holodeck
	ship[3]->setWest(ship[2]);
	ship[3]->setEast(ship[4]);

	//Strategy Room
	ship[4]->setWest(ship[3]);
	ship[4]->setSouth(ship[6]);

	//Cafeteria
	ship[5]->setNorth(ship[2]);
	ship[5]->setEast(ship[6]);
	ship[5]->setSouth(ship[9]);

	//Hallway
	ship[6]->setNorth(ship[4]);
	ship[6]->setSouth(ship[10]);
	ship[6]->setWest(ship[5]);

	//Supply Closet
	ship[7]->setSouth(ship[11]);

	//Transporter Room
	ship[8]->setEast(ship[9]);
	ship[8]->setSouth(ship[12]);

	//Corridor
	ship[9]->setNorth(ship[5]);
	ship[9]->setSouth(ship[13]);
	ship[9]->setWest(ship[8]);

	//Armory
	ship[10]->setNorth(ship[6]);
	ship[10]->setEast(ship[11]);

	//Quartermaster
	ship[11]->setNorth(ship[7]);
	ship[11]->setSouth(ship[15]);
	ship[11]->setWest(ship[10]);

	//Command Center
	ship[12]->setNorth(ship[8]);
	ship[12]->setEast(ship[13]);
	ship[12]->setSouth(ship[16]);

	//MedBay
	ship[13]->setNorth(ship[9]);
	ship[13]->setWest(ship[12]);

	//Lab
	ship[14]->setEast(ship[15]);

	//Workshop
	ship[15]->setNorth(ship[11]);
	ship[15]->setWest(ship[14]);

	//Escape Pod
	ship[16]->setWest(ship[12]);

}

//Accepts a character pointer to the directory to read in files. 
//Populates gamestate object with file data. Finally it sets current 
//working directroy to main game folder. 
void GameState::readInGameState(char * path){
	int success = chdir(path);
	if(success == -1){
		cout << "error in chdir readInGameState." << endl;
	}

	string position;
	string oxygen;
	string inventorySize;
	fstream inputFile;

	inputFile.open("GameState.txt"); //Add error handling here. 
	
	getline(inputFile, position);
	getline(inputFile, oxygen);
	getline(inputFile, inventorySize);

	setPosition(getShipLocal(stoi(position)));
	setOxygen(stoi(oxygen));
	setInventorySize(stoi(inventorySize));

	//Move out of read in folder to main game directory. 
	success = chdir("..");
	if(success == -1){
		cout << "error in chdir readInGameState." << endl;
	}

}

//Accepts a character pointer to the directory to read in files. 
//Populates ship array with room data. Finally it sets current 
//working direcotry to main game folder. 
void GameState::readInRooms(char * path){

	int success = chdir(path);

	if(success == -1){
		cout << "error in chdir readInRooms" << endl;
	}

	string name;
	string longDesc;
	string shortDesc;
	string visitedString;
	string dead = "Null";
	string pushed = "Null";
	string filePrefix = "Room";
	string fileSuffix = ".txt";
	string fileName;
	fstream inputFile;

	//Setup to handle generic rooms currently. Need to rewrite for
	//holodeck and command center. 
	for(int i = 0 ; i < 17 ; i++){
		
		//Create room file names "Room0.txt"
		fileName = filePrefix + to_string(i) + fileSuffix;

		inputFile.open(fileName); //add error handling here!!!

		//Get file contents
		getline(inputFile, name);
		getline(inputFile, longDesc);
		getline(inputFile, shortDesc);
		getline(inputFile, visitedString);

		//Set room to file data
		ship[i]->setName(name);
		ship[i]->setLongDesc(longDesc);
		ship[i]->setShortDesc(shortDesc);

		if(visitedString == "true"){
			ship[i]->setVisited(true);
		}
		else{
			ship[i]->setVisited(false);
		}

		
		//Reset file name for next iteration
		fileName = "";

		inputFile.close();
	}

	//Return cwd to main game folder. 
	success = chdir("..");
	if(success == -1){
		cout << "error in chdir readInGameState." << endl;
	}

}

void GameState::readInItems(char * path){

	int i;
	int success = chdir(path);

	if(success == -1){
		cout << "error in chdir readInItems" << endl;
	}

	string name; 
	string desc1; 
	string desc2; 
	string pickup; 
	string secondVerb;
	string conditionMet;
	string locationName;
	string requirement;
	fstream inputFile;

	string itemPrefix = "Item";
	string containPrefix = "Contain";
	string consumePrefix = "Consume";
	string suffix = ".txt";
	string fileName = "";

	//Populate regular items array.
	for(i = 0 ; i < 33 ; i++){
		
		fileName = itemPrefix + to_string(i) + suffix; 
		
		inputFile.open(fileName);

		//Get file contents
		getline(inputFile, name);
		getline(inputFile, desc1);
		getline(inputFile, desc2);
		getline(inputFile, pickup);
		getline(inputFile, secondVerb);
		getline(inputFile, conditionMet);
		getline(inputFile, locationName);

		//Set data in item
		regularItems[i]->setName(name);
		regularItems[i]->setDesc1(desc1);
		regularItems[i]->setDesc2(desc2);

		if(pickup == "true"){
			regularItems[i]->setPickup(true);
		}
		else if(pickup == "false"){
			regularItems[i]->setPickup(false);
		}

		regularItems[i]->setSecondVerb(secondVerb);

		if(conditionMet == "true"){
			regularItems[i]->setConditionMet(true);
		}
		else if(conditionMet == "false"){
			regularItems[i]->setConditionMet(false);
		}

		regularItems[i]->setLocationName(locationName);

		fileName = "";
		
		inputFile.close();
	}

	//Populate consumables array.
	for(i = 0 ; i < 2 ; i++){
		
		fileName = consumePrefix + to_string(i) + suffix; 
		
		inputFile.open(fileName);

		//Get file contents
		getline(inputFile, name);
		getline(inputFile, desc1);
		getline(inputFile, desc2);
		getline(inputFile, pickup);
		getline(inputFile, secondVerb);
		getline(inputFile, conditionMet);
		getline(inputFile, locationName);

		//Set data in item
		consumables[i]->setName(name);
		consumables[i]->setDesc1(desc1);
		consumables[i]->setDesc2(desc2);

		if(pickup == "true"){
			consumables[i]->setPickup(true);
		}
		else if(pickup == "false"){
			consumables[i]->setPickup(false);
		}

		consumables[i]->setSecondVerb(secondVerb);

		if(conditionMet == "true"){
			consumables[i]->setConditionMet(true);
		}
		else if(conditionMet == "false"){
			consumables[i]->setConditionMet(false);
		}

		consumables[i]->setLocationName(locationName);

		fileName = "";
		
		inputFile.close();
	}

	//Populate containers
	for(i = 0 ; i < 5 ; i++){
		fileName = containPrefix + to_string(i) + suffix;

		inputFile.open(fileName);

		//Get file contents
		getline(inputFile, name);
		getline(inputFile, desc1);
		getline(inputFile, desc2);
		getline(inputFile, pickup);
		getline(inputFile, secondVerb);
		getline(inputFile, conditionMet);
		getline(inputFile, locationName);
		getline(inputFile, requirement);


		containers[i]->setName(name);
		containers[i]->setDesc1(desc1);
		containers[i]->setDesc2(desc2);

		if(pickup == "true"){
			containers[i]->setPickup(true);
		}
		else if(pickup == "false"){
			containers[i]->setPickup(false);
		}

		containers[i]->setSecondVerb(secondVerb);

		if(conditionMet == "true"){
			containers[i]->setConditionMet(true);
		}
		else if(conditionMet == "false"){
			containers[i]->setConditionMet(false);
		}

		containers[i]->setLocationName(locationName);
		containers[i]->setRequirement(requirement);

		fileName = "";
		
		inputFile.close();

	}

	//Return cwd to main game folder. 
	success = chdir("..");
	if(success == -1){
		cout << "error in chdir readInItems." << endl;
	}

}

//Sets item locations for regular item array, containers, and consumables. 
//Items must already be populated with file data before this function is called!
void GameState::setItemLocations(){

	int i ; 

	//Set containers
	for(i = 0 ; i < 5 ; i++){

		//Check ship, containers cannot be in inventory or in themselves.
		for(int j = 0 ; j < 17 ; j++){
			if((containers[i]->getLocationName()) == (ship[j]->getName())){

				//Check if item is feature or not
				if(containers[i]->getPickup() == false){
					ship[j]->setFeature(containers[i]);
					break;
				
				}
				else if(regularItems[i]->getPickup() == true){
					ship[j]->setItem(containers[i]);
					break;
					
				}
			}
		}
	}
		

	//Set regular items 
	for(i = 0 ; i < 33 ; i++){
		
		//Check if item is in inventory and place accordingly. 
		if(regularItems[i]->getLocationName() == "inventory"){

			int emptySlot = -1;

			//Find empty slot in inventory array
			for(int j = 0 ; j < 8 ; j++){
				if(inventory[j] == NULL){
					emptySlot = i;
	
				}
			}
			//Confirm that slot is found and item is not a feature.
			if(emptySlot != -1 && (regularItems[i]->getPickup() == true)){
				
				//Set inventory to item
				inventory[emptySlot] = regularItems[i];
			}
			else{
				cout << "Error on setItemLocation, adding to inventory." << endl;
			}
			
		}
		//If item is not in inventory it must be in a container or ship room.
		else{
			
			//Check containers
			for(int j = 0 ; j < 5 ; j++){
				if((regularItems[i]->getLocationName()) == (containers[j]->getName())){
					containers[j]->setItem(regularItems[i]); 
					break;
				}
			}
	

			//Check ship names
			for(int j = 0 ; j < 17 ; j++){
				if((regularItems[i]->getLocationName()) == (ship[j]->getName())){

					//Check if item is feature or not
					if(regularItems[i]->getPickup() == false){
						ship[j]->setFeature(regularItems[i]);
						break;
					}
					else if(regularItems[i]->getPickup() == true){
						ship[j]->setItem(regularItems[i]);
						break;
				
					}
				}
			}


		}
	}


	//Set consumables items 
	for(i = 0 ; i < 2 ; i++){
		
		//Check if item is in inventory and place accordingly. 
		if(consumables[i]->getLocationName() == "inventory"){

			int emptySlot = -1;

			//Find empty slot in inventory array
			for(int j = 0 ; j < 8 ; j++){
				if(inventory[j] == NULL){
					emptySlot = i;
				}
			}
			//Confirm that slot is found and item is not a feature.
			if(emptySlot != -1 && (consumables[i]->getPickup() == true)){
				
				//Set inventory to item
				inventory[emptySlot] = consumables[i];
			}
			else{
				cout << "Error on setItemLocation, adding to inventory." << endl;
			}
			
		}
		//If item is not in inventory but is not a feature check containers. 
		else{
			//Check containers
			for(int j = 0 ; j < 5 ; j++){
				if((consumables[i]->getLocationName()) == (containers[j]->getName())){
					containers[j]->setItem(consumables[i]);
					break;
				}
			}
	

			//Check ship names
			for(int j = 0 ; j < 17 ; j++){
				if((consumables[i]->getLocationName()) == (ship[j]->getName())){

					//Check if item is feature or not
					if(consumables[i]->getPickup() == false){
						ship[j]->setFeature(consumables[i]);
						break;
						
					}
					else if(consumables[i]->getPickup() == true){
						ship[j]->setItem(consumables[i]);
						break;
						
					}
				}
			}


		}
	}


}

void GameState::saveGameState(){
	
	//Build path to save folder
	char * path ; 
	char pathName [] = "/saves";
	char cwdName [1000];

	memset(cwdName, '\0', sizeof(cwdName));
	getcwd(cwdName, sizeof(cwdName));
	strcat(cwdName, pathName);
	path = cwdName;

	int success = chdir(path);
	if(success == -1){
		cout << "error in chdir in saveRooms" << endl;
	}

	string position;
	string oxygen;
	string inventorySize;
	
	string fileName = "GameState.txt"; 
	fstream outputFile;

	//Create the file
	outputFile.open(fileName, ios::out);

	//Determine array location of current position
	for(int i = 0 ; i < 17 ; i ++){
		if(ship[i] == getPosition()){
			position = to_string(i);
		}
	}

	oxygen = to_string(getOxygen());
	inventorySize = to_string(getInventorySize());

	outputFile << position << "\n";
	outputFile << oxygen << "\n";
	outputFile << inventorySize << "\n";

	outputFile.close(); 

	success = chdir("..");
	if(success == -1){
		cout << "error in chdir in saveGameState" << endl;
	}

}

//Changes current working directory to saves folder. Prints room data
//to files. Finally changes current working directory to main game
//folder. 
void GameState::saveRooms(){
	
	//Build the path to the save folder
	char * path ; 
	char pathName [] = "/saves";
	char cwdName [1000];

	memset(cwdName, '\0', sizeof(cwdName));
	getcwd(cwdName, sizeof(cwdName));
	strcat(cwdName, pathName);
	path = cwdName;

	int success = chdir(path);
	if(success == -1){
		cout << "error in chdir in saveRooms" << endl;
	}

	string name; 
	string longDesc; 
	string shortDesc;
	string visitedString;
	bool visited; 

	string filePrefix = "Room";
	string fileSuffix = ".txt";
	string fileName; 
	fstream outputFile;

	//Loop through ship
	for(int i = 0 ; i < 17 ; i++){

		//Create room file name. 
		fileName = filePrefix + to_string(i) + fileSuffix;

		//Create the file
		outputFile.open(fileName, ios::out); 

		name = ship[i]->getName();
		longDesc = ship[i]->getLongDesc();
		shortDesc = ship[i]->getShortDesc();
		visited = ship[i]->getVisited();

		if(visited == true){
			visitedString = "true";
		}
		else{
			visitedString = "false";
		}

		outputFile << name << "\n";
		outputFile << longDesc << "\n";
		outputFile << shortDesc << "\n";
		outputFile << visitedString << "\n";

	
		outputFile.close();

		fileName = "";

	}
	success = chdir("..");
	if(success == -1){
		cout << "error in chdir in saveRooms" << endl;
	}
}

void GameState::saveItems(){
	
	//Build the path to the save folder
	char * path ; 
	char pathName [] = "/saves";
	char cwdName [1000];

	memset(cwdName, '\0', sizeof(cwdName));
	getcwd(cwdName, sizeof(cwdName));
	strcat(cwdName, pathName);
	path = cwdName;

	int success = chdir(path);
	if(success == -1){
		cout << "error in chdir in saveItems" << endl;
	}
	
	string name; 
	string desc1; 
	string desc2;
	bool pickup;  
	string secondVerb;
	bool conditionMet;
	string location;
	string requirement;
	fstream outputFile;

	string itemPrefix = "Item";
	string containPrefix = "Contain";
	string consumePrefix = "Consume";
	string suffix = ".txt";
	string fileName = "";

	//Export regular items
	for(int i = 0 ; i < 33 ; i++){

		//Create item file name. 
		fileName = itemPrefix + to_string(i) + suffix;

		//Create the file
		outputFile.open(fileName, ios::out); 

		name = regularItems[i]->getName();
		desc1 = regularItems[i]->getDesc1();
		desc2 = regularItems[i]->getDesc2();
		pickup = regularItems[i]->getPickup();
		secondVerb = regularItems[i]->getSecondVerb();
		conditionMet = regularItems[i]->getConditionMet();
		location = regularItems[i]->getLocationName();

		outputFile << name << "\n";
		outputFile << desc1 << "\n";
		outputFile << desc2 << "\n";

		if(pickup == true){
			outputFile << "true\n" ;
		}
		else if(pickup == false){
			outputFile << "false\n";
		}

		outputFile << secondVerb << "\n";

		if(conditionMet == true){
			outputFile << "true\n";
		}
		else if(conditionMet == false){
			outputFile << "false\n";
		}

		outputFile << location << "\n";
	
		outputFile.close();

		fileName = "";

	}

	//Export consumables
	for(int i = 0 ; i < 2 ; i++){

		//Create item file name. 
		fileName = consumePrefix + to_string(i) + suffix;

		//Create the file
		outputFile.open(fileName, ios::out); 

		name = regularItems[i]->getName();
		desc1 = regularItems[i]->getDesc1();
		desc2 = regularItems[i]->getDesc2();
		pickup = regularItems[i]->getPickup();
		secondVerb = regularItems[i]->getSecondVerb();
		conditionMet = regularItems[i]->getConditionMet();
		location = regularItems[i]->getLocationName();

		outputFile << name << "\n";
		outputFile << desc1 << "\n";
		outputFile << desc2 << "\n";

		if(pickup == true){
			outputFile << "true\n" ;
		}
		else if(pickup == false){
			outputFile << "false\n";
		}

		outputFile << secondVerb << "\n";

		if(conditionMet == true){
			outputFile << "true\n";
		}
		else if(conditionMet == false){
			outputFile << "false\n";
		}

		outputFile << location << "\n";
	
		outputFile.close();

		fileName = "";

	}

	//Export containers
	for(int i = 0 ; i < 5 ; i++){
		
		//Create item file name. 
		fileName = containPrefix + to_string(i) + suffix;

		//Create the file
		outputFile.open(fileName, ios::out); 

		name = containers[i]->getName();
		desc1 = containers[i]->getDesc1();
		desc2 = containers[i]->getDesc2();
		pickup = containers[i]->getPickup();
		secondVerb = containers[i]->getSecondVerb();
		conditionMet = containers[i]->getConditionMet();
		location = containers[i]->getLocationName();
		requirement = containers[i]->getRequirement();

		outputFile << name << "\n";
		outputFile << desc1 << "\n";
		outputFile << desc2 << "\n";

		if(pickup == true){
			outputFile << "true\n" ;
		}
		else if(pickup == false){
			outputFile << "false\n";
		}

		outputFile << secondVerb << "\n";

		if(conditionMet == true){
			outputFile << "true\n";
		}
		else if(conditionMet == false){
			outputFile << "false\n";
		}

		outputFile << location << "\n";
		
		outputFile << requirement << "\n";

		outputFile.close();

		fileName = "";

	}
	success = chdir("..");
	if(success == -1){
		cout << "error in chdir in saveRooms" << endl;
	}
}

/******************************************************************************************************************/
//Getter functions
/******************************************************************************************************************/

//Testing function.
Room * GameState::getShipLocal(int roomNum){
	if(roomNum > -1 && roomNum < 17){
		return ship[roomNum];
	}
	return NULL;
}

//Return pointer to current room.
Room * GameState::getPosition(){
	return position;
}

//Return current O2 level.
int GameState::getOxygen(){
	return oxygen;
}

//Return game win bool.
bool GameState::getGameWon(){
	return gameWon;
}

//Return game lost bool. 
bool GameState::getGameLost(){
	return gameLost;
}

//Return game quit bool. 
bool GameState::getGameQuit() {
	return gameQuit;
}

//Get number of items in inventory.
int GameState::getInventorySize(){
	return inventorySize;
}

/******************************************************************************************************************/
//Print functions
/******************************************************************************************************************/
//Print game intro.
void GameState::printIntro() {
	cout << intro << endl;
	return;
}

//Print adjacent room names to inform player of exits
void GameState::printExits(){
	
	cout << "\n";
	cout << "The room exits are:" << endl ; 

	if(position->getNorth() != NULL){
		cout << "North to the " << position->getNorth()->getName() << endl;
	}
	if(position->getEast() != NULL){
		cout << "East to the " << position->getEast()->getName() << endl;
	}
	if(position->getSouth() != NULL){
		cout << "South to the " << position->getSouth()->getName() << endl;
	}
	if(position->getWest() != NULL){
		cout << "West to the " << position->getWest()->getName() << endl;
	}
	cout << endl;


}

//Print game won description.
void GameState::printWinDesc() {
	cout << winDesc << endl;
	return;
}

//Print game lost / game over description
void GameState::printLossDesc() {
	cout << lossDesc << endl;
	return;
}

//Check if a room has been visited, print correct description 
//then update visited bool. 
void GameState::printCurRoomDesc() {

	if (position->getVisited() == false) {
		cout << "\n" << position->getLongDesc() << endl;
		position->setVisited(true);
	}
	else {
		cout << "\n" << position->getShortDesc() << endl;
	}

	cout << endl;
}

void GameState::printRoomItems(){
	
	position->printItemNames();
	return;
}

void GameState::printRoomFeatures(){
	
	position->printFeatureNames();
	return;
}

void GameState::printItemsForAllRooms(){

	cout << "----Items by room----" << endl;
	for(int i = 0 ; i < 17 ; i ++){
		cout << "-----Room: " << ship[i]->getName() << "----" << endl;
		cout << "Items\n" << endl;
		ship[i]->printItemNames();
		cout << endl;
		cout << "Freatures\n" << endl;
		ship[i]->printFeatureNames();
		cout << endl;
	}
}

void GameState::printAllItems(){

	cout << "----Regular Items----" << endl;
	for(int i = 0 ; i < 33 ; i++){
		cout << "Name: " << regularItems[i]->getName() << endl;
		cout << "	Target Room: " << regularItems[i]->getLocationName() << endl;
	}
	cout << "----Containers----" << endl;
	for(int i = 0 ; i < 5 ; i++){
		cout << "Name: " << containers[i]->getName() << endl;
		cout << "	Target Room: " << containers[i]->getLocationName() << endl;
	}
	cout << "----Consumables----" << endl;
	for(int i = 0 ; i < 2 ; i++){
		cout << "Name: " << consumables[i]->getName() << endl;
		cout << "	Target Room: " << consumables[i]->getLocationName() << endl;
	}
}

/******************************************************************************************************************/
//Setter / Modifier functions
/******************************************************************************************************************/

//Change current position pointer.
void GameState::setPosition(Room * newRoom){
	position = newRoom; 
	return;
}

//Change oxygen level.
void GameState::setOxygen(int oxygenLevel){
	oxygen = oxygenLevel;
	return;
}

//Decrement oxygen by one, called after player moves rooms.
void GameState::decOxygen(){
	if(oxygen > 0){
		oxygen -= 1;
	}
	return;
}

//Set gameWon bool
void GameState::setGameWon(bool state){
	gameWon = state;
}

//Set gameLost bool
void GameState::setGameLost(bool state){
	gameLost = state;
}

//Set gameQuit bool 
void GameState::setGameQuit(bool state){
	gameQuit = state; 
}


//Set inventory size to specific value.
void GameState::setInventorySize(int numItems){
	inventorySize = numItems;
	return;
}


//Increment number of items in inventory, used in pickup commands.
void GameState::incInventorySize(){
	if(inventorySize < 8){
		inventorySize += 1;
	}
	return;
}

//Decrement number of items in inventory, used in drop commands.
void GameState::decInventorySize(){
	if(inventorySize > 0){
		inventorySize -= 1;
	}
	return;
}



/******************************************************************************************************************/
//Parser Functions
/******************************************************************************************************************/



//Checks if a particular feature is present in the current room. Returns
//a pointer to the feature if present, otherwise it returns NULL.
Item * GameState::_checkForFeature(string noun){
	return position->getFeature(noun);
}

//Checks if a particular item is present in the current room. Returns a
//pointer to the item if present, otherwise it returns NULL.
Item * GameState::_checkForItem(string noun){
	return position->getItem(noun);
}

//Checks if an item is in inventory, returns a pointer to the item if found, 
//otherwise it returns NULL;
Item * GameState::_checkInventory(string noun){

	int i;

	for(i = 0; i < 8 ; i++){
		if(inventory[i] != NULL){
			if(inventory[i]->getName() == noun){
				return inventory[i];
			}
		}
	}

	return NULL;
}

//Check if a parsed noun referes to the current room name. Return true if match, false otherwise.
bool GameState::_checkCurrentRoom(string noun){

	if(position->getName() == noun){
		return true;
	}
	else{
		return false;
	}
}

//Include function for checking adjacent rooms?

//Prints long room description
void GameState::_look(){
	cout << position->getLongDesc() << endl;
	return;
}

//Checks to see if noun is a feature, item in the room, 
//or item in inventory. If the item is found a success 
//message is printed along with the item desc1. Otherwise,
//a generic "you cannot look at that" message is printed. 
void GameState::_lookAt(string noun){

	Item * lookedItem = NULL;
	string successLook = "You look at the ";
	string failedLook = "You cannot look at that.";

	//Check if noun is a feature.
	if(_checkForFeature(noun) != NULL){
		lookedItem = _checkForFeature(noun);
	}
	//Check if noun is an item in room.
	else if(_checkForItem(noun) != NULL){
		lookedItem = _checkForItem(noun);
	}
	//Check if noun is an item in inventory.
	else if(_checkInventory(noun) != NULL){
		lookedItem = _checkInventory(noun);
	}

	//Print corresponding result
	if(lookedItem != NULL){
		cout << successLook << noun << endl;
		cout << lookedItem->getDesc1() << endl;
	}
	else{
		cout << failedLook << endl;
	}
}

//How is parser sending room data to this function?
void GameState::_moveRooms(string noun){


	//Check if noun is cardinal direction AND that direction is not null OR that the noun is
	//the name of the room at that location. 
	if((noun == "north" && position->getNorth() != NULL) || (noun == position->getNorthName())){
		position = position->getNorth();
		decOxygen();
	}
	else if((noun == "east" && position->getEast() != NULL) || (noun == position->getEastName())){
		position = position->getEast();
		decOxygen();
	}
	else if((noun == "south" && position->getSouth() != NULL) || (noun == position->getSouthName())){
		position = position->getSouth();
		decOxygen();
	}
	else if((noun == "west" && position->getWest() != NULL) || (noun == position->getWestName())){
		position = position->getWest();
		decOxygen();
	}
	else{
		cout << "You cannot go that way!" << endl;
	}
	

}

//Take item whose name matches the passed in noun from room and place in inventory. 
void GameState::_takeItem(string noun){

	Item * itemToTake = NULL;

	//Get item from room.
	itemToTake = _checkForItem(noun);

	if(itemToTake != NULL){
		
		int emptySlot = -1;


		//Find an empty slot in the inventory array	
		for(int i = 0 ; i < 8 ; i++){
			if(inventory[i] == NULL){
				emptySlot = i;
				break;
			}

		}

		inventory[emptySlot] = itemToTake;
		incInventorySize();

		//Set room itemArr pointer to null and decrement itemCount in room
		position->setItemToNull(noun);

		//Change the location name in the item. 
		itemToTake->setLocationName("inventory");

		cout << "You picked up the " << noun << endl;

		itemToTake = NULL;
	}
	else{
		cout << "There is no " << noun << " to pick up!" << endl;
	}

	return;
}

//Drop an item whose name matches the passed in noun from inventory into the room.
void GameState::_dropItem(string noun){
	
	Item * itemToDrop = NULL;

	//Get item from inventory.
	itemToDrop = _checkInventory(noun);

	if(itemToDrop != NULL){

		for(int i = 0 ; i < 8 ; i++){
			//Find item and remove from inventory array.
			if(inventory[i] != NULL){
				if(inventory[i]->getName() == noun){
					inventory[i] = NULL;
					decInventorySize();
				}	
			}
			
				
		}
	
		//Drop item in the room
		position->setItemToPointer(itemToDrop);

		//Change the location name in the item to the current room name.
		itemToDrop->setLocationName(position->getName());

		cout << "You dropped the " << noun << endl;

		itemToDrop = NULL;
	}
	else{
		cout << "You do not have a " << noun << " to drop!" << endl;
	}

	return;
}

//Print the list of acceptable verbs to the user. 0
void GameState::_help(){

	int i;
	
	cout << "Here is a list of acceptable game commands:" << endl;
	
	for(i = 0 ; i < 19 ; i++){
		cout << verbList[i] << ", ";
	}
	cout << verbList[19]<< "." << endl;

	return;
}

//Print the contents of the player inventory. 
void GameState::_printInventory(){

	int i;

	cout << "You have the following items in inventory:" << endl;

	//Check for holes in inventory array due to item drops. 
	for(i = 0 ; i < 8 ; i++){
		if(inventory[i] != NULL){
			cout << inventory[i]->getName() << endl;
		}
	}

	return;
}

//Figure out file structure. Need to export GameState and room data.
void GameState::_saveGame() {
	saveGameState();
	saveRooms();
	saveItems();
	cout << "Game Saved!" << endl;
}


void GameState::_quitGame() {
	
	cout << "Are you sure you want to quit? Y/n" << endl;
	char anwser; 
	bool invalidResp = true;

	while(invalidResp){
		
		cout << "\n>";
		cin >> anwser;

		if(anwser == 'Y'){
		cout << "Thanks for playing!" << endl;
		gameQuit = true;
		invalidResp = false;
		}
		else if(anwser == 'n'){
			invalidResp = false;
		}
		else{
			cout << "Please type Y for yes or n for no." << endl;
		}
	}
	
	return;
}


//Check with Maressia on how this is passing to items. 
void GameState::_itemAction(string verb, string noun, GameState * game) {

	Item * subject = NULL;
	
	//Find item to act upon
	if(_checkInventory(noun) != NULL){
		subject = _checkInventory(noun);
	}
	else if(_checkForItem(noun) != NULL){
		subject = _checkForItem(noun);
	}
	else if(_checkForFeature(noun) != NULL){
		subject = _checkForFeature(noun);
	}

	//Call item function.
	if(subject != NULL){
		subject->actionFunction(game, verb);
	}
	else{
		cout << "You cannot do that!" << endl;
	}

	return;
}


void GameState::enactVerb(vector<string> parsedInput, GameState * game) {

	string noun;
	string verb; 

	//Copy contents from vector.
	if(parsedInput.size() == 2){
		verb = parsedInput[0];
		noun = parsedInput[1];
		cout << "noun in enactVerb: " << noun << endl ;
		cout << "verb in enactVerb: " << verb << endl << endl;
	}
	else{
		verb = parsedInput[0];
		cout << "verb in enactVerb: " << verb << endl << endl;
	}

	

	//verb == look
	if (verb == "look") {
		_look();
	}
	else if (verb == "look at") {
		_lookAt(noun);
	}
	else if (verb == "go") {
		_moveRooms(noun);
	}
	else if (verb == "take") {
		_takeItem(noun);
	}
	else if (verb == "drop") {
		_dropItem(noun);
	}
	else if (verb == "inventory") {
		_printInventory();
	}
	else if (verb == "help") {
		_help();
	}
	//Function not created yet.
	else if (verb == "save") {
		_saveGame();
	}
	else if (verb == "quit") {
		_quitGame();
	}
	else if(verb == "invalid"){
		cout << "You cannot do that!" << endl;
	}
	
	else{
		_itemAction(verb, noun, game);
	}

}
