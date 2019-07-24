/**********************************************************************************
Class Definition - Rooms Base Class Definition
This is the definition of thebase class for the rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <stdio.h>
#include "gameState.hpp"
using namespace std;
class Room
{
  private:
    string name;
    string shortDesc;
    string longDesc;
    bool visited
    int itemCount;
    Item * inventory[8];
    Item *features[2];
    Room * north;
    Room * east;
    Room * south;
    Room * west;
   
   public:
    //functions
    Room room(string nameInput, string shortInput, string longInput, bool visitInput, Item *inventInput[], Item *featInput[], Room *nInput, Room *eInput, Room *wInput, Room *sInput);
    string getName();
    string getLongDesc();
    string getshortDesc();
    bool getVisited();
    string getExits();
    Item getFeature(string featureName);
    Item getItem(string itemName);
    void setVisited();
    bool metRequ(Gamestate *G);
    
};
#endif
