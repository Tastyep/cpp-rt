#include "Parser.hh"
#include "Window.hh"

int main(int argc, char *argv[]) {
  Parser parser;
  Window window(1600, 900);
  bool valid_data = false;

  for (unsigned int i = 1; i < argc; ++i) {
    if (parser.parse(argv[i]))
      valid_data = true;
  }
  if (!valid_data)
    return 0;
  window.run();
  return 0;
}
