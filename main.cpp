#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

// Funkcija pašalinti skyrybos ženklus iš žodžio
string removePunctuation(const string& word) {
    string cleanedWord;
    for (char ch : word) {
            if((ch >= 65 && ch <=90) || (ch >= 97 && ch <= 122))// Paliekame tik raides, skaičius ir brūkšnelius
            cleanedWord += tolower(ch);
    }
    return cleanedWord;
}

int main() {
    // Įvedamo teksto failas
    ifstream inputFile("tekstas.txt");
    if (!inputFile.is_open()) {
        cerr << "Klaida: Nepavyko atidaryti failo tekstas.txt" << endl;
        return 1;
    }

    // Asociatyvus konteineris skaičiuoti žodžių pasikartojimus ir jų vietas
    map<string, vector<int>> wordOccurrences;
    string line;
    int lineNumber = 0;

    // Nuskaitome failo eilutes ir skaičiuojame žodžius
    while (getline(inputFile, line)) {
        lineNumber++;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            word = removePunctuation(word);
            if (!word.empty()) {
                wordOccurrences[word].push_back(lineNumber);
            }
        }
    }

    inputFile.close();

    // Rezultato išvedimo failas
    ofstream outputFile("rezultatai.txt");
    if (!outputFile.is_open()) {
        cerr << "Klaida: Nepavyko atidaryti failo rezultatai.txt" << endl;
        return 1;
    }

    for (const auto& entry : wordOccurrences) {
        if (entry.second.size() > 1) {
            outputFile << entry.first << " pasikartoja " << entry.second.size() << " kartus, eilutese: ";
            for (size_t i = 0; i < entry.second.size(); i++) {
                outputFile << entry.second[i];
                if (i < entry.second.size() - 1) outputFile << ", ";
            }
            outputFile << endl;
            outputFile << endl;
        }
    }

    outputFile.close();

    cout << "Programa baigta. Rezultatai issaugoti faile rezultatai.txt." << endl;
    return 0;
}

