#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void HandleInput(sf::RenderWindow&) = 0;
	virtual void UpdateGame(sf::RenderWindow&) = 0;
	virtual void DrawElements(sf::RenderWindow&) = 0;
};