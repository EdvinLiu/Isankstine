#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>

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

    // Asociatyvus konteineris skaičiuoti žodžių pasikartojimus
    map<string, int> wordCount;
    string line;

    // Nuskaitome failo eilutes ir skaičiuojame žodžius
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {
            word = removePunctuation(word);
            if (!word.empty()) {
                wordCount[word]++;
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

    for (const auto &entry : wordCount) {
        if (entry.second > 1) {
            outputFile << entry.first << " " << entry.second << endl;
        }
    }

    outputFile.close();

    cout << "Programa baigta. Rezultatai issaugoti faile rezultatai.txt." << endl;
    return 0;
}
