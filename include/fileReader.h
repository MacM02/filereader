#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

class FileReader {
private:
    std::ifstream fileStream;

public:
    FileReader(std::string fileName) : fileStream(fileName) {
        if (!fileStream.is_open()) {
            //FIXME:make this a logger statement potentially
            std::cout << "Invalid file name: " << fileName;
            throw std::runtime_error("Could not find the file " + fileName);
        }
        std::cout << "Successfully read in the file: " << fileName;
    };

    /**
     * Parses the tokens in an open file stream into a vector.
     */
    void parseTokens(std::vector<std::string>& tokenList);

    /**
     * Counts the number of occurrences of repeated tokens in the token list and maps 
     * them to an unordered map.
     */
    void countTokens(std::unordered_map<std::string, int>& tokenCount, std::vector<std::string>& tokenList);

    /**
     * Gets the size of the file in the passed ifstream.
     * @return - the size of the file (in bytes).
     */
    int getFileSize();


};


#endif