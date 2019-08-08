/**********************************************************************************
Class Definition - Phaser Class Definition
This is the definition of the phaser class
**********************************************************************************/
#ifndef PHASER_H
#define PHASER_H
#include <string>
#include <stdio.h>
#include <cstring>
#include "Item.hpp"
#include "GameState.hpp"

using namespace std;
class Item
{
   private:

   
   public:
    

    //virtual function for actions on unique items
    void actionFunction(GameState *G, string verb){};
};
#endif
