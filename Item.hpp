/**********************************************************************************
Class Definition - Item Base Class Definition
This is the definition of the base class for the items Class that will be the parent
of the features and different types of items.
**********************************************************************************/
#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <stdio.h>
using namespace std;
class Item
{
  private:
    string name;
    string desc1;
    string desc2;
    bool pickup;
    string secondVerb;
   
   public:
    //functions
    Item item(string nameInput, string desc1Input, bool pickupInput, string desc2Input, string secondVerbInput){};
    string getDesc(string verb){};
    bool getPickup();
    
};
#endif
