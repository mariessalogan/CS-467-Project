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
	
	if(this->getConditionMet() == false)
	{
		cout << "You need " << this->getRequirement() << "\n\n";
		if(this->getName() == "coffee maker")
		{
			cout << "There is no more coffee.\n";
		}
		else if(this->getName() == "kelvin")
		{
			cout << "Kelvin died doing what he loved.\n";
		}
		else if(G->_checkInventory(this->getRequirement()) == NULL)
		{
			
			
			cout << "You will need to find a way to unlock this.\n";
			
		}
		else
		{
			this->setConditionMet(true);
			G->getPosition()->setItemToPointer(storedItem);
			if(this->getName() == "bathroom")
			{
				cout << "You open the room and see armor thrown on the ground, right by the door.  It must have been tossed aside by the captain when he was running out of the room.  You look further into the room and see a marble, palatial bathtub with half burned scented candles. You look up and there are mirrors on the ceiling.  No wonder the crew members kept pranking him, this bathroom was obviously built with a purpose.\n";

			}
			if(this->getName() == "safe")
			{
				cout << "You open the safe and find only one phaser charger inside. You should put this in your pack for later. \n";
			}
			if(this->getName() == "desk")
			{
				cout << "You open the drawer and see a pair of thermal goggles sitting on top of a pile of pens.  They help you see things that are invisible to the naked eye, that might come in handy. \n";
			}
		}
	
	}
	else
		{
			if(this->getName() == "coffee maker")
			{
				G->getPosition()->setItemToPointer(storedItem);
				
				cout << "You breathe in the smell of fresh coffee as it brews.\n";
				this->setConditionMet(false);
			}
			else if(this->getName() == "kelvin")
			{
				G->getPosition()->setItemToPointer(storedItem);
				
				cout << "As you shake Kelvin, a small metallic object falls to the ground. Kelvin is dead, but he had a key in his pocket. This may be important later.\n";
				this->setConditionMet(false);
			} 
			else
			{
				cout << "You've already checked here.\n";
			}
		}

	
}
