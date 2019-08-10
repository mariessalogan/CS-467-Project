/**********************************************************************************
Class Implementation - Items Base Class 
This is the implementation of the base class for the Items Class 
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Coffee.hpp"
using namespace std;

void Coffee::actionFunction(GameState * G, string verb)
{
	
	//if locked then coffee was already drunk
	if(verb == "drink" && this->getLocked() == false)
	{
		int oxygen = 5 + G->getOxygen();
		this->setLocked(true);
		G->setOxygen(oxygen);
		cout << "You feel energized!\n";
	}
	else
	{
		cout << "You have already drank enough coffee.\n";
	}
	
}