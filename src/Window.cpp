#include "Window.hh"
#include "Rt.hh"

#include <cstdint>
#include <iostream>
#include <thread>
#include <chrono>

Window::Window(unsigned int width, unsigned int height)
    : _window(sf::VideoMode(width, height), "Noise Renderer") {}

void Window::run(const Parser &parser) {
  sf::Event event;
  sf::Texture texture;
  sf::Vector2u size = _window.getSize();
  std::uint8_t *pixels = new std::uint8_t[4 * size.y * size.x];
  texture.create(size.x, size.y);
  sf::Sprite sprite(texture);
  Vector vision;

  Rt rt(parser.getCamera(), parser.getObjects(), parser.getLights());
  unsigned int color;
  unsigned int pos;

  while (_window.isOpen()) {
    _window.clear();
    pos = 0;
    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        _window.close();
    }
    for (unsigned int y = 0; y < size.y; ++y) {
      for (unsigned int x = 0; x < size.x; ++x) {
        rt.computeRayVec(vision, x, y, static_cast<sf::Vector2i>(size));
        color = rt.computePixelColor(vision);
        pixels[4 * pos] = (color >> 16) & 0xFF;
        pixels[4 * pos + 1] = (color >> 8) & 0xFF;
        pixels[4 * pos + 2] = color & 0xFF;
        pixels[4 * pos + 3] = 0xFF;
        ++pos;
      }
    }
    texture.update(pixels);
    _window.draw(sprite);
    _window.display();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}