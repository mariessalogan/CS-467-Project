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
  name = "Employee Manual";
  desc1 = "This is a manual that will list the commands that you can use in the game.\n";
  pickup = NULL;
  desc2 = "second description\n";
  secondVerb = "second verb\n";
}

string Item::getName(){
  return name;
}

string Item::getDesc1(){
  return desc1;
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
