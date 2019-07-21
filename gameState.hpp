/*****************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Date: 7/15/19
* Class: CS 467 Capstone Summer '19
* Description: Header file for the gameState class. 
******************************************************************************/
#include "Room.hpp"									
#include "Item.hpp"
#include <string>
#include <iostream>
#include <fstream>
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class gameState{

	private: 
		Room * ship [16];
		Room * position;
		int oxygen; 
		bool gameWon;
		string * verbList [10]; 
		string gameIntro;
		Item * inventory [8];
		int inventorySize;

	public: 
		gameState(char * loadDir); 						//Default constructor
		//_checkForSaveFile();							//Look for save directory, if found look for files. 
		~gameState();									//Deconstructor
		Room * getPosition(); 							//Return pointer to current room
		int getOxygen();								//Return Oxygen levels
		bool getGameWon();								//Return gameWon bool
		int getInventorySize();							//Return number of items in inventory
		void printIntro();								//Print game intro for new game
		void setPosition(Room * newRoom);				//Set position to new room
		void setOxygen(int oxygenLevel);				//Set oxygen level
		void decOxygen();								//Decrement oxygen. Call only after room change. 
		void setInventorySize(int numItems);			//Set inventory size to specific value.
		void incInventorySize();						//Increase inventory size by one.
		void decInventorySize();						//Decrease inventory size by one.

		void enactVerb(string verb, string noun);		//Main switch function for receiving input from parser
		
		//Helper functions used inside enactVerb	
		Item * _checkForFeature(string noun);				//Check if noun is a feature in the current room. Return a pointer to feature if found, else returns null
		Item * _checkForItem(string noun);					//Check if noun is an item in the current room. Return a pointer to the item if present, else returns null. 
		Item * _checkInventory(string noun);				//Check if noun matches name of an item in player inventory. Return a pointer to the item if present, else returns null. 
		Bool _checkCurrentRoom(string noun);				//Check if noun is name of the current room.
		
		Item * _findFeature(string noun);
		Item * _findItem(string noun);


		void _look(string verb, string noun);			//Prints long room description
		void _lookAt(string verb, string noun);			//Prints description of item / feature
		void _moveRooms(Room * newRoom);				//Update position pointer call decOxygen()
		void _takeItem(string noun);					//Add item to inventory
		void _dropItem(string noun);					//Drop item from inventory into room. 
		void _help();									//Prints contents of verb list
		void _printInventory();							//Prints names of items in inventory
		void _saveGame();
		void _quitGame();
		void _uniqueFunction(string verb, string noun, gameState game);	//Calls unique function of item / feature
}		