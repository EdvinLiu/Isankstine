#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>
#include <regex>

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

vector<string> findURLs(const string& line) {
    vector<string> urls;
    regex urlRegex(R"((http|https):\/\/\S+|www\.\S+|\b\w+\.\w{2,}\b)");
    auto wordsBegin = sregex_iterator(line.begin(), line.end(), urlRegex);
    auto wordsEnd = sregex_iterator();

    for (auto it = wordsBegin; it != wordsEnd; ++it) {
        urls.push_back(it->str());
    }

    return urls;
}

int main() {
    char pasirinkite;
    cout << "Pasirinkite ar skaiciuoti zodzius (z) ar ieskoti URL (u): ";
    cin >> pasirinkite;

    ifstream inputFile("tekstas_url.txt");
    if (!inputFile.is_open()) {
        cerr << "Klaida: Nepavyko atidaryti failo tekstas.txt" << endl;
        return 1;
    }

    if (pasirinkite == 'z') {
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
    }
    else if (pasirinkite == 'u') {
        ofstream outputFile("rezultatai.txt");
        if (!outputFile.is_open()) {
            cerr << "Klaida: Nepavyko atidaryti failo rezultatai.txt" << endl;
            return 1;
        }

        string line;
        int lineNumber = 0;
        while (getline(inputFile, line)) {
            lineNumber++;
            vector<string> urls = findURLs(line);
            for (const string& url : urls) {
                outputFile << "Eilute " << lineNumber << ": " << url << endl;
            }
        }

        inputFile.close();
        outputFile.close();
        cout << "Programa baigta. URL adresai issaugoti faile rezultatai.txt." << endl;

    }
    else cout << "Blogai ivestas pasirinkimas" << endl;

    return 0;
}
