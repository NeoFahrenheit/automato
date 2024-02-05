#include "Automata.h"

Automata::Automata()
{
}



void Automata::getAutomataFromFile(const string& filename)
{
	vector<string> splittedWords;
	string currentWord;

	//vector<string> states;
	ifstream file(filename);

	if (file.is_open()) {
		// Pega o nome do automatico e a definicao.
		getline(file, currentWord);
		splittedWords = split(currentWord, '=');
		automataName = splittedWords[0];

		// Pega a definicao
		string temp = splittedWords[1];
		splittedWords = split(temp, '{'); // Descarta o primeiro {
		splittedWords = split(splittedWords[1], '{'); // Descarta o segundo {
		splittedWords = split(splittedWords[1], '{'); // [1] aqui ja e o inicio dos estados.
		splittedWords = split(splittedWords[1], '}');

		// states = splitGetAll(splittedWords[0], ','); // Estados
		splittedWords = split(splittedWords[1], ',');

		// Pegando o estado inicial e final
		splittedWords = split(splittedWords[1], ',');
		initialState = splittedWords[0];

		splittedWords = split(splittedWords[1], '{');
		splittedWords = split(splittedWords[1], '}');
		splittedWords = split(splittedWords[0], '}');

		finalStates = splitGetAll(splittedWords[0], ',');

		getline(file, currentWord);	// Descarta a linha p:

		while (getline(file, currentWord))
		{
			splittedWords = split(currentWord, '(');
			splittedWords = split(splittedWords[1], ')');

			vector<string> fileStates = splitGetAll(splittedWords[0], ',');
			transitions.push_back({ {"at", fileStates[0]}, {"go", fileStates[2]}, {"by", fileStates[1]} });
		}

	}
	else
	{
		cout << "Erro ao abrir o arquivo " << filename << endl;
	}
}

// Seta a palavra de entrada e prepara o aut�mato para iniciar.
void Automata::initialize(string entryWord)
{
	word = entryWord;
	computationLog.clear();
	currentState = initialState;
	index = 0;
	isFinished = false;
	wasUndefined = false;
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


vector<string> Automata::split(const string& str, char delimiter)
{

	vector<string> parts(2);
	size_t pos = str.find(delimiter);

	if (pos != string::npos) {
		// Extrai o lado esquerdo da string (antes do delimitador)
		parts[0] = str.substr(0, pos);
		// Extrai o lado direito da string (depois do delimitador)
		parts[1] = str.substr(pos + 1);
	}
	else {
		// Se o delimitador não for encontrado, o lado esquerdo é a própria string e o lado direito é uma string vazia.
		parts[0] = str;
		parts[1] = "";
	}

	return parts;

}

vector<string> Automata::splitGetAll(const string& str, char delimiter)
{
	vector<string> tokens; // Vetor para armazenar as palavras entre os delimitadores
	istringstream ss(str);
	string token; // Variável temporária para armazenar cada palavra

	while (std::getline(ss, token, delimiter)) {
		// Verifica se a palavra não está vazia
		if (!token.empty()) {
			// Adiciona a palavra ao vetor de tokens
			tokens.push_back(token);
		}
	}

	return tokens;
}