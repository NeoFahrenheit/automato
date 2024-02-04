#include <iostream>
#include <format>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Automata
{
public:
	explicit Automata(vector<map<string, string>> transitionList);
	~Automata() = default;

    void initialize(string entryWord);
    void setupFields(string initialState, vector<string> finalStatesList);
	void start();
	string getLog();

private:
	string currentState{  }; //q0
	
	string word{};
	int index{0};
	string computationLog{};
	bool isFinished{ false };
	bool wasUndefined{ false };
	vector<map<string, string>> transitions{};
    vector<string> finalStates{};

	bool changeState(char letter);
	vector<map<string, string>> getStatesAvaiable();
	bool isAccepted();
};

