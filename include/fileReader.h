#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

class FileReader {
private:
    // holds a list of all tokens in the input file.
    std::vector<std::string> tokens;
    // holds a mapping of all tokens to their number of occurrences in the input file.
    std::unordered_map<std::string, int> tokenToOccurrence;
    
    /**
     * Parses the tokens from an open file stream into a vector.
     * @param - An input file stream to read in the file.
     */
    void parseTokens(std::ifstream& stream);

    /**
     * Converts the list of tokens to a set.
     * @param - an empty vector ready to fill with the mapped key, value pairs.
     **/ 
    void toSet(std::vector<std::pair<std::string, int>>& emptyList);

    /**
     * Counts the number of most repeated characters in the token.abort
     * @param - a single token derived from the file.
     * @return - number of most repeated characters.
     */
    int mostRepeatedChars(const std::string& token);

    /** 
     * Prints the ten most occurring tokens.
     * @param - a vector of sorted tokens.
     * @param - the number of tokens to print.
     */
    void printTenMostOccurring(const std::vector<std::pair<std::string, int>>& sortedTokens, int numTokens);

    /**
     * Prints out the entire list of tokens and their occurrences unsorted.
     */
    void printTokenOccurrences();

    /**
     * Prints the tokens and their occurrences in the file.
     * @param - a token list to print.
     * @param - the number of tokens to print.
     */
    void printTokenOccurrences(const std::vector<std::pair<std::string, int>>& tokenList, int numTokens);

    /**
     * Prints the tokens and their lcharacter lengths.
     * @param - a token list to print.
     * @param - the number of tokens to print.
     */
    void printTokenLengths(const std::vector<std::pair<std::string, int>>& tokenList, int numTokens);

public:
    // constructor + destructor
    FileReader(std::string& fileName);
    ~FileReader();

    /**
     * Counts the number of occurrences of repeated tokens in the token list and maps 
     * them to an unordered map.
     */
    void countTokensOccurrences();

    /**
     * sorts the token list by occurrence in descending order.
     */
    void sortByOccurrence();

    /**
     * sorts the token list by character length in descending order.
     */
    void sortByLength();

    /**
     * Iterates through the unique tokens in the list and looks for the token with 
     * the most repeated characters.
     * @return - the token with the most repeated characters.
     */
    std::string getTokenWithMostRepeatedChars();

    // overloaded friend function that prints out tokens and their occurrence in the file.
    friend std::ostream& operator<<(std::ostream& output, const FileReader& reader);
};


#endif