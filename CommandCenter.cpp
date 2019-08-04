/**********************************************************************************
Name: Mariessa Logan
Class Implementation - Command Center Class 
This is the implementation of the command center that will have the alien as the
feature
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include "CommandCenter.hpp"
using namespace std;

  void CommandCenter::actionFunction(Gamestate *G)
  {
    
      if(metRequ(G) == true)
      {
        //check if the alien is dead, if not print description for fighting the alien
        if(dead == false)
        {
          cout << "You see movement on the left side of the room thanks to your thermal goggles.  As soon as you notice the heat signature of the alien, it lands a blow across your chest.  Luckily you are wearing the armor that you found earlier.  His claw bounces off the armor, and you swing your phaser up in response.  You squeeze the trigger twice, just as you were trained and they both land squarely between the alien’s eyes.  the alien falls over dead.\n";      
          dead = true;
        }
        else
        {
          cout << "You sigh with relief, the alien is still dead.\n";
        }
      }
      //
      else
      {
        //Ask justin about a set function??
        G.setGameLost(true);
      }
    
  }

//check player inventory for the requirements
bool CommandCenter::metRequ(GameState *G)
{
    int reqs = 0;
    for(int i = 0;i < 8; i++)
    {
      //if item is armor, phaser gun, or goggles then increment
      if(strcmp(G->inventory, "armor"))
      {
          reqs++;
      }
      else if(strcmp(G->inventory, "phaser gun"))
      {
          reqs++;
      }
      else if(strcmp(G->inventory, "goggles"))
      {
        reqs++;
      }
      else
        continue;
    }
    if(reqs == 3)
    {
      return true;
    }
    else
    {
      return false;
    }
 }
