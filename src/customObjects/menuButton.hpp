#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class menuButton : public sf::Drawable
{
private:
	sf::RectangleShape box;
	sf::Font font;
	sf::Text boxText;
	std::string buttonName;
public:
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	sf::FloatRect getBounds();
	std::string getName();
public:
	menuButton(std::string, sf::Vector2f, sf::Vector2f);
	~menuButton();
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};
