#include <iostream>
#include "Automata.h"

static vector<string> getWordsFromFile(string filename)
{

}

int main()
{
	string entryWord = "bcemp";
	Automata automato = Automata();
	automato.initialize(entryWord);
	automato.start();

	return 0;
}
