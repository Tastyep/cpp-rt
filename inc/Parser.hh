#ifndef RT_PARSER_HH
#define RT_PARSER_HH

#include <string>
#include <fstream>

class Parser
{
public:
    Parser() = default;

    ~Parser() = default;
    Parser(const Parser& other) = default;
    Parser(Parser&& other) = default;
    Parser& operator=(const Parser& other) = default;
    Parser& operator=(Parser&& other) = default;

public:
    bool parse(const std::string& fileName);

private:
    bool readFile(std::ifstream& file);
};

#endif /* end of include guard: RT_PARSER_HH */
