/**********************************************************************************
Class Definition - Rooms Base Class Definition
This is the definition of thebase class for the rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <stdio.h>
using namespace std;
class Room
{
  private:
    string name;
    string shortDesc;
    string longDesc;
    bool visited
    Item * inventory[8];
    Item * features[8];
    Room * north;
    Room * east;
    Room * south;
    Room * west;
   
   public:
    //functions
    Room room(File *roomFile);
    string getName();
    string getLongDesc();
    string getshortDesc();
    bool getVisited();
    string getExits();
    Item getFeature(string featureName);
    Item getItem(string itemName);
    void setVisited();
    
};
#endif
