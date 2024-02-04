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
	const vector<string> finalStates{ "q14" };
	
	string word;
	int index{0};
	string computationLog;
	bool isFinished{ false };
	bool wasUndefined{ false };
	vector<map<string, string>> transitions;

	bool changeState(char letter);
	vector<map<string, string>> getStatesAvaiable();
	bool isAccepted();
};

