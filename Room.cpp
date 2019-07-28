/**********************************************************************************
Class Implementation - Rooms Base Class 
This is the implementation of the base class for the Rooms Class that will be linked 
together by the Gamestate function.
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include "Room.hpp"
#include "Item.hpp"
using namespace std;

//Room constructor
Room::Room(string nameInput, string shortInput, string longInput, bool visitInput, int itemCount, Item *itemInput[], Item *featInput[], Room *nInput, Room *eInput, Room *wInput, Room *sInput){
  name = nameInput;
  shortDesc = shortInput;
  longDesc = longInput;
  visited = visitInput;
  this->itemCount = itemCount;
  for(int i = 0; i < itemCount; i++)
  {
    itemInventory[i] = itemInput[i];
  }
  features[0] = featInput[0];
  features[1] = featInput[1];
  north = nInput;
  east = eInput;
  west = wInput;
  south = sInput;

}

string Room::getName(){
  return name;
}

string Room::getLongDesc(){
  return longDesc;
}

string Room::getShortDesc(){
  return shortDesc;
}

bool Room::getVisited(){
  return visited;
}

/*
//Unsure if this is supposed to be a string or set of objects? check with Justin on what he needs
string Room::getExits(){
  string exits = north->name + "\n" + east->name + "\n" + south->name + "\n" + west->name +"\n";
  return name;
}
*/

Room * Room::getNorth(){
  return north;
}
Room * Room::getSouth(){
  return south;
}
Room * Room::getEast(){
  return east;
}
Room * Room::getWest(){
  return west;
}

string Room::getNorthName(){
  return north->getName();
}
string Room::getSouthName(){
  return south->getName();
}
string Room::getEastName(){
  return east->getName();
}
string Room::getWestName(){
  return west->getName();
}

Item * Room::getFeature(string featureName){
//check if features are in Room
  for(int i = 0; i < 2; i++){
    if(featureName == features[i]->getName()){
      return features[i];
    }
  }
  return NULL;
}

Item * Room::getItem(string itemName){
//check inventory for the item
  for(int i = 0; i < 8; i++){
    if(itemName == itemInventory[i]->getName()){
      return itemInventory[i];
    }
  }
  return NULL;
}

int Room::getItemCount(){
  return itemCount;
}


void Room::setItemCount(int count){
  itemCount = count;
  return;
}


//Find item in itemInventory that matches the takeName. When found
//set that slot to null and decrement itemCount for room. Used
//when player picks up an item. 
void Room::setItemToNull(string takeName){
  for(int i = 0 ; i < 8 ; i++){
    
    if(takeName == itemInventory[i]->getName()){
      itemInventory[i] = NULL;
      itemCount--;
      break;
    }
  
  }
  return;
}

//Find an empty slot in the room itemInventory. When found set that slot to
//point to the dropped item. Increment itemCount for room. Used when player
//drops and item. 
void Room::setItemToPointer(Item * dropItem){
  for(int i = 0; i < 8 ; i++){
    if(itemInventory[i] == NULL){
      itemInventory[i] = dropItem;
      itemCount++;
      break;
    }
  }
  return;
}

void Room::setVisited(bool value){
  visited = value;
}
