#include "Parser.hh"

int main(int argc, char* argv[])
{
    Parser  parser;
    bool    valid_data = false;

    for (unsigned int i = 1; i < argc; ++i) {
        if (parser.parse(argv[i]))
            valid_data = true;
    }
    if (!valid_data)
        return 0;

    return 0;
}
