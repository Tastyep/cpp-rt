#include "Parser.hh"

#include <iostream>

bool
Parser::parse(const std::string& fileName) {
    std::ifstream file;
    bool ret = false;

    file.open(fileName);
    if (file.is_open()) {
        this->readFile(file);
        file.close();
    }
    else
        std::cerr << "Could not open the file named \"" << fileName << "\"" << std::endl;
    return ret;
}

bool
Parser::readFile(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}
