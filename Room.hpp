/**********************************************************************************
Class Definition - Rooms Base Class Definition
This is the definition of thebase class for the Rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <stdio.h>
#include "Item.hpp"
using namespace std;
class Room
{
  private:
    string name;
    string shortDesc;
    string longDesc;
    bool visited;
    int itemCount;
    Item * itemInventory[8];
    Item * features[2];
    Room * north;
    Room * east;
    Room * south;
    Room * west;
   
   public:
    //functions
    Room();
    string getName();
    string getLongDesc();
    string getShortDesc();
    bool getVisited();
    Room * getNorth();
    Room * getSouth();
    Room * getEast();
    Room * getWest();
    string getNorthName();
    string getSouthName();
    string getEastName();
    string getWestName();
    Item * getFeature(string featureName);
    Item * getItem(string itemName);
    int getItemCount();
    void printItemNames();
    void printFeatureNames();
    void setItemCount(int count);
    void setItemToNull(string takeName); 
    void setItemToPointer(Item * dropItem);    
    void setVisited(bool state);
    void setName(string input);
    void setShortDesc(string input);
    void setLongDesc(string input);

    void setNorth(Room * room);
    void setEast(Room * room);
    void setSouth(Room * room);
    void setWest(Room * room);
    //virtual void actionFunction();
};
#endif
