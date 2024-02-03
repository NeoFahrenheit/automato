#pragma once

#include <iostream>
#include <format>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Automata
{
public:
	Automata();
	~Automata() {};

	void initialize(string entry);
	void start();
	string getLog();

private:
	string currentState{ "q0" };
	vector<string> finalStates{ "q14", "q16" };
	
	string word;
	int index{0};
	string computationLog;
	bool isFinished{ false };
	vector<map<string, string>> transitions;

	bool changeState(char letter);
	vector<map<string, string>> getStatesAvaiable();
	bool isAccepted();
};

