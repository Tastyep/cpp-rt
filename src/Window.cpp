#include "Window.hh"

Window::Window(unsigned int width, unsigned int height)
    : _window(sf::VideoMode(width, height), "Noise Renderer") {}

void Window::run() {
  sf::Event event;
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2u size = _window.getSize();

  image.create(size.x, size.y, sf::Color::Black);
  texture.create(size.x, size.y);
  while (_window.isOpen()) {
    _window.clear();
    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        _window.close();
    }
    _window.draw(sprite);
    _window.display();
  }
}