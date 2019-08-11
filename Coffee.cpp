/**********************************************************************************
Class Implementation - Consumable Class 
This is the implementation of the Consumable and holodeck button class 
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Consumable.hpp"
using namespace std;

void Consumable::actionFunction(GameState * G, string verb)
{
	
	//if locked then Consumable was already drunk
	if(verb == "drink" && this->getLocked() == false)
	{
		int oxygen = 5 + G->getOxygen();
		this->setLocked(true);
		G->setOxygen(oxygen);
		if(G->getPosition()->getName() == "Holodeck")
		{
			cout << "You press the button and it turns the Holodeck off.  You can hear the atmo engine powering up.\n";
		}
		else
		{
			cout << "You feel energized!\n";
		}
	}
	else
	{
		if(G->getPosition()->getName() == "Holodeck")
		{
			cout << "You press the button and it turns the Holodeck off.  You can hear the atmo engine powering up.\n";
		}
		else
		{
			cout << "You have already drank enough Consumable.\n";		
		}
		
	}
	
}