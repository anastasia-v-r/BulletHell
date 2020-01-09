#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.hpp"

class Button : public UIElement
{
public:
	Button(std::string text, sf::Vector2f size, sf::Vector2f position, sf::Color color);
	inline bool contains(sf::Vector2f point)  override { return (box.getGlobalBounds().contains(point)) ? true : false; }
	inline void setActive() { this->active = !this->active; }
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
	sf::RectangleShape box;
	sf::Text text;
	bool active;
};