#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> parse(const string& input, char delim);
bool validateVerb(vector<string> commands);
vector<string> stripPreps(vector<string> commands);

//splits a user input string by spaces and returns a vector of strings
//ultimately the vector will only contain either 1 or 2 strings
vector<string> parse(const string& inputStr, char delim)
{
	vector<string> commands;
	vector<string> stripped;

	istringstream iss(inputStr);
	string token;
	bool validVerb;

	//split input by delimiter and push to a vector
	while (getline(iss, token, delim)) {
		commands.push_back(token);
	}

	stripped = stripPreps(commands);

	validVerb = validateVerb(stripped);

	if(validVerb){
		return stripped;
	}
	else{
		stripped.clear();
		stripped.push_back("Invalid command...");
	}
	
	return stripped;
}


//checks that the verb is an action recognized by the game
bool validateVerb(vector<string> commands)
{
	bool valid = false;
	vector<string> verbs = 
		{"look", "go", "move", "take", "grab", "help", "inventory",
		 "drop", "leave", "save game", "load game", "open", "close",
		"shut", "push", "turn on", "turn off", "drink", "shake", "read",
		"scan", "shoot", "fire", "listen"};

	for(int i = 0; i < verbs.size(); i++){
		if(commands[0] == verbs[i]){
			valid = true;
		}
	}

	return valid;
}


//removes unnecessary articles and prepositions from the input
vector<string> stripPreps(vector<string> commands)
{	
	vector<string> stripped;
	vector<string> removables =
		{"on", "the", "above", "below", "to", "a"};
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
	
		for (auto token : parsedLine) {
			cout << token << endl;
		}

		userInput.clear();
	}
	
	cout << "Game ended..." << endl;
	return 0;
}

