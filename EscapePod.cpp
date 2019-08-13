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
	cout << "Safety at last! You stumble into the escape pod, where there is an ergonomic chair that will fold out into a hibernation bed when activated.  Someone has thoughtfully placed a bottle of vodka with a glass next to the chair, likely a soldier was using the pod as a room for some private drinking.  You look to the right and see a porthole that shows the vast expanse of space.  You can see a planet surrounded by four moons far away, otherwise it’s a black blanket dotted with distant stars.  You breathe a sigh of relief, sit in the chair and press the button to activate the escape pod.  You sip at the vodka as you watch the spaceship slowly get smaller out of the porthole. \n";
	cout << "____    ____  ______    __    __     ____    __    ____  __  .__   __.  __   __   __\n\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  | |  | |  | |  | \n \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  | |  | |  | |  | \n  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  | |  | |  | |  | \n    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   | |__| |__| |__| \n    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__| (__) (__) (__)\n";	
}