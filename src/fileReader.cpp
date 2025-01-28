/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
 */

#include "../include/fileReader.h"
#include <string>

class FileReader;

FileReader::FileReader(std::string& fileName) : fileStream(fileName, std::ios::binary | std::ios::ate) {
    if (!fileStream.is_open()) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        throw std::runtime_error("Could not find the file " + fileName);
    }

    std::cout << "Successfully read in the file: " << fileName;

    if (getFileSize() > 4096) {
        std::cout << "The file is too large." << std::endl;
        throw std::runtime_error("The file " + fileName + " was too large.");
    }

    // moving pointer to the front of the stream again
    fileStream.seekg(0, std::ios::beg);
};

// parses the tokens into a list
void FileReader::parseTokens() {
    std::string token;

    // add each token from the file to the token vector
    while(this->fileStream.is_open()) {
        std::getline(fileStream, token, ' ');
        this->tokens.push_back(token);
    }
}

// counts tokens in a list and maps their occurrences to a map
void FileReader::countTokens() {
    for (auto& token : this->tokens) {
        this->tokenCount[token]++;
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

// overloaded friend function that prints the entire token map to the terminal
std::ostream& operator<<(std::ostream& output, const FileReader& reader) {
    for (auto& tokenPair : reader.tokenCount) {
        output << tokenPair.first << ": " << tokenPair.second << std::endl;
    }
}