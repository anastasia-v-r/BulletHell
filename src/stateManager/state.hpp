#pragma once
#include <SFML/Graphics.hpp>

class State
{
private:


protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) = 0;
};