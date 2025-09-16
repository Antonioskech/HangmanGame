#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

const string FILE_NAME = "dictionary.txt";
vector<string> words;
unordered_set<char> letterGuesses;

void printDashes(int wordIndex) {
    string chosenWord = words[wordIndex];
    for (int i = 0; i < chosenWord.size(); i++) {
        cout << "_";
    }
    cout << endl;
}

void addWords() {
    ifstream ifs(FILE_NAME);
    if (!ifs.is_open()) {
        throw std::exception("Could not open file.");
    }
    
    while (!ifs.eof()) {
        string word;
        ifs >> word;
        words.push_back(word);
    }

    ifs.clear();
    ifs.close();
}

bool isLetter(char ch) {
    if (ch < 'a' || ch > 'z') {
        return false;
    }
    
    return true;
}

bool findLetterInWord(const string& word, char ch) {
    for (int i = 0; i < word.size(); i++) {
        if (ch == word[i]) {
            return true;
        }
    }

    return false;
}

void markFoundLetter(const string& word, vector<bool>& isFound ,char ch) {
    for (int i = 0; i < word.size(); i++) {
        if (ch == word[i]) {
            isFound[i] = true;
        }
    }
}

void printDashesWithLetter(const string& word, vector<bool>& isFound, char ch) {
    markFoundLetter(word, isFound, ch);

    for (int i = 0; i < word.size(); i++) {
        if (isFound[i]) {
            cout << word[i];
        }
        else {
            cout << '-';
        }
    }
    cout << endl;
}

bool checkIfEverythingIsFound(const vector<bool>& isFound) {
    for (int i = 0; i < isFound.size(); i++) {
        if (!isFound[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    addWords();
    int lives = 10;

    std::cout << "Welcome to our game! Guess the word by typing up a letter\n";

    srand(time(0));
    int randNum = rand() % (words.size() - 1);
    printDashes(randNum);
    vector<bool> isFound(words[randNum].size(), false);


    while (true) {

        cout << "Type a letter: ";
        char letter;
        cin >> letter;

        if (letterGuesses.count(letter) > 0) {
            cout << "You already tried that letter. Type in a new one\n";
            continue;
        }

        letterGuesses.insert(letter);

        if (isLetter(letter)) {            
            if (!findLetterInWord(words[randNum], letter)) {
                lives--;
                if (!lives) {
                    break;
                }
                cout << "Try again\n";
                cout << "You have " << lives << " remaining lifes\n";
            }
            else {

                printDashesWithLetter(words[randNum], isFound, letter);
            }
        }
        else {
            cout << "Type in a letter from a to z in lowercase.\n";
            continue;
        }

        if (checkIfEverythingIsFound(isFound)) {
            cout << "Congratulations! The word was " << words[randNum];
            cout << endl;
            break;
        }
    }

    if (lives == 0) {
        cout << "The word was " << words[randNum] << ", better luck next time!\n";
    }

    return 0;
}
