#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

class FileReader {
private:
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> tokenToOccurrence;
    
    /**
     * Parses the tokens from an open file stream into a vector.
     */
    void parseTokens(std::ifstream& stream);

    /**
     * Converts the list of tokens to a set.
     **/ 
    void toSet(std::vector<std::pair<std::string, int>>& emptyList);

    // prints the ten most occurring tokens and their occurrences
    void printTenMostOccurring(const std::vector<std::pair<std::string, int>>& sortedTokens);

    // prints the tokens and their number of reoccurrences in the file.
    void printTokenOccurrences();

public:
    // constructor + destructor
    FileReader(std::string& fileName);
    ~FileReader();

    /**
     * Counts the number of occurrences of repeated tokens in the token list and maps 
     * them to an unordered map.
     */
    void countTokens();

    /**
     * sorts the token list by occurrence in descending order.
     */
    void sortTokens();

    /**
     * Counts the number of most repeated characters in the token.abort
     * @return - number of most repeated characters.
     */
    int mostRepeatedChars(const std::string token);

    // overloaded friend function that prints out tokens and their occurrence in the file.
    friend std::ostream& operator<<(std::ostream& output, const FileReader& reader);
};


#endif