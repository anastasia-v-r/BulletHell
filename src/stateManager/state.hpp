#pragma once
#include <SFML/Graphics.hpp>

class State
{
private:


public:
	virtual void events() = 0;
	virtual void logic() = 0;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) = 0;
};