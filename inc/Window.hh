#ifndef RT_WINDOW_HH
#define RT_WINDOW_HH

#include "Parser.hh"

#include <SFML/Graphics.hpp>

class Window {
public:
  Window(unsigned int width, unsigned int height);

  ~Window() = default;
  Window(const Window &other) = default;
  Window(Window &&other) = default;
  Window &operator=(const Window &other) = default;
  Window &operator=(Window &&other) = default;

  void run(const Parser& parser);

private:
  sf::RenderWindow _window;
};

#endif /* end of include guard: RT_WINDOW_HH */
