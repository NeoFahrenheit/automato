#include "Automata.h"

Automata::Automata(vector<map<string, string>> transitionList)
{
    transitions = transitionList;
}

// Seta a palavra de entrada e prepara o aut�mato para iniciar.
void Automata::initialize(string entryWord)
{
	word = entryWord;
	computationLog.clear();
	index = 0;
	isFinished = false;
	wasUndefined = false;
}

void Automata::setupFields(string initialState, vector<string> finalStatesList) {
    finalStates = finalStatesList;
    currentState = initialState;
}

void Automata::start()
{
	if (isFinished)
	{
		std::cout << "Inicialize o automato novamente para realizar a proxima computacao.\n";
		return;
	}

	computationLog.append(format("{} ", currentState));
	while (index < word.length())
	{	
		const char letter = word[index];
		computationLog.append(format("{} ", letter));

		if (!changeState(letter))
		{
			computationLog.append("X");
			wasUndefined = true;
			break;
		}
		else
		{
			computationLog.append(format("{} ", currentState));
		}
	
	}

	if (isAccepted())
	{
		std::cout << "Palavra aceita!\n";
		cout << getLog();
	}
	else
	{
		std::cout << "Palavra rejeitada!\n";
		cout << getLog();
	}

	isFinished = true;
}

string Automata::getLog()
{
	return computationLog;
}

// Faz um tentativa de transi��o tendo como base o estado atual e uma letra na entrada.
// Retorna true em caso de sucesso.
bool Automata::changeState(char letter)
{
	vector<map<string, string>> states = getStatesAvaiable();
	for (auto state : states)
	{
		if (state["by"].at(0) == word[index])
		{	
			currentState = state["go"];
			index++;
			return true;
		}
	}

	return false;
}

// Retorna todos os maps que cont�m o estado atual.
vector<map<string, string>> Automata::getStatesAvaiable()
{
	vector<map<string, string>> found;
	for (auto state : transitions)
	{
		if (currentState == state["at"])
			found.push_back(state);
	}

	return found;
}

bool Automata::isAccepted()
{
	if (wasUndefined)
	{
		return false;
	}

	for (auto& finalState : finalStates)
	{
		if (currentState == finalState)
			return true;
	}

	computationLog.append("X");
	return false;
}