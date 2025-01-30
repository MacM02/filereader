/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
 */

#include "../include/fileReader.h"
#include <string>
#include <sstream>
#include <array>
#include <algorithm>

class FileReader;

FileReader::FileReader(std::string& fileName) {

    std::ifstream fileStream(fileName, std::ios::binary | std::ios::ate);

    if (!fileStream.is_open()) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        throw std::runtime_error("Could not find the file " + fileName);
    }

    std::cout << "Successfully read in the file: " << fileName << std::endl;

    if (fileStream.tellg() > 4096) {
        throw std::runtime_error("The file " + fileName + " was too large.");
    }

    // moving pointer to the front of the stream again
    fileStream.seekg(0, std::ios::beg);
    parseTokens(fileStream);
};

FileReader::~FileReader() {};

// counts tokens in a list and maps their occurrences to a map and prints the results.
void FileReader::countTokens() {
    for (auto& token : this->tokens) {
        this->tokenToOccurrence[token]++;
    }
    printTokenOccurrences();
}

// sorts the list of tokens in descending order based on token occurrences and prints out the top 10.
void FileReader::sortTokens() {
    //creates an empty pair vector to fill with the unique token key, value pairs.
    std::vector<std::pair<std::string, int>> sortedTokens;
    toSet(sortedTokens);

    std::sort(sortedTokens.begin(), sortedTokens.end(), 
    [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });
    
    printTenMostOccurring(sortedTokens);
}

// prints the entire token map to the terminal
void FileReader::printTokenOccurrences() {
    std::cout << *this;
}

// prints the key and value of the first ten tokens in the list.
void FileReader::printTenMostOccurring(const std::vector<std::pair<std::string, int>>& sortedTokens) {
    std::string token;
    int occurrence;

    std::cout << "Ten most occurring tokens in the file!" << std::endl;
    for (int i = 0; i < 10; i++) {
        token = sortedTokens.at(i).first;
        occurrence = sortedTokens.at(i).second;
        std::cout << token << ": " << occurrence << std::endl;
    }
}

// counts and returns the number of the most repeated characer in a word.
int FileReader::mostRepeatedChars(const std::string token) {
    std::unordered_map<char, int> charToOccurrence;
    
    int charRepeats = 0;

    for (auto& letter : token) {
        charToOccurrence[letter]++;
        if (charToOccurrence[letter] > charRepeats) {
            charRepeats = charToOccurrence[letter];
        }
    }
    return charRepeats;
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
}

// mapping tokens to a vector that acts as a set
void FileReader::toSet(std::vector<std::pair<std::string, int>>& emptyList) {
    for (auto& token: this->tokenToOccurrence) {
        emptyList.push_back(token);
    }
}