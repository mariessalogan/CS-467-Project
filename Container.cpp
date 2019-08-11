/**********************************************************************************
Name: Mariessa Logan
Class Implementation - Container Class 
This is the implementation of the Container and holodeck button class 
This will be used for:
Coffee Maker, safe, kelvin, Captain's bathroom
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Container.hpp"
using namespace std;

//setter
void Container::setItem(Item *stored)
{
	storedItem = stored;
}
void Container::setRequirement(string required)
{
	requirement = required;
}
//getter
Item * Container::getItem()
{
	return storedItem;
}
string Container::getRequirement()
{
	return requirement;
}

void Container::actionFunction(GameState * G, string verb)
{
	
	if(this->getLocked() == true)
	{
		if(this->getName() == "Coffeemaker")
		{
			cout << "There is no more coffee.\n";
		}
		else if(G->_checkInventory(requirement) == NULL)
		{
			
			
			cout << "You will need to find a way to unlock this.\n";
			
		}
		else
		{
			G->getPosition()->setItemToPointer(storedItem);
			
			cout << "successfully added item to room container\n";
		}
	
	}
	else
		{
			if(this->getName() == "Coffeemaker")
			{
				G->getPosition()->setItemToPointer(storedItem);
				
				cout << "successfully added item to room container\n";
			}
			else
			{
				cout << "You've already checked here.\n";
			}
		}

	
}