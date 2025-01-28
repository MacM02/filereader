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

class FileReader;

FileReader::FileReader(std::string& fileName) : fileStream(fileName, std::ios::binary | std::ios::ate) {
    if (!fileStream.is_open()) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        throw std::runtime_error("Could not find the file " + fileName);
    }

    std::cout << "Successfully read in the file: " << fileName << std::endl;

    if (getFileSize() > 4096) {
        throw std::runtime_error("The file " + fileName + " was too large.");
    }

    // moving pointer to the front of the stream again
    fileStream.seekg(0, std::ios::beg);
};

FileReader::~FileReader() {};

// parses the tokens into a list
void FileReader::parseTokens() {
    std::string tokenLine;

    // add each token from the file to the token vector by splitting lines into tokens
    while(std::getline(fileStream, tokenLine)) {
        std::istringstream lineStream(tokenLine); 
        std::string token;
        while (lineStream >> token) {
            this->tokens.push_back(token);
        }
    }
    this->fileStream.close();
}

// counts tokens in a list and maps their occurrences to a map
void FileReader::countTokens() {
    for (auto& token : this->tokens) {
        this->tokenCount[token]++;
    }
}

// sorts the list of tokensin descending order based on  text occurrences.
void FileReader::sortTokens() {
    // getting vector of pair<string, int> that only has unique tokens
    toSet();

    // unique tokens is a vector of pair<string, int>
    int numTokens = sortedTokens.size();
    // O(N^2) amortized
    for (int i = 0; i < numTokens - 1; i++) {
        // while the second token is greater than the first swap the elements
        std::pair<std::string, int> tempPair;
        
        // best case -> O(1)
        // worst/avg (O(N))
        int currIndex = i;
        int previousIndex = i + 1;
        while (!compare(sortedTokens.at(currIndex), sortedTokens.at(previousIndex)) && (currIndex >= 0)) {
            // O(1)
            std::swap(sortedTokens.at(currIndex), sortedTokens.at(previousIndex));
            currIndex--;
            previousIndex--;
        }
    }
}

// gets the size of the file in the stream
int FileReader::getFileSize() {
    return this->fileStream.tellg();
}

// prints the entire token map to the terminal
void FileReader::printTokenOccurrences() {
    std::cout << *this;
}

// mapping tokens to a vector that acts as a set
void FileReader::toSet() {
    for (auto& token: this->tokenCount) {
        this->sortedTokens.push_back(token);
    }
}

void FileReader::printTenMostOccurring() {
    std::string token;
    int occurrence;

    std::cout << "Ten most occurring tokens in the file!" << std::endl;
    for (int i = 0; i < 10; i++) {
        token = this->sortedTokens.at(i).first;
        occurrence = this->sortedTokens.at(i).second;
        std::cout << token << ": " << occurrence << std::endl;
    }
}

// compares a pair of values
bool FileReader::compare(const std::pair<std::string, int> first, const std::pair<std::string, int> last) {
    return first.second >= last.second;
}

// overloaded friend function that prints the entire token map to the terminal
std::ostream& operator<<(std::ostream& output, const FileReader& reader) {
    for (auto& tokenPair : reader.tokenCount) {
        output << tokenPair.first << ": " << tokenPair.second << std::endl;
    }
    return output;
}