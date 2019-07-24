/**********************************************************************************
Name: Mariessa Logan
Class Implementation - Command Center Class 
This is the implementation of the command center that will have the alien as the
feature
**********************************************************************************/
#include <string>
#include <iostream>
#include <stdio.h>
#include "CommandCenter.hpp"
using namespace std;

//Room constructor
Room::room(string nameInput, string shortInput, string longInput, bool visitInput, int itemCount, Item *inventInput[], Item *featInput[], Room *nInput, Room *eInput, Room *wInput, Room *sInput){
  name = nameInput;
  shortDesc = shortInput;
  longDesc = longInput;
  visited = visitInput;
  for(int i = 0; i < itemCount; i++)
  {
    inventory[i] = inventInput[i];
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

  //check player inventory for the requirements
  bool CommandCenter::metRequ(Gamestate *G)
  {
    int reqs = 0;
    for(int i = 0;i < 8; i++)
    {
      //if item is armor, phaser gun, or goggles then increment
      if(strcmp(G->inventory, "armor"))
      {
          reqs++;
      }
      else if(strcmp(G->inventory, "phaser gun"))
      {
          reqs++;
      }
      else if(strcmp(G->inventory, "goggles"))
      {
        reqs++;
      }
      else
        continue;
    }
    if(reqs == 3)
    {
      return true;
    }
    else
    {
      return false;
    }
    
    void CommandCenter::actionFunction(gameState *G)
    {
      if(metRequ(G) == false
      {
        cout << deathDescription;
      }
      else
      {
        printFunction();
      }
    }
  }
