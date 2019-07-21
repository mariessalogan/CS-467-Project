/**********************************************************************************
Class Implementation - Rooms Base Class 
This is the implementation of the base class for the rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include "Room.hpp"
using namespace std;

//Room constructor
Room::room(File * roomFile){
  
}

string Room::getName(){
  return name;
}

string Room::longDesc(){
  return longDesc;
}

string Room::shortDesc(){
  return shortDesc;
}

bool Room::getVisited(){
  return visited;
}

//Unsure if this is supposed to be a string or set of objects? check with Justin on what he needs
string Room::getexits(){
  string exits = north->name + "\n" + east->name + "\n" + south->name + "\n" + west->name +"\n";
  return name;
}

string Room::getFeature(string featureName){
//check if features are in room
  for(int i = 0; i < 4; i++){
    if(strcmp(featureName, features[i]->name)){
      return features[i];
    }
  return NULL;
}

string Room::getItem(string itemName){
//check inventory for the item
  for(int i = 0; i < 4; i++){
    if(strcmp(itemName, inventory[i]->name)){
      return inventory[i];
    }
  return NULL;
}

void Room::setVisited(){
  visited = true;
}
