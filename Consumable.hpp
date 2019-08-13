/**********************************************************************************
Class Definition - Consumable Class Definition
This is the definition of the base class for the Consumable
**********************************************************************************/
#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include <string>
#include <stdio.h>
#include <cstring>
#include "GameState.hpp"
#include "Item.hpp"

using namespace std;

class Consumable : public Item
{
  private:
   
   public:
   
    //virtual function for actions on unique items
    void actionFunction(GameState* G, string verb);
};
#endif
