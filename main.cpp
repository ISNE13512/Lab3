#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class WordEntry {
public:
    string word;
    vector<int> lines;

    WordEntry() {}

    WordEntry(string w, int lineNumber) {
        word = w;
        lines.push_back(lineNumber);
    }

    bool operator<(const WordEntry &other) const {
        return word < other.word;
    }

    bool operator==(const WordEntry &other) const {
        return word == other.word;
    }

    void merge(const WordEntry &other) {
        for (size_t i = 0; i < other.lines.size(); i++) {
            if (lines.empty() || lines.back() != other.lines[i]) {
                lines.push_back(other.lines[i]);
            }
        }
    }

    void print() const {
        cout << word << ": ";
        for (size_t i = 0; i < lines.size(); i++) {
            cout << lines[i];
            if (i != lines.size() - 1) cout << ", ";
        }
    }
};


string cleanWord(const string &rawToken) {
    string cleaned;
    for (size_t i = 0; i < rawToken.size(); i++) {
        char c = rawToken[i];
        if (isalpha((unsigned char)c)) {
            cleaned += tolower((unsigned char)c);
        }
    }
    return cleaned;
}

int main() {
    string filename = "import.txt";
    ifstream inFile(filename);

    if (!inFile) {
        cout << "Could not open \"" << filename << "\". "
             << "Make sure it's in the same folder as the program." << endl;
        return 1;
    }

    Tree<WordEntry> crossRef;

    string line;
    int lineNumber = 0;

    while (getline(inFile, line)) {
        lineNumber++;
        istringstream lineStream(line);
        string rawToken;
        while (lineStream >> rawToken) {
            string word = cleanWord(rawToken);
            if (!word.empty()) {
                crossRef.insert(WordEntry(word, lineNumber));
            }
        }
    }

    inFile.close();

    cout << "=== Cross-Reference ===" << endl;
    crossRef.inorder();

    return 0;
}