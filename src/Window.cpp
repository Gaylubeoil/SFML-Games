#include "Window.hpp"

Window::Window(const size_t _width, const size_t _height, const std::string Title)
{
    this->vm.width = _width;
    this->vm.height = _height;
    this->instance = new sf::RenderWindow(this->vm, Title, sf::Style::Close | sf::Style::Titlebar);
    instance->setFramerateLimit(60);
    instance->setVerticalSyncEnabled(false);
}

sf::RenderWindow *Window::get() const
{
    return instance;
}

size_t Window::getHeight() const
{
    return vm.height;
}

size_t Window::getWidth() const
{
    return vm.width;
}

Window::~Window()
{
    delete instance;
}