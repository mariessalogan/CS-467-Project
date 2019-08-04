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
Room::Room(){
  name =  "Bunk";
  shortDesc = "There is a dresser across the door, a picture frame on the floor, and an employee manual on the floor.";
  longDesc = "WARNING! WARNING! OXYGEN LEVELS DROPPING TO CRITICAL LEVEL! PLEASE EVACUATE TO THE NEAREST ESCAPE POD\" You groggily awaken to the sound of a robotic voice booming over the PA system.  You look around and see that the bunk room is in disarray. Other bunks are tipped over, dressers have come apart, and Lopez’ angel figurines are shattered on the ground. You are wedged between your bunk and the wall, a lamp with blood lies directly next to your head.  You touch your forehead and wince, the lamp must have hit you while you slept, possibly causing a minor concussion.  There is blood on your face, but it seems the wound has clotted and is no longer bleeding.  There is a dresser laying across the door to the break room. You will have to push it out of the way to get through the door.  You see a cracked frame on the floor.  Your employee manual is sticking out from a pile of rubble.\n";
  visited = 0;
  itemCount = 0;
  //for(int i = 0; i < itemCount; i++)
  //{
    //itemInventory[i] = itemInput[i];
  //}
  itemInventory[0] = NULL;
  features[0] = NULL;
  features[1] = NULL;
  north = NULL;
  east = NULL;
  west = NULL;
  south = NULL;

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
    if(features[i] != NULL){
      if(featureName == features[i]->getName()){
        return features[i];
      }
    }
  }
  return NULL;
}

Item * Room::getItem(string itemName){
//check inventory for the item
  for(int i = 0; i < 8; i++){
    if(itemInventory[i] != NULL){
        if(itemName == itemInventory[i]->getName()){
          return itemInventory[i];
      }
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

//This may need to be reworked 
void Room::printItemNames(){
  
  if(itemCount != 0){
    for(int i = 0 ; i < 8 ; i++){
      if(itemInventory[i] != NULL){
        cout << "You see a " << itemInventory[i]->getName() << ". " ;
      }
    }
    cout << endl;
  }

 
}

//This may need to be reworked 
void Room::printFeatureNames(){

  for(int i = 0 ; i < 2 ; i++){
    if(itemInventory[i] != NULL){      
      cout << "You see a " << features[i]->getName() << ". ";
    }
  }
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


void Room::setVisited(bool state){
  visited = state;
}

void Room::setName(string input){
  name = input;
}

void Room::setShortDesc(string input){
  shortDesc = input;
}

void Room::setLongDesc(string input){
  longDesc = input;
}

void Room::setNorth(Room * room){
  north = room;
}

void Room::setEast(Room * room){
  east = room;
}

void Room::setSouth(Room * room){
  south = room;
}

void Room::setWest(Room * room){
  west = room;
}