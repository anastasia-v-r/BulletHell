#pragma once
#include <SFML/Graphics.hpp>

class State
{
private:


public:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) = 0;
};