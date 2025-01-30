/**
 * Reads in a file and parses the data by counting token occurrences, finding 
 * tokens with the greatest length, and the token with the most repeating
 * characters.
 * 
 * Mack Muir-Jeffryes
 * January 29th, 2025
 */

#include "../include/fileReader.h"
#include <string>
#include <sstream>
#include <array>
#include <algorithm>

class FileReader;

FileReader::FileReader(std::string& fileName) {
    std::ifstream fileStream(fileName, std::ios::ate);

    if (!fileStream.is_open()) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        throw std::runtime_error("Could not find the file " + fileName);
    }

    std::cout << "Successfully read in the file: " << fileName << std::endl;

    if (fileStream.tellg() > 4096) {
        throw std::runtime_error("The file " + fileName + " was too large. Must be smaller than 4096 bytes.");
    }

    // moving pointer to the front of the stream again
    fileStream.seekg(0, std::ios::beg);

    // initializing tokenToOccurrence and tokenSet
    parseTokens(fileStream);
};

// default destructor
FileReader::~FileReader() {};

// counts tokens in a list and maps their occurrences to a map and prints the results.
void FileReader::countTokensOccurrences() {
    for (auto& token : this->tokens) {
        this->tokenToOccurrence[token]++;
    }
    std::cout << "Printing out all tokens and their occurrences unsorted!" << std::endl;
    std::cout << "Token: " << "Occurrence" << std::endl;
    printTokenOccurrences();
}

// sorts the list of tokens in descending order based on token occurrences and prints out the top 10.
void FileReader::sortByOccurrence() {
    std::vector<std::pair<std::string, int>> tokenVector;

    // initializing the token set with the mapped K,V pairs
    toSet(tokenVector);

    std::sort(tokenVector.begin(), tokenVector.end(), 
    [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });
    
    std::cout << "Printing out all tokens and their occurrences sorted!" << std::endl;
    int numTokens = tokenVector.size();
    std::cout << "Token: " << "Occurrence" << std::endl;
    printTokenOccurrences(tokenVector, numTokens);
}

// fills an empty vector with the a sorted list of tokens based on character length.
void FileReader::sortByLength() {
    std::vector<std::pair<std::string, int>> tokenVector;

    // initializing the token set with the mapped K,V pairs
    toSet(tokenVector);

    // lambda comparator passed to sort by descending order
    std::sort(tokenVector.begin(), tokenVector.end(), 
    [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.first.length() > b.first.length();
        });

    std::cout << "Printing out the 10 tokens with the greatest length!" << std::endl;
    std::cout << "Token: " << "Length" << std::endl;
    printTokenLengths(tokenVector, 10);
}

// returns the token with the most repeated characrters in the file.
std::string FileReader::getTokenWithMostRepeatedChars() {
    std::string mostRepeats = "";
    int numRepeatedChars = 0;

    for (auto& token : this->tokenToOccurrence) {
        // get tokens repeated char count
        int currentTokenChars = mostRepeatedChars(token.first);
        // compare this count to the last highest char count
        if (currentTokenChars > numRepeatedChars) {
            numRepeatedChars = currentTokenChars;
            mostRepeats = token.first;
        }
    }
    return mostRepeats;
}

// overloaded friend function that prints the entire token map to the terminal
std::ostream& operator<<(std::ostream& output, const FileReader& reader) {
    for (auto& tokenPair : reader.tokenToOccurrence) {
        output << tokenPair.first << ": " << tokenPair.second << std::endl;
    }
    return output;
}

// Private helpers:

// parses the tokens into a list
void FileReader::parseTokens(std::ifstream& fileStream) {
    std::string tokenLine;

    // add each token from the file to the token vector by splitting lines into tokens
    while(std::getline(fileStream, tokenLine)) {
        std::istringstream lineStream(tokenLine);
        std::string token;
        while (lineStream >> token) {
            this->tokens.push_back(token);
        }
    }
    fileStream.close();

    if (this->tokens.size() == 0) {
        std::cout << "The file was empty! No tokens could be parsed." << std::endl;
        throw std::invalid_argument("The file was empty! Nothing to read here.");
    }
}

// mapping tokens to a vector that acts as a set
void FileReader::toSet(std::vector<std::pair<std::string, int>>& emptyList) {
    for (auto& token: this->tokenToOccurrence) {
        emptyList.push_back(token);
    }
}

// counts and returns the number of the most repeated characer in a word.
int FileReader::mostRepeatedChars(const std::string& token) {
    std::unordered_map<char, int> charToOccurrence;
    int charRepeats = 0;

    for (auto& letter : token) {
        charToOccurrence[letter]++;

        // if the newly incremented value of the character key is greater than the old value, set new.
        if (charToOccurrence[letter] > charRepeats) {
            charRepeats = charToOccurrence[letter];
        }
    }
    return charRepeats;
}

// prints the tokens with the most characters
void FileReader::printTokenLengths(const std::vector<std::pair<std::string, int>>& tokenList, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        std::cout << tokenList.at(i).first << ": " << tokenList.at(i).first.length() << std::endl;
    }
}

// prints all the tokens and their occurrences by calling overloaded friend function.
void FileReader::printTokenOccurrences() {
    std::cout << *this;
}

// prints the key and value of the first ten tokens in the list.
void FileReader::printTokenOccurrences(const std::vector<std::pair<std::string, int>>& sortedTokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        std::cout << sortedTokens.at(i).first << ": " << sortedTokens.at(i).second << std::endl;
    }
}