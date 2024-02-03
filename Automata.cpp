#include "Automata.h"

Automata::Automata()
{
	transitions = {
		/*
		* "at": Estado atual.
		* "go": próximo estado.
		* "by": letra necessária para a transição.
		*/

		// q0
		{{"at", "q0"}, {"go", "q1"}, {"by", "a"}},
		{{"at", "q0"}, {"go", "q2"}, {"by", "b"}},

		// q1
		{{"at", "q1"}, {"go", "q3"}, {"by", "c"}},

		// q2
		{{"at", "q2"}, {"go", "q3"}, {"by", "c"}},

		// q3
		{{"at", "q3"}, {"go", "q4"}, {"by", "e"}},
		{{"at", "q3"}, {"go", "q14"}, {"by", "i"}},
		{{"at", "q3"}, {"go", "q5"}, {"by", "d"}},

		// q4
		{{"at", "q4"}, {"go", "q15"}, {"by", "o"}},
		{{"at", "q4"}, {"go", "q10"}, {"by", "n"}},
		{{"at", "q4"}, {"go", "q11"}, {"by", "k"}},
		{{"at", "q4"}, {"go", "q12"}, {"by", "l"}},
		{{"at", "q4"}, {"go", "q3"}, {"by", "c"}},

		// q5
		{{"at", "q5"}, {"go", "q6"}, {"by", "f"}},
		{{"at", "q5"}, {"go", "q7"}, {"by", "g"}},
		{{"at", "q5"}, {"go", "q8"}, {"by", "h"}},
		{{"at", "q5"}, {"go", "q3"}, {"by", "c"}},

		// q6
		{{"at", "q6"}, {"go", "q16"}, {"by", "p"}},

		// q7
		{{"at", "q7"}, {"go", "q16"}, {"by", "p"}},

		// q8
		{{"at", "q8"}, {"go", "q16"}, {"by", "p"}},

		// q9
		{{"at", "q9"}, {"go", "q16"}, {"by", "p"}},

		// q10
		{{"at", "q10"}, {"go", "q9"}, {"by", "q"}},
		{{"at", "q10"}, {"go", "q16"}, {"by", "p"}},

		// q11
		{{"at", "q11"}, {"go", "q13"}, {"by", "m"}},
		{{"at", "q11"}, {"go", "q16"}, {"by", "p"}},

		// q12
		{{"at", "q12"}, {"go", "q13"}, {"by", "m"}},
		{{"at", "q12"}, {"go", "q16"}, {"by", "p"}},

		// q13
		{{"at", "q13"}, {"go", "q16"}, {"by", "p"}},

		// q14
		{{"at", "q14"}, {"go", "q3"}, {"by", "c"}},

		// q15
		{{"at", "q15"}, {"go", "q9"}, {"by", "q"}},
		{{"at", "q15"}, {"go", "q16"}, {"by", "p"}},

		// q16
		{{"at", "q16"}, {"go", "q14"}, {"by", "i"}},
	};
}

// Seta a palavra de entrada e prepara o autômato para iniciar.
void Automata::initialize(string entryWord)
{
	word = entryWord;
	computationLog.clear();
	index = 0;
	isFinished = false;
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

// Faz um tentativa de transição tendo como base o estado atual e uma letra na entrada.
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

// Retorna todos os maps que contém o estado atual.
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
	for (auto& finalState : finalStates)
	{
		if (currentState == finalState)
			return true;
	}

	return false;
}