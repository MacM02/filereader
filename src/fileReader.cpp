/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
 */

#include "../include/fileReader.h"
#include <string>
#include <sstream>

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
    return output;
}