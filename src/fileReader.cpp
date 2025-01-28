/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
 */

#include "../include/fileReader.h"
#include <string>

// parses the tokens into a list
void FileReader::parseTokens(std::vector<std::string>& tokenList) {
    std::string token;

    // add each token from the file to the token vector
    while(this->fileStream.is_open()) {
        std::getline(fileStream, token, ' ');
        tokenList.push_back(token);
    }
}

// counts tokens in a list and maps their occurrences to a map
void FileReader::countTokens(std::unordered_map<std::string, int>& tokenCount, std::vector<std::string>& tokenList) {
    for (auto token : tokenList) {
        tokenCount[token]++;
    }
}

// gets the size of the file in the stream
int FileReader::getFileSize() {

}