#include "SceneObj.hh"

#include <iostream>
#include <stdexcept>

bool SceneObj::parseArg(const std::vector<std::string>& tokens) {
    auto it1 = IntegerValues.find(tokens[0]);
    auto it2 = FloatingValues.find(tokens[0]);
    
    if (it1 == IntegerValues.end() && it2 == FloatingValues.end()) {
        std::cerr << "Unknown keyword \"" << tokens[0] << "\"" << std::endl;
        return false;
    }
    if (it1 == IntegerValues.end()) {
        try {
            it2->second.get() = std::stof(tokens[2]);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
    else {
        try {
            it1->second.get() = std::stoi(tokens[2]);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }        
    }
    return true;
}

bool SceneObj::parseArgs(std::stringstream &ss) {
    std::vector<std::string> tokens;
    std::string token;
    
    while (ss >> std::dec >> token) {
        tokens.push_back(token);
    }
    if (tokens.size() != 3)
        return true;
    return this->parseArg(tokens);
}