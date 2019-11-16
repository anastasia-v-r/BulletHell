#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void update(sf::Time /* elapsedTime */) = 0;
};