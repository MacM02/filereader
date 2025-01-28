/**
 * Reads in a file and parses the data.
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
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
    std::fstream stream(fileName);
    FileReader reader{fileName};
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> tokenCount;
    
    // performing the work
    reader.parseTokens();
    reader.countTokens();
    reader.printTokenOccurrences();
    
    reader.sortTokens();
    reader.printTenMostOccurring();
}