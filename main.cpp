#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Automata.h"

static vector<string> getWordsFromFile(string filename)
{
	vector<string> words;
	string readFromFile;

	ifstream file(filename);

	if (file.is_open()) {
		while (getline(file, readFromFile));

		// Remove os espa�os em branco da string
		while (!readFromFile.empty() && isspace(readFromFile.front()))
		{
			readFromFile.erase(readFromFile.begin());
		}

		// Remove os espa�os em branco da string
		while (!readFromFile.empty() && isspace(readFromFile.back()))
		{
			readFromFile.pop_back();
		}

		stringstream ss{ readFromFile };
		while (std::getline(ss, readFromFile, ',')) {
			words.push_back(readFromFile);
		}


		file.close();

		for (const auto& w : words) {
			std::cout << w << std::endl;
		}
	}
	else
	{
		cout << "Erro ao abrir o arquivo " << filename << endl;
	}

	return words;
}

void processWords(vector<string> &words) {
    Automata automato = Automata({});

	cout << "\n";
	for (auto& word : words)
	{
		automato.initialize(word);
		cout << word << endl;
		automato.start();
		cout << "\n\n";
	}
}

Automata getAutomataFromFile(const string &filename) {
    vector<string> words;
    string currentWord;
    vector<map<string, string>> transitionList;

    vector<string> finalStates = {};
    string initialState = "";

    ifstream file(filename);

    if (file.is_open()) {
        //Descarta as informacoes que nao utilizamos.
        //Descarta nome do automato
        getline(file, currentWord, '=');

        getline(file, currentWord);
        currentWord.erase(currentWord.begin(), currentWord.begin() + 2);
        currentWord.pop_back();

        //Descarta o alfabeto
        for (int i = 0; i < currentWord.size() && currentWord[0] != '{'; i++) {
            currentWord.erase(currentWord.begin());
        }
        currentWord.erase(currentWord.begin());

        //Descarta os estados
        while (currentWord[0] != '}') {
            currentWord.erase(currentWord.begin());
        }
        //Descarta ultimo }, dos estados
        currentWord.erase(currentWord.begin(), currentWord.begin()+2);

        //Estado inicial
        auto pos = currentWord.find(',');
        if(pos != string::npos) {
            initialState = currentWord.substr(0, pos);
        }

        //Descarta ate o inicio dos finais
        while (currentWord[0] != '{') {
            currentWord.erase(currentWord.begin());
        }
        currentWord.erase(currentWord.begin());

        while (currentWord[0] != '}') {
            pos = currentWord.find(',');
            auto removeTil = currentWord.begin() + int(pos) + 1;
            //Caso esteja no ultimo estado final da lista
            if (pos == string::npos) {
                pos = currentWord.find('}');
                removeTil= currentWord.begin() + int(pos);
            }
            if(pos != string::npos) {
                finalStates.push_back(currentWord.substr(0, pos));
                currentWord.erase(currentWord.begin(), removeTil);
            }
        }

        //Descarta linha `p:\n`
        getline(file, currentWord);

        while (getline(file, currentWord)) {
            currentWord.erase(currentWord.begin());

            pos = currentWord.find(',');
            auto state = currentWord.substr(0, pos);
            currentWord.erase(currentWord.begin(), currentWord.begin() + int(pos) + 1);

            pos = currentWord.find(',');
            auto value = currentWord.substr(0, pos);
            currentWord.erase(currentWord.begin(), currentWord.begin() + int(pos) + 1);

            pos = currentWord.find(')');
            auto nextState = currentWord.substr(0, pos);

            transitionList.push_back({{"at", state},
                                      {"go", nextState},
                                      {"by", value}});
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return Automata({});
    }

    Automata output = Automata(transitionList);
    output.setupFields(initialState, finalStates);
    return output;
}

int main() {
    string entryWord = "bcemp";
    Automata automato = Automata({});
    string word;
    string filename;
    vector<string> fileWords;
    int option = 1;

	cout << "Trabalho de Linguagens Formais e Automatos, Parte 2\n";
	cout << "Leandro Arruda Monteiro\n";
	cout << "Gabriela Copetti Maccagnan\n";
	cout << "Gabriel Vieclli Pillonetto";

    while (option > 0) {
        cout << "\n\nSelecione uma opcao:\n";
        cout << "1: Digitar uma palavra\n";
        cout << "2: Carregar de um arquivo\n";
        cout << "3: Carregar um automato\n";
        cout << "0: Sair\n";

		cin >> option;
		cin.ignore();
		
		switch (option)
		{
		case 1:
			getline(std::cin, word);
			automato.initialize(word);
			automato.start();
			break;

            case 2:
                cout << "Digite o nome do arquivo:\n";
                getline(std::cin, filename);
                fileWords = getWordsFromFile(filename);
                processWords(fileWords);
                break;

            case 3:
                cout << "Digite o nome do arquivo:\n";
                getline(std::cin, filename);
                automato = getAutomataFromFile(filename);
                automato.removeUselessStates();
                break;
            default:
                break;
        }
    }

	return 0;
}
