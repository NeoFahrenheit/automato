#pragma once

#include <iostream>
#include <format>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Automata
{
public:
	Automata();
	~Automata() {};

	void getAutomataFromFile(const string& filename);
	void initialize(string entry);
	void start();
	string getLog();

private:
	string initialState;
	string currentState;
	vector<string> finalStates;

	string automataName;
	string word;
	int index{ 0 };
	string computationLog;
	bool isFinished{ false };
	bool wasUndefined{ false };
	vector<map<string, string>> transitions;

	bool changeState(char letter);
	vector<map<string, string>> getStatesAvaiable();
	bool isAccepted();

	vector<string> split(const string& str, char delimiter);
	vector<string> splitGetAll(const string& str, char delimiter);
};
