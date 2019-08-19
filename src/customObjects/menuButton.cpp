#include "menuButton.hpp"
#include <string>
#include <SFML/Graphics.hpp>

sf::Vector2f menuButton::getPos() {
	return box.getPosition();
}

sf::Vector2f menuButton::getSize() {
	return box.getSize();
}

sf::FloatRect menuButton::getBounds() {
	return box.getGlobalBounds();
}

std::string menuButton::getName() {
	return buttonName;
}

menuButton::menuButton(std::string text, sf::Vector2f sizeA, sf::Vector2f pos):box(sizeA) {
	buttonName = text;
	
	box.setFillColor(sf::Color::White);
	box.setOrigin(sizeA.x / 2, sizeA.y / 2);
	box.setPosition(pos);
	
	if (!font.loadFromFile("C:/Windows/Fonts/AGENCYB.TTF"));
	
	boxText = sf::Text(text, font, 20);
	boxText.setColor(sf::Color::Black);
	boxText.setOrigin(boxText.getPosition().x / 2, boxText.getPosition().y / 2);
	boxText.setPosition(box.getPosition().x, box.getPosition().y);
}

menuButton::~menuButton() {

}

void menuButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(box, states);
	target.draw(boxText, states);
}
