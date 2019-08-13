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
	
	//if conditionMet then Consumable was already drunk
	if(this->getConditionMet() == false)
	{
		int oxygen = 5 + G->getOxygen();
		this->setConditionMet(true);
		G->setOxygen(oxygen);
		if(G->getPosition()->getName() == "Holodeck")
		{
			cout << "You press the button and it turns the Holodeck off.  You can hear the atmo engine powering up.\n";
			G->getPosition()->setLongDesc("The room is dark and dim without the holodeck projection.  The walls are a simple white color, boring and uninteresting.  The kill switch is still depressed from when you pressed it.\n");
			G->getPosition()->setShortDesc("The room is dim and has white walls and floors.  You've already pressed the button for the kill switch.\n");
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
			cout << "You have already turned the holodeck off.\n";
		}
		else
		{
			cout << "You have already drank enough Coffee.\n";		
		}
		
	}
	
}