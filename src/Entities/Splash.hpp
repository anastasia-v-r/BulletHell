#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Splash : public sf::Drawable
{
public:
	Splash(sf::Texture& /* texture */);
	bool fade(sf::Time /* elapsedTime */);
	virtual void draw(sf::RenderTarget& /* window */, sf::RenderStates /* states */) const;
private:
	sf::Time timebank;
	sf::Sprite box;
	sf::RectangleShape cover;
	bool fadingIn;
};