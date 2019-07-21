/**********************************************************************************
Class Implementation - Items Base Class 
This is the implementation of the base class for the items Class 
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include "Item.hpp"
using namespace std;

//Room constructor
Item::item(string nameInput, string desc1Input, bool pickupInput, string desc2Input, string secondVerbInput){
  name = nameInput;
  desc1 = desc1Input;
  pickup = pickupInput;
  desc2 = desc2Input;
  secondVerb = secondVerbInput;
}

string Item::getName(){
  return name;
}

//This function determines whether or not to get Desc 1 or Desc2
string Item::getDesc(string verb)
{
  if(strcmp(verb, secondVerb)
    return desc1;
  else
    return desc2;
}

bool Item::getPickup(){
  return pickup;
}
