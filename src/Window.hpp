#pragma once
#include "PCH.hpp"

class Window {
public:
    Window(const size_t _width, const size_t _height, const std::string Title);
    sf::RenderWindow* get() const;
    size_t getWidth() const;
    size_t getHeight() const;

    ~Window();
private:
    sf::RenderWindow* instance;
    sf::VideoMode vm;

};