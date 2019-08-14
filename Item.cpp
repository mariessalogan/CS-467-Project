/**********************************************************************************
Class Implementation - Items Base Class 
This is the implementation of the base class for the Items Class 
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Item.hpp"
using namespace std;

//Room constructor
Item::Item(){


  pickup = NULL;
  conditionMet = NULL;
}

/*************************************************************
*Setter functions
*
**************************************************************/
void Item::setName(string nameInput)
{
  name = nameInput;
}
void Item::setDesc1(string desc1Input)
{
  desc1 = desc1Input;
}
void Item::setDesc2(string desc2Input)
{
  desc2 = desc2Input;
}
void Item::setPickup(bool value)
{
  pickup = value;
}
void Item::setSecondVerb(string secVerb)
{
  secondVerb = secVerb;
}
void Item::setConditionMet(bool value)
{
  conditionMet = value;
}
void Item::setLocationName(string name)
{
  locationName = name;
}
/*************************************************************
*Getter functions
*
**************************************************************/
string Item::getName(){
  return name;
}

string Item::getDesc1(){
  return desc1;
}

string Item::getDesc2(){
  return desc2;
}
//This function determines whether or not to get Desc 1 or Desc2
void Item::getDesc(string verb)
{
  //print the correct description
  if(verb == secondVerb)
    cout << desc2 << "\n";
  else
    cout << desc1 << "\n";
}

bool Item::getPickup(){
  return pickup;
}

string Item::getSecondVerb(){
  return secondVerb;
}

bool Item::getConditionMet()
{
  return conditionMet;
}

string Item::getLocationName(){
  return locationName;
}

void Item::actionFunction(GameState * G, string verb){
  

  if(verb == secondVerb){
    cout << desc2 << endl;
  }
  else
  {
    cout << "Error, you cannot do that.\n";
  }
}