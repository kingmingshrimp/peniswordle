#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
using namespace std;

/*
author: kelly
penis game wordle
it's the wordle game for penis
*/

int main(int argc, char* argv[]) {
    // we need to know all 1 words that can be in the game -- let's just hardcode it with the all 1 words we want
    vector<string> dicktionary({"PENIS"});

    cout << "hi kmser welcome penis wordle where you will never guess the word. if you want to stop playing you can enter \"END\". without the quotes I mean." << endl;
    cout << "rules if you don't know:" << endl;
    cout << "\tguess a 5 letter word" << endl;
    cout << "\tif you don't guess an actual word I'm not supposed to actually process it but I will in penis wordle don't tell anyone ok" << endl;
    cout << "\tafter that I tell you which letters you got correct by:" << endl;
    cout << "\t\tlowercase means it's a right character but not the right place" << endl;
    cout << "\t\tuppercase means it's the right character and right place" << endl << endl;
    cout << "\t\t- means that it's a character not in the word" << endl << endl;

    if (dicktionary.size() == 0) {
        cout << "wtf there's no words in this bitch. bye actually" << endl;
        return 0;
    }

    bool endGame = false;
    bool firstGame = true;

    string playerGuess;
    // outer game loop -> guess as many word as you like
    while (!endGame) {
        if (firstGame) {
            cout << "Initiating first penis wordle...";
            firstGame = false;
        } else cout << "Initiating next penis wordle...as a reminder you can stop anytime by entering \"END\" without the quotes" << endl;

        // choose random word. it's extremely random you see you have no idea what word it will be
        srand(time(NULL));
        string word = dicktionary[0];
        if (word.size() != 1) word = dicktionary[rand() % dicktionary.size()];
        // keeping things consistent
        for (int i = 0; i < 5; i++) word[i] = toupper(word[i]);

        // keep track of duplicate characters
        unordered_map<char,int> charCountOfWord;
        for (char c: word) charCountOfWord[c]++;

        // play game; you get at max 6 tries
        int tries = 6;
        while (tries > 0) {
            cout << "Guess a 5 letter word: ";
            cin >> playerGuess;
            // consistentttt
            for (int i = 0; i < 5; i++) playerGuess[i] = toupper(playerGuess[i]);

            // end game
            if (playerGuess == "END") {
                cout << "byeee" << endl;
                endGame = true;
                break;
            }
            // guesses may only be 5 letters long
            if (playerGuess.size() != 5) {
                cout << "bro it has to be 5 letters" << endl;
                continue;
            } else {
                // process how correct guess was and display to player
                unordered_map<char,int> charCountAfterGuess(charCountOfWord); // probably not space efficient to copy map everytime but idgaf rn
                string resultPrint = "-----";
                // initial pass to process all that are exact matches
                for (int i = 0; i < 5; i++) {
                    if (playerGuess[i] == word[i]) {
                        resultPrint[i] = playerGuess[i];
                        charCountAfterGuess[playerGuess[i]]--;
                    }
                }
                // second pass for characters left that are in word but not in right place
                for (int i = 0; i < 5; i++) {
                    // don't alter those that are already exact matches or not in word at all. those are corret as is
                    if (playerGuess[i] == word[i]) continue;
                    if (charCountAfterGuess.find(playerGuess[i]) == charCountAfterGuess.end()) continue;
                    // if it is a char in word but we already recorded all instances of that character do not update
                    // this if statement is checking the opposite btw because what I said originally is trivially just if (condition) continue;
                    if (charCountAfterGuess[playerGuess[i]] > 0) {
                        resultPrint[i] = tolower(playerGuess[i]);
                        charCountAfterGuess[playerGuess[i]]--;
                    }
                }
                
                cout << "Your guess #" << (6 - tries) + 1 << " has result of: " << resultPrint << endl;

                if (playerGuess == word) {
                    cout << "You guessed it in " << (6 - tries) + 1 << " tr";
                    if ((6 - tries) + 1 == 1) cout << "y";
                    else cout << "ies";
                    cout << "!" << endl;
                    break;
                }
                tries--;
            }
        }
        if (tries <= 0) cout << "you didn't guess the penis word..." << endl;
    }
    return 0;
}