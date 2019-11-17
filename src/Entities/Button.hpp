#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button(std::string /* text */, sf::Vector2f /* size */, sf::Vector2f /* position */, sf::Color /* color */);
	inline bool contains(sf::Vector2f point) { return (box.getGlobalBounds().contains(point)) ? true : false; }
	virtual void draw(sf::RenderTarget& /* window */, sf::RenderStates /* states */) const override;
private:
	sf::RectangleShape box;
	sf::Text text;
};