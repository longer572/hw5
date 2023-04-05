#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string currentWord,
    std::set<string>& words,
    int index,
    int numDashes);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Number of dashes - used in helepr function
    int n = 0;
    for (int i=0; i < (int) in.size(); i++) {
        if (in[i] == '-') {
            n++;
        }
    }

    std::set<std::string> result;
    wordleHelper(in, floating, dict, "", result, 0, n);
    return result;

}

// Define any helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string currentWord,
    std::set<string>& words,
    int index,
    int numDashes)
{
    // If a word has been fully completed
    if (index > (int) in.size() - 1) {
        if (dict.find(currentWord) != dict.end()) {
            words.insert(currentWord);
        }
        return;
    }

    // If the current letter is already fixed
    if (in[index] != '-') {
        currentWord += in[index]; 
        wordleHelper(in, floating, dict, currentWord, words, index+1, numDashes);
        return;

    // If the current letter is not fixed
    } else {

        // Need to know how if we can use a non-floating letter (ex: 4 -'s, 3 floating letters left)
        int sizeDif = numDashes - floating.size();
        for (size_t i = 0; i < floating.size(); i++) {
            std::string newCurrentWord = currentWord;
            newCurrentWord += floating[i];
            std::string newFloating = floating;
            newFloating.erase(newFloating.begin() + i);
            wordleHelper(in, newFloating, dict, newCurrentWord, words, index+1, numDashes-1);
        }
        
        // Trying all non-floating letter combinations if necessary
        if (sizeDif > 0) {
            for (int i = 0; i < 26; i++) {
                std::string newCurrentWord = currentWord;
                newCurrentWord += ('a' + i);
                wordleHelper(in, floating, dict, newCurrentWord, words, index+1, numDashes-1);
            }
        }
        return;
    }
}
