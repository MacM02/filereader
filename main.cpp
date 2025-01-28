/**
 * Reads in a file and parses the data based on 
 * 
 * Mack Muir-Jeffryes
 * January 27th, 2025
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

// parses the tokens into a list
void parseTokens(std::ifstream& stream, std::vector<std::string>& tokenList) {

}

// counts tokens in a list and maps their occurrences to a map
void countTokens(std::unordered_map<std::string, int> tokenCount, std::vector<std::string>& tokenList) {

}

// gets the size of the file in the stream
int getFileSize(std::ifstream& stream) {

}


int main(int argc, char* argv[]) {
    // Two args should be the executable name and the file name.
    if (argc != 2) {
        std::cout << "Invalid number of arguments";
        return 1;
    }
    std::string fileName = argv[1];
    std::fstream reader(fileName);

    //FIXME: must print path as well
    if(!reader.is_open()) {
        std::cout << "Invalid file name: " << fileName;
        return 1;
    }
    //FIXME: must print path as well
    std::cout << "Successfully read in file:" << fileName;

    //FIXME: check file size


}