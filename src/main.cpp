/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 29th, 2025
 */
#include "../include/fileReader.h"
#include <string>

int main(int argc, char* argv[]) {
    // Two args should be the executable name and the file name.
    if (argc != 2) {
        std::cout << "Invalid number of arguments";
        return 1;
    }
    std::string fileName = argv[1];
    FileReader reader{fileName};
    
    // initializes map (token -> occurrence in file) + prints all tokens and occurrences (no order)
    reader.countTokensOccurrences();
    std::cout << std::endl;

    // prints the same list but in order by occurrence
    reader.sortByOccurrence();
    std::cout << std::endl;

    // prints the same length 
    reader.sortByLength();
    std::cout << std::endl;

    std::string repeatedCharToken = reader.getTokenWithMostRepeatedChars();
    std::cout << "The token with the most repeated characters is " << "'" << repeatedCharToken << "'!" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Thanks for using the fileReader!" << std::endl;
}