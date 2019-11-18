#include "Button.hpp"
#include <iostream>

Button::Button(std::string text, sf::Vector2f size, sf::Vector2f pos, sf::Color color)
	: box(size) {
	this->box.setPosition(pos);
	this->box.setFillColor(color);
	if (!this->font.loadFromFile("assets/Global/font/OpenSans-Regular.ttf"))
		std::cout << "Font Failed to load" << std::endl;
	this->text = sf::Text(text, font, 30U);
}

void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(this->box);
	window.draw(this->text);
}
