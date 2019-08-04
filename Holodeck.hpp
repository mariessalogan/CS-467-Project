/**********************************************************************************
Name: Mariessa Logan
Class Definition - Holodeck Class Definition
This is the definition of the holodeck class which is a child of  the rooms Class 
that will be linked together by the Gamestate function.
**********************************************************************************/
#ifndef HOLODECK_H
#define HOLODECK_H
#include <string>
#include <stdio.h>
#include "gameState.hpp"
#include "Room.hpp"
using namespace std;
class Holodeck
{
  private:
    bool pushed;
   
   public:
    //functions
    void actionFunction(Gamestate *G);
    
    
};
#endif
