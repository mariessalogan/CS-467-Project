/**********************************************************************************
Class Definition - Item Base Class Definition
This is the definition of the base class for the Items Class that will be the parent
of the features and different types of Items.
**********************************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;
class GameState;

class Item
{
  private:
    string name;
    string desc1;
    string desc2;
    bool pickup;
    string secondVerb;
    bool conditionMet;//for phaser to check if charged as well
    string locationName;//for location of item
   
   public:
    //functions
    Item();
    
    //setters
    void setName(string nameInput);
    void setDesc1(string desc1Input);
    void setDesc2(string desc2Input);
    void setPickup(bool value);
    void setSecondVerb(string secVerb);
    void setConditionMet(bool value);
    void setLocationName(string name);

    //getters
    string getName();
    string getDesc1();
    string getDesc2();
    void getDesc(string verb);
    bool getPickup();
    string getSecondVerb();
    bool getConditionMet();
    string getLocationName();

    //virtual function for actions on unique items
    virtual void actionFunction(GameState * G, string verb);
};
#endif
