#pragma once
#include <SFML/Graphics.hpp>

class State : public sf::Drawable
{
private:


public:

	virtual void draw(sf::RenderTarget&, sf::RenderStates) = 0;
};