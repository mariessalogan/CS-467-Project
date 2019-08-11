/**********************************************************************************
Name: Mariessa Logan
Class Implementation - EscapePod Class 
This is the implementation of the EscapePod 
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "EscapePod.hpp"
using namespace std;


void EscapePod::actionFunction(GameState * G, string verb)
{
	G->setGameWon(true);	
}