#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum StateEnum
{
	Splash,
	Menu,
	Game
};

class State
{
public:
	virtual void HandleInput(sf::RenderWindow&) = 0;
	virtual void UpdateGame(sf::RenderWindow&) = 0;
	virtual void DrawElements(sf::RenderWindow&) = 0;
private:

public:
	bool moveState;
	StateEnum nextState;
};