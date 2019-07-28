/*****************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Last Modified: 7-27-19
* Class: CS 467 Capstone Summer '19
* Description: Implementation of GameState class and functions. 
******************************************************************************/
#include "GameState.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


/******************************************************************************************************************/
//Constructor and Destructor Functions
/**************************************************************************************************************/
//Demo Constructor
GameState::GameState(){

	int i;
	
	//Update these once I get more data on room constructors. 
	for(i = 0 ; i < 16 ; i++){
		ship[i] = NULL;
	}
	position = NULL;

	oxygen = 100; 
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

	//Change this once I get info from Mariessa
	intro = "You are a member of the Elite Space Force for the Federated Alliance.  A month ago you departed from the capital to explore the uncharted reaches of the galaxy. Your mission was to search for other cultures and create diplomatic relations. Last night was your turn for night watch. After a normal night, you retired to your bed at 0500 hours. All is well... Or so you thought.\n" ;
	winDesc = "You Won!";
	lossDesc = "You Lost, haha!";

	for(i = 0 ; i < 8 ; i++){
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
	cout << "The destructor is now running." << endl;
}

/******************************************************************************************************************/
//Getter functions
/******************************************************************************************************************/

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
		cout << position->getLongDesc() << endl;
		position->setVisited(true);
	}
	else {
		cout << position->getShortDesc() << endl;
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

	for(i = 0; i < inventorySize ; i++){
		if(inventory[i]->getName() == noun){
			return inventory[i];
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
		
		for(int i = 0 ; i < 8 ; i++){
	
			//Find an empty slot in the inventory array	
			if(inventory[i] == NULL){
				inventory[i] = itemToTake;
				incInventorySize();
			}

			//Set room itemArr pointer to null and decrement itemCount in room
			position->setItemToNull(noun);
		}

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

		for(int i = 0 ; i < inventorySize ; i++){
			
			//Find item and remove from inventory array.
			if(inventory[i]->getName() == noun){
				inventory[i] = NULL;
				decInventorySize();
			}

			position->setItemToPointer(itemToDrop);
		}
		
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

}


void GameState::_quitGame() {
	gameQuit = true;

}


//Check with Maressia on how this is passing to items. 
void GameState::_itemAction(string verb, string noun, GameState game) {

}


void GameState::enactVerb(vector<string> parsedInput) {

	string noun;
	string verb; 

	//Copy contents from vector.
	if(parsedInput.size() == 2){
		verb = parsedInput[0];
		noun = parsedInput[1];
	}
	else{
		verb = parsedInput[0];
	}


	//verb == look
	if (verb == "look") {
		_look();
	}
	else if (verb == "lookAt") {
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

	}
	else if (verb == "quit") {
		_quitGame();
	}
	//Check with Hamiltion what the passed verb will be to call 
	//unique object functions. Check with Mareissa on how this is
	//called in item.
	else if (verb == "act") {

	}

	//verb == lookAt
		//Determine location of item
			//If item not present print no item message
		//Print item description

	//verb == move
		//Determine if noun refers to valid room
			//If invalid inform player
			//else Change position pointer
			//Decrement oxygen stat

	//verb == take
		//Find item in room
			//If not found print message
			//else Find open slot in inventory
			//Set empty inventory slot to point to item
			//Update inventorySize
			//Set item slot in room to null

	//verb == drop
		//Find item in inventory
		//Find open slot in room item array
		//Set empty room slot to point to item
		//Set inventory slot to null
		//decrement inventory size

	//verb == inventory
		//Loop through contents of inventory
		//Print a message
		//Print names of inventory items

	//verb == help
		//Print a message
		//Print list of game verbs. 

	//verb == save
		//Check for the existence of a save directory
		//If not present create it
		//Loop through rooms, print room data into individual file for each room
		//

	//verb == quit

	//verb == action



}
