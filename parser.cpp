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
#include <parser.hpp>
using namespace std;

//splits a user input string by spaces and returns a vector of strings
//ultimately the vector will only contain either 1 or 2 strings
vector<string> parse(const string& inputStr, char delim)
{
	string lowerCaseStr;
	vector<string> commands;

	//convert input to lower case
	for (int i = 0; i < inputStr.length(); i++) {
		lowerCaseStr.push_back(tolower(inputStr[i]));
	}

	istringstream iss(lowerCaseStr);
	string token;

	//split input by delimiter and push to a vector
	while (getline(iss, token, delim)) {
		commands.push_back(token);
	}

	//check for double verbs up front
	if (commands.size() == 2) {
		commands = concatDoubleVerbs(commands);
	}

	if (commands.size() == 1) {
		commands = validateSingleEntry(commands);
		return commands;
	}

	if (commands.size() == 2) {
		commands = validateDoubleEntry(commands);
		//commands = validateCombo(commands);
		return commands;
	}

	if (commands.size() == 3) {
		commands = validateTripleEntry(commands);
		return commands;
	}

	if (commands.size() >= 4) {
		commands = validateManyEntry(commands);
		return commands;
	}
}


/**************************************************************************
*These 3 functions test that the input is recognized in the game's lexicon
***************************************************************************/
bool validateVerb(vector<string> commands)
{
	bool valid = false;

	for(int i = 0; i < verbs.size(); i++){
		if(commands[0] == verbs[i]){
			valid = true;
		}
	}

	return valid;
}


bool validateMovement(vector<string> commands, int indexToCheck) {
	int index = indexToCheck;
	bool valid = false;

	for (int i = 0; i < exits.size(); i++) {
		if (commands[indexToCheck] == exits[i]) {
			valid = true;
		}
	}

	return valid;
}


bool validateNoun(vector<string> commands)
{
	bool found = false;

	for (int i = 1; i < commands.size(); i++) {
		for (int j = 0; j < nouns.size(); j++) {
			if (commands[i] == nouns[j]) {
				found = true;
			}
		}
	}

	return found;
}


vector<string> validateSingleEntry(vector<string> &commands) {
	bool isValid = false;
	bool validVerb = false;
	bool validMovement = false;
	vector<string> movementVerbs = { "go", "move" };

	validVerb = validateVerb(commands);
	
	//if single entry is a valid verb
	if (validVerb) {
		//check that it is not a movement verb without a destination
		for (int i = 0; i < movementVerbs.size(); i++) {
			if (commands[0] == movementVerbs[i]) {
				commands.push_back("Please enter an exit or direction...");
			}
		}
		return commands;
	}

	//if single entry and not a verb, then check for an exit
	if (!validVerb) {
		validMovement = validateMovement(commands, 0);
	}

	//if verb is invalid and movement valid - return as valid input
	if (!validVerb && validMovement) {
		return commands;
	}

	commands.clear();
	commands.push_back("Invalid entry...");
	return commands;
}


vector<string> validateDoubleEntry(vector<string> &commands) {
	bool validVerb = false;
	bool validMovement = false;
	bool validNoun = false;

	validVerb = validateVerb(commands);
	//cout << "**check for double entry verb: " << validVerb << endl;

	validMovement = validateMovement(commands, 1);
	//cout << "**check for double entry exit: " << validMovement << endl;

	validNoun = validateNoun(commands);
	//cout << "**check for doulbe entry noun: " << validNoun << endl;

	if (validVerb && validMovement) {
		if (commands[0] == "go" || commands[0] == "move") {
			//cout << "return valid verb/exit" << endl;
			return commands;
		}
	}

	if (validVerb && validNoun) {
		//cout << "return valid verb/noun" << endl;
		return commands;
	}

	commands.clear();
	commands.push_back("Invalid entry...");
	return commands;
}


vector<string> validateTripleEntry(vector<string> &commands) {
	//check for double verbs
	commands = concatDoubleVerbs(commands);
	
	//check for double nouns
	commands = concatDoubleNouns(commands);

	if (commands.size() == 2) {
		commands = validateDoubleEntry(commands);
		return commands;
	}

	if (commands.size() == 3) {
		commands = stripTrashWords(commands);
		commands = validateDoubleEntry(commands);
		return commands;
	}

	commands.clear();
	commands.push_back("Invalid entry...");
	return commands;
}


vector<string> validateManyEntry(vector<string> &commands) {
	//check for double verbs
	commands = concatDoubleVerbs(commands);

	//check for double nouns
	commands = concatDoubleNouns(commands);

	if (commands.size() == 2) {
		commands = validateDoubleEntry(commands);
		return commands;
	}

	if (commands.size() >= 3) {
		commands = stripTrashWords(commands);
		commands = validateDoubleEntry(commands);
		return commands;
	}

	commands.clear();
	commands.push_back("Invalid entry...");
	return commands;
}


vector<string> concatDoubleVerbs(vector<string> &commands) {
	if (commands[0] == "look" && commands[1] == "at") {
		commands[0] = "look at";
		commands.erase(commands.begin() + 1);
	}

	if (commands[0] == "turn" && commands[1] == "on") {
		commands[0] = "turn on";
		commands.erase(commands.begin() + 1);
	}

	if (commands[0] == "turn" && commands[1] == "off") {
		commands[0] = "turn off";
		commands.erase(commands.begin() + 1);
	}

	return commands;
}


int getDoubleNounIndex(vector <string> commands) {
	int foundIdx = -1;

	vector<string> doubleNouns = {
		"manual", "badge", "key", "goggles", "maker",
		"meter", "pipe", "supplies", "monitor"
	};

	for(int i = 0; i < commands.size(); i++) {
		for (int j = 0; j < doubleNouns.size(); j++) {
			if (commands[i] == doubleNouns[j]) {
				foundIdx = i;
			}
		}
	}

	return foundIdx;
}


//combines 2 worded nouns seperated by spaces back into a single string
vector<string> concatDoubleNouns(vector<string> &commands){

	int index = getDoubleNounIndex(commands);

	if (index == -1) {
		return commands;
	}

	if(commands[index] == "manual" && commands[index - 1] == "employee"){
		commands[index - 1] = "employee manual";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "badge" && commands[index - 1] == "security") {
		commands[index - 1] = "security badge";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "key" && commands[index - 1] == "desk") {
		commands[index - 1] = "desk key";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "goggles" && commands[index - 1] == "thermal") {
		commands[index - 1] = "thermal goggles";
		commands.erase(commands.begin() + index);
		return commands;
	}
	
	if (commands[index] == "maker" && commands[index - 1] == "coffee") {
		commands[index - 1] = "coffee maker";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "meter" && commands[index - 1] == "oxygen") {
		commands[index - 1] = "oxygen meter";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "pipe" && commands[index - 1] == "steam") {
		commands[index - 1] = "steam pipe";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "supplies" && commands[index - 1] == "surgical") {
		commands[index - 1] = "surgical supplies";
		commands.erase(commands.begin() + index);
		return commands;
	}

	if (commands[index] == "monitor" && commands[index - 1] == "heart") {
		commands[index - 1] = "heart monitor";
		commands.erase(commands.begin() + index);
		return commands;
	}

	return commands;
	
}


//removes unnecessary articles and prepositions from the input
vector<string> stripTrashWords(vector<string> &commands)
{
	bool found = false;

	for (int i = 0; i < commands.size(); i++) {
		for (int j = 0; j < removables.size(); j++) {
			if (commands[i] == removables[j]) {
				commands.erase(commands.begin() + i);
				i--;
			}
		}
	}

	return commands;
}