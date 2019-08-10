/**********************************************************************************
Author: Mariessa Logan
Class Definition - Command Center Class Definition
This is the definition of thebase class for the rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <string>
#include <stdio.h>
#include "Room.hpp"
#include "GameState.hpp"

using namespace std;

class CommandCenter
{
  private:
    bool dead;
   
   public:
    //setter
    void setDead(bool value);
    //getter
    bool getDead();
    //functions
    void actionFunction(GameState *G);
    bool metRequ(GameState *G);
    
};
#endif
