#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void HandleInput() = 0;
	virtual void UpdateGame() = 0;
	virtual void DrawElements(sf::RenderWindow&) = 0;
};