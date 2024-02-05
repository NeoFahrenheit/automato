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

void Automata::setupFields(string initial, vector<string> finalStatesList) {
    finalStates = finalStatesList;
    currentState = initial;
    initialState = initial;
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
	vector<map<string, string>> states = getStatesAvaiable(currentState);
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
vector<map<string, string>> Automata::getStatesAvaiable(string current)
{
	vector<map<string, string>> found;
	for (auto state : transitions)
	{
		if (current == state["at"])
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

void Automata::removeUselessStates() {
    vector<map<string, string>> newTransitions = {};
    vector<map<string, string>> alreadyVisited = {};
    for(auto state : transitions) {
        bool skip = false;

        for(auto added : newTransitions) {
            if(added["at"] == state["at"]) {
                skip = true;
            }
        }

        if (skip) continue;

        auto reachable =canReachFinal(state["at"], alreadyVisited);
        auto reachableStates = getStatesAvaiable(state["at"]);
        for(auto currStateTransition : reachableStates) {
            if(reachable) {
                newTransitions.push_back(currStateTransition);
            } else {
                alreadyVisited.push_back(currStateTransition);
            }
        }
    }
    transitions = newTransitions;
    printStatesToFile();
}

bool Automata::canReachFinal(string state, vector<map<string, string>> &alreadyVisited) {
    auto available = getStatesAvaiable(state);
    bool output = false;
    bool skipState = false;
    bool nonReachable = true;
    for (auto trans: transitions) {
        nonReachable = true && trans["go"] != state && state != initialState && nonReachable;
    }
    if (nonReachable) return false;

    //Para todas as transicoes do estado atual
    for(auto reachableState : available) {
        skipState = false;
        //Caso a transicao atual ja tenha sido avaliada
        for (auto& visited : alreadyVisited)
        {
            if (reachableState["at"] == visited["at"] && reachableState["go"] == visited["go"])
                skipState = true;
        }
        //Passa pra prox transicao
        if(skipState){
            continue;
        }
        //Verificar se a transicao atual leva a um dos estados finais
        for (auto& finalState : finalStates)
        {
            auto a = reachableState["go"];
            if (reachableState["go"] == finalState)
                return true;
        }

        output = output || canReachFinal(reachableState["go"], alreadyVisited);
    }
    return output;
}

bool Automata::isEmptyLanguage() {
    return transitions.size() == 0;
}

void Automata::printStatesToFile() {
    ofstream outputFile("transitions.txt");
    if(outputFile.is_open()) {
        for (auto trans : transitions) {
            outputFile << "(" + trans["at"] +"," + trans["by"] + "," + trans["go"] + ")" << endl;
        }
    } else {
        cerr << "Erro ao abrir o arquivo " << "transitions.txt" << endl;
    }
    outputFile.close();
};