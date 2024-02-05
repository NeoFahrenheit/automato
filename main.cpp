#include <iostream>
#include <fstream>
#include <sstream>
#include "Automata.h"

static vector<string> getWordsFromFile(string filename)
{
	vector<string> words;
	string readFromFile;

	ifstream file(filename);

	if (file.is_open()) 
	{
		while (getline(file, readFromFile));

		// Remove os espacos em branco da string
		while (!readFromFile.empty() && isspace(readFromFile.front()))
		{
			readFromFile.erase(readFromFile.begin());
		}

		// Remove os espacos em branco da string
		while (!readFromFile.empty() && isspace(readFromFile.back()))
		{
			readFromFile.pop_back();
		}

		stringstream ss{ readFromFile };
		while (std::getline(ss, readFromFile, ',')) {
			words.push_back(readFromFile);
		}

		file.close();
	}
	else
	{
		cout << "Erro ao abrir o arquivo " << filename << endl;
	}

	return words;
}

void processWords(Automata& automato, vector<string>& words)
{
	cout << "\n";
	for (auto& word : words)
	{
		automato.initialize(word);
		cout << word << endl;
		automato.start();
		cout << "\n\n";
	}
}

int main()
{
	string entryWord = "bcemp";
	Automata automato = Automata();
	string word;
	string filename;
	vector<string> fileWords;
	int option = 1;

	cout << "Trabalho de Linguagens Formais e Automatos, Parte 2\n";
	cout << "Leandro Arruda Monteiro\n";
	cout << "Gabriela Copetti Maccagnan\n";
	cout << "Gabriel Vieclli Pillonetto";

	while (option > 0)
	{

		cout << "\n\nSelecione uma opcao:\n";
		cout << "1: Carregar um automato\n";
		cout << "2: Digitar uma palavra\n";
		cout << "3: Carregar palavras de um arquivo\n";
		cout << "0: Sair\n";

		cin >> option;
		cin.ignore();

		switch (option)
		{
		case 1:
			cout << "Digite o nome do arquivo:\n";
			getline(std::cin, filename);
			automato.getAutomataFromFile(filename);
			break;

		case 2:
			getline(std::cin, word);
			automato.initialize(word);
			automato.start();
			break;

		case 3:
			cout << "Digite o nome do arquivo:\n";
			getline(std::cin, filename);
			fileWords = getWordsFromFile(filename);
			processWords(automato, fileWords);
			break;

		default:
			break;
		}
	}

	return 0;
}