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
    
    //FIXME: must print path as well
    if(!stream.is_open()) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        return 1;
    }
    //FIXME: must print path as well
    std::cout << "Successfully read in file:" << fileName << std::endl;
    FileReader reader{fileName};
    std::vector<std::string> tokens;
    std::unordered_map<std::string, int> tokenCount;
    
    if (reader.getFileSize() > 4096) {
        std::cout << "The file is too large." << std::endl;
        return 1;
    }

    //FIXME: check file size
    reader.parseTokens(tokens);

    

}