/*****************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Date: 7/15/19
* Class: CS 467 Capstone Summer '19
* Description: Implementation of gameState class and functions. 
******************************************************************************/
#include "gameState.hpp"

//Constructor
gameState::gameState(char * loadDir){

}

//Destructor
gameState::~gameState(){

}

//Return pointer to current room.
Room * gameState::getPosition(){
	return position;
}

//Return current O2 level.
int gameState::getOxygen(){
	return oxygen;
}

//Return game win bool.
bool gameState::getGameWon(){
	return gameWon;
}

//Get number of items in inventory.
int gameState::getInventorySize(){
	return inventorySize;
}

//Print game intro.
void gameState::printIntro(){
	cout << gameIntro << endl;
	return;
}

//Change current position pointer.
void gameState::setPosition(Room * newRoom){
	position = newRoom; 
	return;
}

//Change oxygen level.
void gameState::setOxygen(int oxygenLevel){
	oxygen = oxygenLevel;
	return;
}

//Decrement oxygen by one, called after player moves rooms.
void gameState::decOxygen(){
	if(oxygen > 0){
		oxygen -= 1;
	}
	return;
}

//Set inventory size to specific value.
void gameState::setInventorySize(int numItems){
	inventorySize = numItems;
	return;
}


//Increment number of items in inventory, used in pickup commands.
void gameState::incInventorySize(){
	if(inventorySize < 8){
		inventorySize += 1;
	}
	return;
}

//Decrement number of items in inventory, used in drop commands.
void gameState::decInventorySize(){
	if(inventorySize > 0){
		inventorySize -= 1;
	}
	return;
}


//Checks if a particular feature is present in the current room. Returns
//true if present, false otherwise.
Item * gameState::_checkForFeature(string noun){

	int i;

	//The number 8 refects the current array size in Rooms.hpp, this is larger than necessary. 
	for(i = 0; i < 8 ; i++){
		if(position->features[i]->name == noun){
			return position->features[i];
		}
	}

	return NULL;
}

//Checks if a particular item is present in the current room. Returns true
//if present, false otherwise.
Item * gameState::_checkForItem(string noun){

	int i;

	for(i = 0; i < 8 ; i++){
		if(position->Items[i]->name == noun){
			return position->Items[i];
		}
	}

	return NULL;
}

//Check if parsed noun is an item in inventory. If 
Item * gameState::_checkInventory(string noun){

	int i;

	for(i = 0; i < inventorySize ; i++){
		if(inventory[i]->name == noun){
			return inventory[i];
		}
	}

	return NULL;
}

//Check if a parsed noun referes to the current room name. Return true if match, false otherwise.
bool gameState::_checkCurrentRoom(string noun){

	if(position->name == noun){
		return true;
	}
	else{
		return false;
	}
}

//Include function for checking adjacent rooms?

//Prints long room description
void gameState::_look(){
	cout << position->longDesc << endl;
	return;
}

//Checks to see if noun is a feature, item in the room, 
//or item in inventory. If the item is found a success 
//message is printed along with the item desc1. Otherwise,
//a generic "you cannot look at that" message is printed. 
void gameState::_lookAt(string noun){

	Item * lookedItem = NULL;
	string successLook = "You look at the ";
	string failedLook = "You cannot look at that."

	//Check if noun is a feature.
	if(_checkForFeature(noun) != NULL){
		lookedItem = _checkForFeature(noun);
	}
	//Check if noun is an item in room.
	else if(_checkForItem(noun) != NULL){
		lookedItem = _checkForItem(noun)
	}
	//Check if noun is an item in inventory.
	else if(_checkInventory(noun) != NULL){
		lookedItem = _checkInventory(noun);
	}

	//Print corresponding result
	if(lookedItem != NULL){
		cout << successLook << noun << endl;
		cout << lookedItem->desc1 << endl;
	}
	else{
		cout << failedLook << endl;
	}
}

//How is parser sending room data to this function?
void gameState::_moveRooms(){

}

//Take item whose name matches the passed in noun from room and place in inventory. 
void gameState::_takeItem(string noun){

	Item * itemToTake = NULL;
	int i;

	//Get item from room.
	itemToTake = _checkForItem(noun);

	if(itemToTake != NULL){

		incInventorySize();
		
		for(i = 0 ; i < 8 ; i++){
	
			//Find item inventory pointer, set to item.			
			if(inventory[i]->name == noun){
				inventory[i] = itemToTake;
			}

			//Find item room pointer, set to NULL
			if(position->Items[i]->name == noun){
				position->Items[i] == NULL;
			}
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
void gameState::_dropItem(string noun){
	Item * itemToDrop = NULL;
	int i;

	//Get item from inventory.
	itemToDrop = _checkInventory(noun);

	if(itemToDrop != NULL){

		decInventorySize();
		
		for(i = 0 ; i < inventorySize ; i++){
			
			if(inventory[i]->name == noun){
				inventory[i] = NULL;
			}

			if(position->Items[i] == NULL){
				position->Items[i] = itemToDrop;
			}
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
void gameState::_help(){

	int i;
	
	cout << "Here is a list of acceptable game commands:" << endl;
	
	for(i = 0 ; i < 10 ; i++){
		cout << verbList[i] << endl;
	}
	return;
}

void gameState::_printInventory(){

	int i;

	cout << "You have the following items in inventory:" << endl;

	//Check for holes in inventory array due to item drops. 
	for(i = 0 ; i < 8 : i++){
		if(inventory[i] != NULL){
			cout << inventory[i]->name << endl;
		}
	}

	return;
}


void enactVerb(string verb, string noun){

	

	//verb == look

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