/**********************************************************************************
Author: Mariessa Logan
Class Definition - EscapePod Class Definition
This is the definition of the base class for the EscapePod.  
**********************************************************************************/
#ifndef ESCAPEPOD_H
#define ESCAPEPOD_H
#include <string>
#include <stdio.h>
#include <cstring>
#include "GameState.hpp"
#include "Item.hpp"

using namespace std;

class EscapePod : public Item
{
  private:
    
   
   public:

    //virtual function for actions on unique items
    void actionFunction(GameState* G, string verb);
};
#endif
