/**********************************************************************************
Class Definition - Coffee Class Definition
This is the definition of the base class for the Coffee
**********************************************************************************/
#ifndef COFFEE_H
#define COFFEE_H
#include <string>
#include <stdio.h>
#include <cstring>
#include "GameState.hpp"
#include "Item.hpp"

using namespace std;

class Coffee : public Item
{
  private:
   
   public:
   
    //virtual function for actions on unique items
    void actionFunction(GameState* G, string verb);
};
#endif
