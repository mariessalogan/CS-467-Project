/**********************************************************************************
Name: Mariessa Logan
Class Implementation - Items "Phaser" Class 
This is the implementation of the phaser object class
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Phaser.hpp"
using namespace std;


void Phaser::actionFunction(string verb)
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
