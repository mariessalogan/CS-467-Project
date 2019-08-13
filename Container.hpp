/**********************************************************************************
Author: Mariessa Logan
Class Definition - Container Class Definition
This is the definition of the base class for the Container.  This will be used for:
Coffee Maker, safe, kelvin, Captain's bathroom
**********************************************************************************/
#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <stdio.h>
#include <cstring>
#include "GameState.hpp"
#include "Item.hpp"

using namespace std;

class Container : public Item
{
  private:
    Item * storedItem;
    string requirement;
   
   public:

    //setter
    void setItem(Item *stored);
    void setRequirement(string required);
    //getter
    Item * getItem();
    string getRequirement();
    //virtual function for actions on unique items
    void actionFunction(GameState* G, string verb);
};
#endif
