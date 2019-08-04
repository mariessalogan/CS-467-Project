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
  this->name = name;
  this->desc1 = desc1;
  this->pickup = pickup;
  this->desc2 = desc2;
  this->secondVerb = secondVerb;
}

string Item::getName(){
  return name;
}

string Item::getDesc1(){
  return desc1;
}

string Item::getDesc2(){
  return desc2;
}

string Item::getSecondVerb(){
  return secondVerb;
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

void Item::actionFunction(string verb)
{
  if(verb == "look")
  {
    getDesc(verb);
  }
  else
  {
    cout << "Error, you cannot do that.\n";
  }
}
