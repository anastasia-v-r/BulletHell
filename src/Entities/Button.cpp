#include "Button.hpp"
#include "Globals.hpp"
#include <iostream>

Button::Button(std::string text, sf::Vector2f size, sf::Vector2f pos, sf::Color color)
	: box(size) {
	this->box.setPosition(pos);
	this->box.setFillColor(color);
	this->text = sf::Text(text, GlobalData::font, 30U);
	this->text.setPosition(pos);
}

void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(this->box);
	window.draw(this->text);
}
