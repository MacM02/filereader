#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

class FileReader {
private:
    std::ifstream fileStream;
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> tokenCount;
public:
    // constructor + destructor
    FileReader(std::string& fileName);
    ~FileReader();

    /**
     * Parses the tokens in an open file stream into a vector.
     */
    void parseTokens();

    /**
     * Counts the number of occurrences of repeated tokens in the token list and maps 
     * them to an unordered map.
     */
    void countTokens();

    /**
     * Gets the size of the file in the passed ifstream.
     * @return - the size of the file (in bytes).
     */
    int getFileSize();

    // prints the tokens and their number of reoccurrences in the file.
    void printTokenOccurrences();

    // overloaded friend function that prints out tokens and their occurrence in the file.
    friend std::ostream& operator<<(std::ostream& output, const FileReader& reader);
};


#endif