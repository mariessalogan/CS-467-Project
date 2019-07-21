/***********************************************************************
Program: Adventure Time CLI Game
Author: Hamilton Skrabanek
Date: 7/17/19
Description: Parsing engine that validates user input. It will return a 
	vector of strings containing either a single valid verb, or 
	an actionable verb and corresponding noun
***********************************************************************/ 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> parse(const string& input, char delim);
bool validateVerb(vector<string> commands);
vector<string> stripPreps(vector<string> commands);
vector<string> validateNoun(vector<string> commands);
void checkDoubleVerbs(vector<string> &commands);
void checkDoubleNouns(vector<string> &commands);

//splits a user input string by spaces and returns a vector of strings
//ultimately the vector will only contain either 1 or 2 strings
vector<string> parse(const string& inputStr, char delim)
{
	vector<string> commands;
	vector<string> stripped;
	vector<string> fincommand;

	istringstream iss(inputStr);
	string token;
	bool validVerb;

	//split input by delimiter and push to a vector
	while (getline(iss, token, delim)) {
		commands.push_back(token);
	}

	//recombine look at, turn on, and turn off 
	if(commands.size() > 1){
		checkDoubleVerbs(commands);
	}

	//check that the verb exsists as a game command
	validVerb = validateVerb(commands);

	if(validVerb && commands.size() == 1){
		return commands;
	}

	if(!validVerb){
		commands.clear();
		commands.push_back("Unrecognized action...");
		return commands;
	}

	//strip the extras
	stripped = stripPreps(commands);

	//concatenate 2 worded items
	if(stripped.size() > 2){
		checkDoubleNouns(stripped);
	}

	fincommand = validateNoun(stripped);

	return fincommand;
}


//checks that the verb is an action recognized by the game
bool validateVerb(vector<string> commands)
{
	bool valid = false;
	vector<string> verbs = 
		{"look", "look at","go", "move", "take", "grab", "help", "inventory",
		 "drop", "leave", "save", "load", "open", "close",
		"shut", "push", "turn on", "turn off", "drink", "shake", "read",
		"scan", "shoot", "fire", "listen"};

	for(int i = 0; i < verbs.size(); i++){
		if(commands[0] == verbs[i]){
			valid = true;
		}
	}

	return valid;
}

//combines 2 worded verbs seperated by spaces back into a single string
void checkDoubleVerbs(vector<string> &commands){
	if(commands[0] == "look" && commands[1] == "at"){
		commands[0] = "look at";
	}
	
	if(commands[0] == "turn" && commands[1] == "on"){
		commands[0] = "turn on";
	}

	if(commands[0] == "turn" && commands[1] == "off"){
		commands[0] = "turn off";
	}
}


//combines 2 worded nouns seperated by spaces back into a single string
void checkDoubleNouns(vector<string> &commands){
	if(commands[1] == "employee" && commands[2] == "manual"){
		commands[1] = "employee manual";
		commands.pop_back();
	}
	
	if(commands[1] == "security" && commands[2] == "badge"){
		commands[1] = "security badge";
		commands.pop_back();
	}

	if(commands[1] == "desk" && commands[2] == "key"){
		commands[1] = "desk key";
		commands.pop_back();
	}

	if(commands[1] == "thermal" && commands[2] == "goggles"){
		commands[1] = "thermal goggles";
		commands.pop_back();
	}

	if(commands[1] == "coffee" && commands[2] == "maker"){
		commands[1] = "coffee maker";
		commands.pop_back();
	}

	if(commands[1] == "oxygen" && commands[2] == "meter"){
		commands[1] = "oxygen meter";
		commands.pop_back();
	}

	if(commands[1] == "steam" && commands[2] == "pipe"){
		commands[1] = "steam pipe";
		commands.pop_back();
	}

}

//removes unnecessary articles and prepositions from the input
vector<string> stripPreps(vector<string> commands)
{	
	vector<string> stripped;
	vector<string> removables =
		{"under", "on", "off", "all", "the", "above", "below", "to", "a", "at"};
	bool found = false;

	for(int i = 0; i < commands.size(); i++){
		for(int j = 0; j < removables.size(); j++){
			if(commands[i] == removables[j]){
				found = true;
			}
		}
	
		if(!found){
			stripped.push_back(commands[i]);
		}
		found = false;
	}

	return stripped;
}

vector<string> validateNoun(vector<string> commands)
{
	bool found = false;

	vector<string> nouns = 
		{"employee manual", "phaser", "armor", "radio", "security badge", "desk key",
		"thermal goggles", "charger", "dresser", "photo", "Lopez", "television", "bar", "cd",
		"scanner", "dryer", "mirror", "menu", "coffee maker", "coffee", "button",
		"oxygen meter", "chair", "binder", "Starbuck", "Mal", "safe", "mech", "blowtorch",
		"uniform", "beaker", "desk", "steam pipe", "Kirk", "transporter", "alien", 
		"screen", "Melvin", "Kelvin", "surgical supplies", "heart", "port", "alcohol", "chemicals",
		"north", "south", "east", "west"
		};

	for(int i = 1; i < commands.size(); i++){
		for(int j = 0; j < nouns.size(); j++){
			if(commands[i] == nouns[j]){
				found = true;
			}
		}
	}

	if(!found){
		commands.clear();
		commands.push_back("You can't " + commands[0] + " the " + commands[1] );
	}

	return commands;
}
 
int main()
{
	vector<string> parsedLine;
	string userInput;
	bool gameLoop = true;

	while(gameLoop){
		
		cout << "> ";

		getline(cin, userInput);
	
		if(userInput == "endgameloop"){
			break;
		}

		parsedLine = parse(userInput, ' ');
	
		cout << "**printing vector**" << endl;
	
		for (auto token : parsedLine){
			cout << token << endl;
		}

		userInput.clear();
	}
	
	cout << "Game ended..." << endl;
	return 0;
}

